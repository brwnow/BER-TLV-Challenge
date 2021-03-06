/**
 * @file bertlv.h
 * @brief BER-TLV objects encoding/decoding API.
 *
 * API for working with BER-TLV data objects. Functions to encode, decode and help on printing formatted BER-TLV object
 * fields and data.
 *
 */

#ifndef BTLV_LIB_BERTLV_H
#define BTLV_LIB_BERTLV_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BTLV_TAG_MAX_SIZE 2

#define BTLV_ERRORCODE_STARTING_VALUE -1000
#define BTLV_WARNINGCODE_STARTING_VALUE 1

// Heuristic for initial array size when amount of element will be discovered
// during array fill up. The array me be reallocated for more space
#define BTLV_ARRAY_INITIAL_SIZE_HEURISTIC 4

/**
 * @brief Return codes for BTLV Lib functions
 *
 * This enumeration is common to the whole BTLV lib API. When a function works fine, BTLV_RET_OK is the enumerator to
 * use, and its value is zero for a reason, all error codes are negative, and all warning codes are greater than zero,
 * so this way it's possible to check if it was error, warning or totally success in a easy way, not knowing all
 * possible return codes. This feature gives a lot of power to the lib's user, making it quite easy to take decisions
 * based on a behavioral interpretation of return codes.
 *
 */
typedef enum {
    BTLV_RET_OK = 0, /**< Function exectued succesfully */

    BTLV_GENERIC_ERROR = BTLV_ERRORCODE_STARTING_VALUE, /**< An error occurred with no special interpretation. */
    BTLV_INVALID_PARAMETER, /**< One or more parameters have invalid value. For example passin NULL to a parameter that
                               cannot be NULL. */
    BTLV_MEMORY_NOT_ENOUGH, /**< Function failed due to lack of free memory. It does happen for those functions that
                               need to allocate heap memory. */
    BTLV_SMALL_BUFFER,      /**< Output buffer was not enough to encode the whole data object. */
    BTLV_TYPE_OVERFLOW,     /**< An overflow of an integer type has occurred during TLV parsing. */
    BTLV_BAD_TLV_ENCODING,  /**< Given encoded TLV byte block is encoded incorrectly. */
    BTLV_BAD_TLV_STRUCTURE, /**< Given BTLV_DataObject has an invalid structure for a TLV Data Object. */
    BTLV_OUTPUT_STREAM_MISSING, /**< No output stream available during printing function execution. */
    BTLV_BAD_CALLBACK_COMMAND,  /**< Some callback function returned an expected control code. */

    BTLV_PRINTING_BYTES_LOST = BTLV_WARNINGCODE_STARTING_VALUE /**< Some bytes were lost during printing operation.
                                                                  Output text is probably broken. */
} BTLV_ReturnCode;

/**
 * @brief Class of BER-TLV data object
 *
 */
typedef enum {
    BTLV_CLASS_UNIVERSAL = 0,    /**< Universal class */
    BTLV_CLASS_APPLICATION,      /**< Application class */
    BTLV_CLASS_CONTEXT_SPECIFIC, /**< Context-specific class */
    BTLV_CLASS_PRIVATE           /**< Private class */
} BTLV_ObjectClass;

/**
 * @brief Type of BER-TLV data object
 *
 */
typedef enum {
    BTLV_PRIMITIVE = 0, /**< Value field holds a number instead of sub data objects */
    BTLV_CONSTRUCTED    /**< Value field holds sub data objects */
} BTLV_ObjectType;

/**
 * @brief Return codes for BTLV_objectPrintCallback
 *
 * BTLV_objectPrintCallback can control the navigation through tree of data objects returning next action that must be
 * performed. This way its possible to ignore completly some data objects and its children or stop at certain data
 * object and return to the parent data object, ignoring subsequent data object in current nesting level. STEP_INTO is
 * the control to go further on nesting if current data object is of type constructed.
 *
 */
typedef enum {
    BTLV_DEPTH_NAVIGATION_STEP_INTO, /**< Go further on nesting level when navigating through a data objects tree */
    BTLV_DEPTH_NAVIGATION_STEP_OVER, /**< Ignores nesting of current data object if its of type constructed */
    BTLV_DEPTH_NAVIGATION_STEP_OUT,  /**< Ignores current data object nesting and subsequent data objects at current
                                          nesting level */
    BTLV_DEPTH_NAVIGATION_HALT       /**< Interrupts the whole naviation at the point that halt was returned */
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
    BTLV_ObjectClass class;         /**< Class of data object */
    BTLV_ObjectType type;           /**< Type of data object */
    uint8_t tag[BTLV_TAG_MAX_SIZE]; /**< Content data of TAG */
    size_t tagSize;                 /**< TAG content data size in bytes */
    size_t length;                  /**< Length of value field in bytes */
    size_t childObjectsCount;       /**< For constructed data objects, amount of children data objects */

    union {
        uint8_t *value;               /**< Pointer to bytes of value field */
        struct _DataObject *children; /**< Array of children data objects */
    } valueField;
} BTLV_DataObject;

/**
 * @brief Callback for printing data objects during a navigation through a tree of data objects
 *
 */
typedef BTLV_ObjectPrintCallbackRetVal (*BTLV_objectPrintCallback)(const BTLV_DataObject *const object,
                                                                   const uint8_t nestingLevel);

/**
 * @brief Gets the string of BTLV lib full version
 *
 * @return Returns a string representing the BTLV lib version formatted as MAJOR.MINOR.PATCH
 *
 */
const char *
BTLV_getVersion(void);

/**
 * @brief Decode a BER-TLV data object to an array of Data Objects Trees
 *
 * Receives a BER-TLV data object encoded as block of bytes and decode it to several trees of
 * BTLV_DataObject representing all the information encoded passed. The output parameter tlvDataObjectsArray
 * is an array of tree roots.
 *
 * @param[in] tlvObjectBuffer The address of the BER-TLV data object block of bytes in memory.
 * @param[in] objectBufferSize Size of the data object block of bytes.
 * @param[out] decodedObject Output parameter where to return the address of decoded data object. Its an array
 * of BTLV_DataObject, each data object representing a tree. In case of failing to decode the object, outputs NULL.
 * @param[out] tlvDataObjectsCount Output parameter where to return the amount of elements in the array returned
 * through parameter decodedObject. In case of failing, returns zero.
 *
 * @return Returns BTLV_RET_OK on success.
 * @return Returns BTLV_INVALID_PARAMETER if some problem is found on given arguments.
 * @return Returns BTLV_MEMORY_NOT_ENOUGH if it fails allocating memory during decoding of TLV object byte block.
 * @return Returns BTLV_BAD_TLV_ENCODING if input TLV object byte block is bad encoded and the function
 * fails to decode it.
 * @return Returns BTLV_TYPE_OVERFLOW if an integer type overflow occur during the parsing of given TLV data object.
 *
 */
BTLV_ReturnCode
BTLV_decodeTlvObject(const uint8_t *const tlvObjectBuffer,
                     const size_t objectBufferSize,
                     BTLV_DataObject **tlvDataObjectsArray,
                     size_t *const tlvDataObjectsCount);

/**
 * @brief Standard data object printing function.
 *
 * Prints a given data object in a default style. If the given object is of constructed type, prints its children and
 * recursively children of children.
 *
 * @param[in] object Data object to be printed.
 *
 * @return Returns BTLV_RET_OK on success.
 * @return Returns BTLV_INVALID_PARAMETER if some problem is found on given arguments.
 *
 */
BTLV_ReturnCode
BTLV_printObject(const BTLV_DataObject *const object);

/**
 * @brief Standard data object array printing function.
 *
 * Prints a given data object array in a default style. Basically calls BTLV_printObject
 * for each data object in given array.
 *
 * @param[in] object Data object array to be printed.
 * @param[in] arraySize Number of elements of given array.
 *
 * @return Returns BTLV_RET_OK on success.
 * @return Returns BTLV_INVALID_PARAMETER if some problem is found on given arguments.
 *
 */
BTLV_ReturnCode
BTLV_printObjectArray(const BTLV_DataObject *const objects, const size_t arraySize);

/**
 * @brief Navigates through a tree of data objects using the depth first approach.
 *
 * For each data object in the tree the print callback is called passing a reference to the data object. The return of
 * the callback guide the behavior of the navigation algorithm.
 *
 * @param[in] object Data object to be navigated.
 * @param[out] printObjectCallback callback to be called to print each data object of data object tree.
 *
 * @return Returns BTLV_RET_OK on success.
 * @return Returns BTLV_INVALID_PARAMETER if some problem is found on given arguments.
 * @return Returns BTLV_BAD_TLV_STRUCTURE if input TLV object tree is bad constructed and it's impossible to navigate
 * correctly through it.
 * @return Returns BTLV_BAD_CALLBACK_COMMAND if callback function returns a control code that is unexpected.
 *
 */
BTLV_ReturnCode
BTLV_depthFirstNavigateObject(const BTLV_DataObject *const object, const BTLV_objectPrintCallback printObjectCallback);

/**
 * @brief Try to recusively free data object properly and safely.
 *
 * The object itself is not deallocated.
 *
 * @param object Reference to the data object that must be destroyed.
 *
 */
void
BTLV_destroyTlvObject(BTLV_DataObject *const object);

/**
 * @brief Try to destroy each object of given array and then finally destroy the array
 *
 * @param objectArray Reference to the data objectarray that must be deallocated.
 * @param elementCount Number of elements in given array
 *
 */
void
BTLV_destroyTlvObjectArray(BTLV_DataObject *const objectArray, const size_t elementCount);

#ifdef __cplusplus
}
#endif

#endif // #ifndef BTLV_LIB_BERTLV_H