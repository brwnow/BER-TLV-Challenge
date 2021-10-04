#include "bertlv.h"

#include "btlvConfig.h"

const char *BTLV_getVersion(void)
{
    return BTLV_VERSION_MAJOR "." BTLV_VERSION_MINOR "." BTLV_VERSION_PATCH;
}

BTLV_ReturnCode BTLV_decodeTlvObject(const uint8_t *const tlvObjectBuffer, const size_t objectBufferSize, BTLV_DataObject **decodedObject)
{
    (void)tlvObjectBuffer;
    (void)objectBufferSize;
    (void)decodedObject;

    return BTLV_GENERIC_ERROR;
}

BTLV_ReturnCode BTLV_encodeTlvObject(const BTLV_DataObject *const object,
                         uint8_t *const tlvObjectBuffer,
                         const size_t objectBufferSize)
{
    (void)object;
    (void)tlvObjectBuffer;
    (void)objectBufferSize;

    return BTLV_GENERIC_ERROR;
}

BTLV_ReturnCode BTLV_printObject(const BTLV_DataObject *const object)
{
    (void)object;

    return BTLV_GENERIC_ERROR;
}

BTLV_ReturnCode BTLV_depthFirstNavigateObject(const BTLV_DataObject *const object,
                                   const BTLV_objectPrintCallback printObjectCallback)
{
    (void)object;
    (void)printObjectCallback;

    return BTLV_GENERIC_ERROR;
}

BTLV_ReturnCode BTLV_blockOfBytesNavigateObject(const uint8_t *const tlvObjectBuffer,
                                     const size_t objectBufferSize,
                                     const BTLV_objectPrintCallback printObjectCallback)
{
    (void)tlvObjectBuffer;
    (void)objectBufferSize;
    (void)printObjectCallback;

    return BTLV_GENERIC_ERROR;
}

void BTLV_destroyTlvObject(BTLV_DataObject *const object)
{
    (void)object;
}