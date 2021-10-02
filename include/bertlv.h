/**
 * @file bertlv.h
 * @brief BER-TLV objects encoding/decoding API.
 *
 * API for working with BER-TLV data objects. Functions to encode, decode and help on printing formatted BER-TLV object fields and data.
 *
 */

#ifndef BTLV_LIB_BERTLV_H
#define BTLV_LIB_BERTLV_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BTLV_TAG_MAX_SIZE 3

/**
 * @brief Class of BER-TLV data object
 *
 */
typedef enum {
    BTLV_CLASS_UNIVERSAL = 0, /**< Universal class */
    BTLV_CLASS_APPLICATION, /**< Application class */
    BTLV_CLASS_CONTEXT_SPECIFIC, /**< Context-specific class */
    BTLV_CLASS_PRIVATE /**< Private class */
} BTLV_ObjectClass;

/**
 * @brief Type of BER-TLV data object
 *
 */
typedef enum {
    BTLV_PRIMITIVE = 0, /**< Value field holds a number instead of sub data objects */
    BTLV_CONSTRUCTED /**< Value field holds sub data objects */
} BTLV_ObjectType;

/**
 * @brief Return codes for BTLV_objectPrintCallback
 *
 * BTLV_objectPrintCallback can control the navigation through tree of data objects returning next action that must be performed.
 *  This way its possible to ignore completly some data objects and its children or stop at certain data object and return to the
 * parent data object, ignoring subsequent data object in current nesting level. STEP_INTO is the control to go further on nesting
 * if current data object is of type constructed.
 *
 */
typedef enum {
    BTLV_DEPTH_NAVIGATION_STEP_INTO, /**< Go further on nesting level when navigating through a data objects tree */
    BTLV_DEPTH_NAVIGATION_STEP_OVER, /**< Ignores nesting of current data object if its of type constructed */
    BTLV_DEPTH_NAVIGATION_STEP_OUT /**< Ignores current data object nesting and subsequent data objects at current nesting level */
} BTLV_ObjectPrintCallbackRetVal;

/**
 * @brief BER-TLV data object with information about the TLV object
 *
 * All information decoded from binary TLV data object are stored in this struct.
 *  For example class, type, length, tag etc. This struct works as a tree of
 * constructed and primitives data objects.
 *
 */
typedef struct _DataObject {
    BTLV_ObjectClass class; /**< Class of data object */
    BTLV_ObjectType type; /**< Type of data object */
    uint8_t tag[BTLV_TAG_MAX_SIZE]; /**< Content data of TAG */
    size_t tagSize; /**< TAG content data size in bytes */
    size_t length; /**< Length of value field in bytes */
    uint32_t childObjectsCount; /**< For constructed data objects, amount of children data objects */

    union {
        uint8_t *value; /**< Pointer to bytes of value field */
        struct _DataObject *children; /**< Array of children data objects */
    };
} BTLV_DataObject;

/**
 * @brief Callback for printing data objects during a navigation through a tree of data objects
 *
 */
typedef void (*BTLV_objectPrintCallback)(const BTLV_DataObject* const, const uint8_t nestingLevel);

/**
 * @brief Gets the string of BTLV lib full version
 *
 * @return Returns a string representing the BTLV lib version formatted as MAJOR.MINOR.PATCH
 *
 */
const char* BTLV_getVersion(void);

/**
 * @brief Decode a BER-TLV data object to a tree of TLV data objects.
 *
 * Receives a BER-TLV data object encoded as block of bytes and decode it to a tree of
 * BTLV_DataObject representing all the information encoded passed.
 *
 * @param[in] tlvObjectBuffer The address of the BER-TLV data object block of bytes in memory.
 * @param[in] objectBufferSize Size of the data object block of bytes.
 *
 * @return On success returns the tree of data objects resulting from the decoding proccess
 * @return On failing, returns NULL
 *
 */
BTLV_DataObject* BTLV_decodeTlvObject(const uint8_t* const tlvObjectBuffer, const size_t objectBufferSize);

/**
 * @brief Encode a BER-TLV data object from tree of objects to block of bytes.
 *
 * Receives a BER-TLV data object as a tree of data objects and encode it to a block of bytes.
 *
 * @param[in] object The tree of data objects to be encoded.
 * @param[out] tlvObjectBuffer The address of the block of memory where to write the bytes of the encoded data object.
 * @param[in] objectBufferSize The size in bytes of the given block of memory to output the encoded data object.
 *
 * @return On success returns 0
 * @return In failing, returns -1
 *
 */
int BTLV_encodeTlvObject(const BTLV_DataObject* const object, uint8_t* const tlvObjectBuffer, const size_t objectBufferSize);

/**
 * @brief Standard data object printing function.
 *
 * Prints a given data object in a default style. If the given object is of constructed type, prints its children and recursively children of children.
 *
 * @param[in] object Data object to be printed.
 *
 * @return On success returns 0
 * @return In failing, returns -1
 *
 */
int BTLV_printObject(const BTLV_DataObject* const object);

/**
 * @brief Navigates through a tree of data objects using the depth first approach.
 *
 * For each data object in the tree the print callback is called passing a reference to the data object. The return of the callback guide the behavior of
 * the navigation algorithm.
 *
 * @param[in] object Data object to be navigated.
 * @param[out] printObjectCallback callback to be called to print each data object of data object tree.
 *
 */
void BTLV_depthFirstNavigateObject(const BTLV_DataObject* const object, const BTLV_objectPrintCallback printObjectCallback);

/**
 * @brief Navigates through data objects encoded in a block of bytes
 *
 * For each data object decoded the print callback is called. The return of the callback guide the behavior of the decoding algorithm.
 *
 * @param[in] tlvObjectBuffer buffer to be decoded data object by data object.
 * @param[in] objectBufferSize size in bytes of given buffer.
 * @param[out] printObjectCallback callback to be called to print each data object of data object tree.
 *
 */
void BTLV_blockOfBytesNavigateObject(const uint8_t* const tlvObjectBuffer, const size_t objectBufferSize, const BTLV_objectPrintCallback printObjectCallback);

/**
 * @brief Try to recusively free data object properly and safely.
 *
 * @param object Reference to the data object that must be deallocated.
 *
 */
void BTLV_destroyTlvObject(BTLV_DataObject* const object);

#ifdef __cplusplus
}
#endif

#endif // #ifndef BTLV_LIB_BERTLV_H