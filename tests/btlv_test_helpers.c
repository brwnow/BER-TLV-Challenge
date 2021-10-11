#include "btlv_test_helpers.h"

#include <string.h>

bool
compareBtlvDataObjects(const BTLV_DataObject* const tlvObjectA, const BTLV_DataObject* const tlvObjectB)
{
    if(tlvObjectA == tlvObjectB)
        return true;

    if(tlvObjectA == NULL || tlvObjectB == NULL)
        return false;

    if( tlvObjectA->class != tlvObjectB->class ||
        tlvObjectA->type != tlvObjectB->type ||
        tlvObjectA->tagSize != tlvObjectB->tagSize ||
        tlvObjectA->length != tlvObjectB->length ||
        tlvObjectA->childObjectsCount != tlvObjectB->childObjectsCount ||
        memcmp(tlvObjectA->tag, tlvObjectB->tag, tlvObjectA->tagSize) != 0)
        return false;

    if(tlvObjectA->type == BTLV_PRIMITIVE) {
        return memcmp(tlvObjectA->valueField.value, tlvObjectB->valueField.value, tlvObjectA->length) == 0;
    } else {
        for(size_t i = 0; i < tlvObjectA->childObjectsCount; ++i) {
            if(!compareBtlvDataObjects(tlvObjectA->valueField.children + i, tlvObjectB->valueField.children + i))
                return false;
        }

        return true;
    }
}