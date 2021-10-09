#include "bertlv.h"

#include <stdlib.h>
#include <string.h>

#include "btlvConfig.h"
#include "io/printinghelper.h"
#include "tlvparser.h"

const char *
BTLV_getVersion(void)
{
    return BTLV_VERSION_MAJOR "." BTLV_VERSION_MINOR "." BTLV_VERSION_PATCH;
}

/** This function is not part of API
  * 
  * It does parse TLV objects recursively and outputs a TLV objects tree
  * through parameter decodedObject and the amount of bytes parsed.
  * 
  * On fail it return the properly return code.
  */
static BTLV_ReturnCode
decodeTlvObjectRecursive(const uint8_t *const tlvObjectBuffer,
                         const size_t objectBufferSize,
                         BTLV_DataObject *decodedObject,
                         size_t *const decodedBytesCount)
{
    if (tlvObjectBuffer == NULL || decodedObject == NULL || decodedBytesCount == NULL)
        return BTLV_INVALID_PARAMETER;

    if (objectBufferSize == 0)
        return BTLV_BAD_TLV_ENCODING;

    // current tlvObjectBuffer input array byte index being processed
    size_t currentByte = 0;
    BTLV_ReturnCode ret = BTLV_GENERIC_ERROR;

    ret = BTLV_tagFieldParse(tlvObjectBuffer, objectBufferSize, decodedObject);

    if (ret == BTLV_RET_OK) {
        // Advancing the bytes of tag field
        currentByte += decodedObject->tagSize;

        size_t lengthFieldByteCount = 0;
        // Passing to length field parser the position of tlv data object buffer that length field starts
        // and subtracting from buffer size the amount of bytes that was left behind for tag field
        ret = BTLV_lengthFieldParse(&(tlvObjectBuffer[currentByte]),
                                    objectBufferSize - currentByte,
                                    &(decodedObject->length),
                                    &lengthFieldByteCount);

        // Advancing the bytes of length field
        currentByte += lengthFieldByteCount;
    }

    // Check if tag field and length field were parsed succesfully
    if (ret != BTLV_RET_OK)
        return ret;

    // Check if there is enough space in buffer to parse value field
    if (decodedObject->length > (objectBufferSize - currentByte))
        return BTLV_BAD_TLV_ENCODING;

    *decodedBytesCount = currentByte + decodedObject->length;

    if (decodedObject->type == BTLV_PRIMITIVE) {
        decodedObject->valueField.value = malloc(sizeof(uint8_t) * decodedObject->length);

        if(decodedObject->valueField.value == NULL)
            return BTLV_MEMORY_NOT_ENOUGH;

        memcpy(decodedObject->valueField.value, &(tlvObjectBuffer[currentByte]), decodedObject->length);

        return BTLV_RET_OK;
    } else {
        return BTLV_decodeTlvObject(&(tlvObjectBuffer[currentByte]),
                                    objectBufferSize - currentByte,
                                    &(decodedObject->valueField.children),
                                    &(decodedObject->childObjectsCount));
    }
}

BTLV_ReturnCode
BTLV_decodeTlvObject(const uint8_t *const tlvObjectBuffer,
                     const size_t objectBufferSize,
                     BTLV_DataObject **tlvDataObjectsArray,
                     size_t *const tlvDataObjectsCount)
{
    if (tlvObjectBuffer == NULL || tlvDataObjectsArray == NULL || tlvDataObjectsCount == NULL)
        return BTLV_INVALID_PARAMETER;

    // Output parameters clean up
    *tlvDataObjectsArray = NULL;
    *tlvDataObjectsCount = 0;

    if (objectBufferSize == 0)
        return BTLV_BAD_TLV_ENCODING;

    // Array of decoded tlv data object elements
    BTLV_DataObject *tlvElementsArray = malloc(sizeof(BTLV_DataObject) * BTLV_ARRAY_INITIAL_SIZE_HEURISTIC);

    if (tlvElementsArray == NULL)
        return BTLV_MEMORY_NOT_ENOUGH;

    // Current length and position. Array length may be changed for more elements or fit exact found elements
    size_t arrayLength = BTLV_ARRAY_INITIAL_SIZE_HEURISTIC;
    size_t currentArrayPosition = 0;

    // Current position at tlvObjectBuffer
    size_t currentByte = 0;

    while(currentByte < objectBufferSize) {
        // Array needs more space for more data object elements
        if(currentArrayPosition >= arrayLength) {
            BTLV_DataObject *newTlvElementsArray = realloc(tlvElementsArray, arrayLength + BTLV_ARRAY_INITIAL_SIZE_HEURISTIC);

            // Check if reallocation the array succeed
            if(newTlvElementsArray == NULL) {
                // Failed
                BTLV_destroyTlvObjectArray(tlvElementsArray, arrayLength);
                return BTLV_MEMORY_NOT_ENOUGH;
            } else {
                // Success
                tlvElementsArray = newTlvElementsArray;
                arrayLength += BTLV_ARRAY_INITIAL_SIZE_HEURISTIC;
            }
        }

        size_t decodedBytes = 0;
        BTLV_ReturnCode ret = decodeTlvObjectRecursive(&(tlvObjectBuffer[currentByte]),
                                                       objectBufferSize - currentByte,
                                                       &(tlvElementsArray[currentArrayPosition]),
                                                       &decodedBytes);

        ++currentArrayPosition;
        currentByte += decodedBytes;

        // Decoding failed
        if(ret != BTLV_RET_OK) {
            BTLV_destroyTlvObjectArray(tlvElementsArray, currentArrayPosition);
            return ret;
        }
    }

    *tlvDataObjectsArray = tlvElementsArray;
    *tlvDataObjectsCount = currentArrayPosition;

    return BTLV_RET_OK;
}

BTLV_ReturnCode
BTLV_encodeTlvObject(const BTLV_DataObject *const object, uint8_t *const tlvObjectBuffer, const size_t objectBufferSize)
{
    (void)object;
    (void)tlvObjectBuffer;
    (void)objectBufferSize;

    return BTLV_GENERIC_ERROR;
}

BTLV_ReturnCode
BTLV_printObject(const BTLV_DataObject *const object)
{
    if (object == NULL)
        return BTLV_INVALID_PARAMETER;

    return BTLV_depthFirstNavigateObject(object, BTLV_getDefaultNavigatorPrinter());
}

static BTLV_ReturnCode
depthFirstNavigateObjectRecursive(const BTLV_DataObject *const object,
                                  const BTLV_objectPrintCallback printObjectCallback,
                                  const uint8_t nestingLevel,
                                  BTLV_ObjectPrintCallbackRetVal *controlRaising)
{
    if(object == NULL || printObjectCallback == NULL)
        return BTLV_INVALID_PARAMETER;

    BTLV_ObjectPrintCallbackRetVal control = printObjectCallback(object, nestingLevel);

    switch(control) {
        case BTLV_DEPTH_NAVIGATION_STEP_INTO:
            if (object->type == BTLV_CONSTRUCTED) {
                for (size_t i = 0; i < object->childObjectsCount; ++i) {
                    BTLV_ReturnCode ret = depthFirstNavigateObjectRecursive(
                        &(object->valueField.children[i]),
                        printObjectCallback,
                        nestingLevel + 1,
                        &control);

                    if (ret != BTLV_RET_OK)
                        return ret;

                    if (control == BTLV_DEPTH_NAVIGATION_STEP_OUT) {
                        *controlRaising = BTLV_DEPTH_NAVIGATION_STEP_INTO;
                        return BTLV_RET_OK;
                    }

                    if (control == BTLV_DEPTH_NAVIGATION_HALT) {
                        *controlRaising = BTLV_DEPTH_NAVIGATION_HALT;
                        return BTLV_RET_OK;
                    }
                }
            }
            return BTLV_RET_OK;

        case BTLV_DEPTH_NAVIGATION_STEP_OVER:
            // Don't go further nesting on current object but return control to previous
            // level to keep going
            *controlRaising = BTLV_DEPTH_NAVIGATION_STEP_INTO;
            return BTLV_RET_OK;

        case BTLV_DEPTH_NAVIGATION_STEP_OUT:
        case BTLV_DEPTH_NAVIGATION_HALT:
            // Return command to previous level so they know what to do
            // totally halt or go one level backward
            *controlRaising = control;
            return BTLV_RET_OK;

        default:
            // Invalid control command received.
            return BTLV_BAD_CALLBACK_COMMAND;
    }
}

BTLV_ReturnCode
BTLV_depthFirstNavigateObject(const BTLV_DataObject *const object, const BTLV_objectPrintCallback printObjectCallback)
{
    if(object == NULL || printObjectCallback == NULL)
        return BTLV_INVALID_PARAMETER;

    BTLV_ObjectPrintCallbackRetVal control;

    return depthFirstNavigateObjectRecursive(object, printObjectCallback, 0u, &control);
}

BTLV_ReturnCode
BTLV_blockOfBytesNavigateObject(const uint8_t *const tlvObjectBuffer,
                                const size_t objectBufferSize,
                                const BTLV_objectPrintCallback printObjectCallback)
{
    (void)tlvObjectBuffer;
    (void)objectBufferSize;
    (void)printObjectCallback;

    return BTLV_GENERIC_ERROR;
}

void
BTLV_destroyTlvObject(BTLV_DataObject *const object)
{
    if (object != NULL) {
        if (object->type == BTLV_PRIMITIVE) {
            free(object->valueField.value);
            object->valueField.value = NULL;
        } else {
            BTLV_destroyTlvObjectArray(object->valueField.children, object->childObjectsCount);
            object->childObjectsCount = 0;
            object->valueField.children = NULL;
        }
    }
}

void
BTLV_destroyTlvObjectArray(BTLV_DataObject *const objectArray, const size_t elementCount)
{
    if(objectArray != NULL && elementCount > 0) {
        for(size_t i = 0; i <= elementCount; ++i) {
            BTLV_destroyTlvObject(&(objectArray[i]));
        }

        free(objectArray);
    }
}