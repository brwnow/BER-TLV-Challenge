#include "btlv_test_setups.h"

#include <stdlib.h>

#include "btlvConfig.h"
#include "bertlv.h"


DECLARE_SETUP_FUNC(btlvVersionString) {
    static char *btlvVersionStr = BTLV_VERSION_MAJOR "." BTLV_VERSION_MINOR "." BTLV_VERSION_PATCH;

    FIXTURE_CREATE(1);
    FIXTURE_INDEX(0) = btlvVersionStr;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvVersionString) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvPrimitiveDataObject) {
    BTLV_DataObject *dataObject = malloc(sizeof(BTLV_DataObject));

    dataObject->class = BTLV_CLASS_PRIVATE;
    dataObject->type = BTLV_PRIMITIVE;
    dataObject->tag[0] = 0xFF;
    dataObject->tagSize = 1;
    dataObject->length = 1;
    dataObject->childObjectsCount = 0;
    dataObject->valueField.value = malloc(sizeof(uint8_t));
    dataObject->valueField.value[0] = 0x75;

    FIXTURE_CREATE(1);
    FIXTURE_INDEX(0) = dataObject;
    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvPrimitiveDataObject) {
    // dataObject is meant to be deleted in the test, so free only fixture
    free(fixture); 
}

DECLARE_SETUP_FUNC(btlvConstructedDataObject) {
    BTLV_DataObject *dataObject = malloc(sizeof(BTLV_DataObject));

    dataObject->class = BTLV_CLASS_PRIVATE;
    dataObject->type = BTLV_CONSTRUCTED;
    dataObject->tag[0] = 0xFF;
    dataObject->tagSize = 1;
    dataObject->length = 1;
    dataObject->childObjectsCount = 2;
    dataObject->valueField.children = malloc(sizeof(BTLV_DataObject) * dataObject->childObjectsCount);

    BTLV_DataObject *child1 = dataObject->valueField.children;
    BTLV_DataObject *child2 = dataObject->valueField.children + 1;

    child1->class = BTLV_CLASS_PRIVATE;
    child1->type = BTLV_PRIMITIVE;
    child1->tag[0] = 0xFA;
    child1->tagSize = 1;
    child1->length = 3;
    child1->childObjectsCount = 0;
    child1->valueField.value = malloc(sizeof(uint8_t) * 3);
    child1->valueField.value[0] = 0xAA;
    child1->valueField.value[1] = 0x12;
    child1->valueField.value[2] = 0xC3;

    child2->class = BTLV_CLASS_CONTEXT_SPECIFIC;
    child2->type = BTLV_PRIMITIVE;
    child2->tag[0] = 0xC7;
    child2->tagSize = 1;
    child2->length = 1;
    child2->childObjectsCount = 0;
    child2->valueField.value = malloc(sizeof(uint8_t));
    child2->valueField.value[0] = 0x85;

    FIXTURE_CREATE(1);
    FIXTURE_INDEX(0) = dataObject;
    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvConstructedDataObject) {
    // dataObject is meant to be deleted in the test, so free only fixture
    free(fixture); 
}