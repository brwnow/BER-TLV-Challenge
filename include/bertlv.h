#ifndef BTLV_LIB_BERTLV_H
#define BTLV_LIB_BERTLV_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BTLV_TAG_MAX_SIZE 3

typedef enum {
    BTLV_CLASS_UNIVERSAL = 0,
    BTLV_CLASS_APPLICATION,
    BTLV_CLASS_CONTEXT_SPECIFIC,
    BTLV_CLASS_PRIVATE
} BTLV_ObjectClass;

typedef enum {
    BTLV_PRIMITIVE = 0,
    BTLV_CONSTRUCTED
} BTLV_ObjectType;

typedef struct _DataObject {
    BTLV_ObjectClass class;
    BTLV_ObjectType type;
    uint8_t tag[BTLV_TAG_MAX_SIZE];
    size_t tagSize;
    size_t length;
    uint32_t childObjectsCount;

    union {
        uint8_t *value;
        struct _DataObject *children;
    };
} BTLV_DataObject;

typedef enum {
    BTLV_DEPTH_NAVIGATION_STEP_INTO,
    BTLV_DEPTH_NAVIGATION_STEP_OVER,
    BTLV_DEPTH_NAVIGATION_STEP_OUT
} BTLV_ObjectPrintCallbackRetVal;

typedef void (*BTLV_objectPrintCallback)(const BTLV_DataObject* const, const uint8_t nestingLevel);

const char* BTLV_getVersion(void);

BTLV_DataObject* BTLV_decodeTlvObject(const uint8_t* const tlvObjectBuffer, const size_t objectBufferSize);

int BTLV_encodeTlvObject(const BTLV_DataObject* const object, uint8_t* const tlvObjectBuffer, const size_t objectBufferSize);

void BTLV_printObject(const BTLV_DataObject* const object);

void BTLV_depthFirstNavigateObject(const BTLV_DataObject* const object, const BTLV_objectPrintCallback printObjectCallback);

void BTLV_destroyTlvObject(BTLV_DataObject* const object);

#ifdef __cplusplus
}
#endif

#endif // #ifndef BTLV_LIB_BERTLV_H