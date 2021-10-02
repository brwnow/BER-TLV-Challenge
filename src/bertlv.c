#include "bertlv.h"

const char* BTLV_getVersion(void)
{
    return "0.0.0";
}

BTLV_DataObject* BTLV_decodeTlvObject(const uint8_t* const tlvObjectBuffer, const size_t objectBufferSize)
{
    (void)tlvObjectBuffer;
    (void)objectBufferSize;

    return NULL;
}

int BTLV_encodeTlvObject(const BTLV_DataObject* const object, uint8_t* const tlvObjectBuffer, const size_t objectBufferSize)
{
    (void)object;
    (void)tlvObjectBuffer;
    (void)objectBufferSize;

    return -1;
}

void BTLV_printObject(const BTLV_DataObject* const object)
{
    (void)object;
}

void BTLV_depthFirstNavigateObject(const BTLV_DataObject* const object, const BTLV_objectPrintCallback printObjectCallback)
{
    (void)object;
    (void)printObjectCallback;
}

void BTLV_destroyTlvObject(BTLV_DataObject* const object)
{
    (void)object;
}