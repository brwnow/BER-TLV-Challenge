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

DECLARE_SETUP_FUNC(btlvUniversalClassDataObject) {
    static uint8_t tagUniversalClass = 0x21;
    static BTLV_ObjectClass expectedResult = BTLV_CLASS_UNIVERSAL;

    FIXTURE_CREATE(2);
    FIXTURE_INDEX(0) = &tagUniversalClass;
    FIXTURE_INDEX(1) = &expectedResult;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvUniversalClassDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvApplicationClassDataObject) {
    static uint8_t tagUniversalClass = 0x61;
    static BTLV_ObjectClass expectedResult = BTLV_CLASS_APPLICATION;

    FIXTURE_CREATE(2);
    FIXTURE_INDEX(0) = &tagUniversalClass;
    FIXTURE_INDEX(1) = &expectedResult;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvApplicationClassDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvContextSpecificClassDataObject) {
    static uint8_t tagUniversalClass = 0xA1;
    static BTLV_ObjectClass expectedResult = BTLV_CLASS_CONTEXT_SPECIFIC;

    FIXTURE_CREATE(2);
    FIXTURE_INDEX(0) = &tagUniversalClass;
    FIXTURE_INDEX(1) = &expectedResult;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvContextSpecificClassDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvPrivateClassDataObject) {
    static uint8_t tagUniversalClass = 0xE1;
    static BTLV_ObjectClass expectedResult = BTLV_CLASS_PRIVATE;

    FIXTURE_CREATE(2);
    FIXTURE_INDEX(0) = &tagUniversalClass;
    FIXTURE_INDEX(1) = &expectedResult;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvPrivateClassDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvTagPrimitiveTypeDataObject) {
    static uint8_t tagPrimitiveType = 0xC1;
    static BTLV_ObjectType expectedResult = BTLV_PRIMITIVE;

    FIXTURE_CREATE(2);
    FIXTURE_INDEX(0) = &tagPrimitiveType;
    FIXTURE_INDEX(1) = &expectedResult;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvTagPrimitiveTypeDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvTagConstructedTypeDataObject) {
    static uint8_t tagConstructedType = 0xE1;
    static BTLV_ObjectType expectedResult = BTLV_CONSTRUCTED;

    FIXTURE_CREATE(2);
    FIXTURE_INDEX(0) = &tagConstructedType;
    FIXTURE_INDEX(1) = &expectedResult;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvTagConstructedTypeDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvLengthFieldSingleByteDataObject) {
    static uint8_t lengthByte = 0x7F;
    static size_t fieldSize = 1;
    static BTLV_ReturnCode expectedRet = BTLV_RET_OK;
    static size_t expectedLength = 127;
    static size_t expectedBytesCount = 1;

    FIXTURE_CREATE(3);
    FIXTURE_INDEX(0) = &lengthByte;
    FIXTURE_INDEX(1) = &fieldSize;
    FIXTURE_INDEX(2) = &expectedRet;
    FIXTURE_INDEX(3) = &expectedLength;
    FIXTURE_INDEX(4) = &expectedBytesCount;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvLengthFieldSingleByteDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvLengthFieldTwoBytesDataObject) {
    // buffer with filler bytes because real TLV with high length value have a lot of extra bytes
    static uint8_t lengthByte[] = { 0x81, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    static size_t fieldSize = 2;
    static BTLV_ReturnCode expectedRet = BTLV_RET_OK;
    static size_t expectedLength = 128;
    static size_t expectedBytesCount = 2;

    FIXTURE_CREATE(3);
    FIXTURE_INDEX(0) = &lengthByte;
    FIXTURE_INDEX(1) = &fieldSize;
    FIXTURE_INDEX(2) = &expectedRet;
    FIXTURE_INDEX(3) = &expectedLength;
    FIXTURE_INDEX(4) = &expectedBytesCount;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvLengthFieldTwoBytesDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvLengthFieldFillShortIntDataObject) {
    // buffer with filler bytes because real TLV with high length value have a lot of extra bytes
    static uint8_t lengthByte[] = { 0x82, 0xAA, 0x55, 0xDE, 0x6F, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    static size_t fieldSize = 5;
    static BTLV_ReturnCode expectedRet = BTLV_RET_OK;
    static size_t expectedLength = 43605;
    static size_t expectedBytesCount = 3;

    FIXTURE_CREATE(3);
    FIXTURE_INDEX(0) = &lengthByte;
    FIXTURE_INDEX(1) = &fieldSize;
    FIXTURE_INDEX(2) = &expectedRet;
    FIXTURE_INDEX(3) = &expectedLength;
    FIXTURE_INDEX(4) = &expectedBytesCount;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvLengthFieldFillShortIntDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvLengthFieldForceOverflowDataObject) {
    // buffer with filler bytes because real TLV with high length value have a lot of extra bytes
    static uint8_t lengthByte[] = { 0x89, 0xFE, 0x45, 0x32, 0x99, 0x5D, 0xA3, 0xF1, 0x89, 0x44,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    static size_t fieldSize = sizeof(lengthByte) / sizeof(uint8_t);
    static BTLV_ReturnCode expectedRet = BTLV_TYPE_OVERFLOW;
    static size_t expectedBytesCount = 10;

#if defined(__x86_64__) || defined(__ppc64__)
    static size_t expectedLength = 0x4532995DA3F18944;
#else
    static size_t expectedLength = 0xA3F18944;
#endif

    FIXTURE_CREATE(3);
    FIXTURE_INDEX(0) = &lengthByte;
    FIXTURE_INDEX(1) = &fieldSize;
    FIXTURE_INDEX(2) = &expectedRet;
    FIXTURE_INDEX(3) = &expectedLength;
    FIXTURE_INDEX(4) = &expectedBytesCount;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvLengthFieldForceOverflowDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvLengthFieldForceBadEncodedDataObject) {
    static uint8_t lengthByte[] = { 0x84, 0xAA, 0x55, 0xDE, 0x6F };
    static size_t fieldSize = 3;
    static BTLV_ReturnCode expectedRet = BTLV_BAD_TLV_ENCODING;
    static size_t expectedLength = 0;
    static size_t expectedBytesCount = 3;

    FIXTURE_CREATE(3);
    FIXTURE_INDEX(0) = &lengthByte;
    FIXTURE_INDEX(1) = &fieldSize;
    FIXTURE_INDEX(2) = &expectedRet;
    FIXTURE_INDEX(3) = &expectedLength;
    FIXTURE_INDEX(4) = &expectedBytesCount;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvLengthFieldForceBadEncodedDataObject) {
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

DECLARE_SETUP_FUNC(btlvConstructedDataObjectArray) {
    static size_t arraySize = 2;
    BTLV_DataObject *dataObjectArray = malloc(sizeof(BTLV_DataObject) * arraySize);

    BTLV_DataObject *dataObject = &(dataObjectArray[0]);
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

    BTLV_DataObject *dataObject2 = &(dataObjectArray[1]);

    dataObject2->class = BTLV_CLASS_PRIVATE;
    dataObject2->type = BTLV_PRIMITIVE;
    dataObject2->tag[0] = 0xFF;
    dataObject2->tagSize = 1;
    dataObject2->length = 1;
    dataObject2->childObjectsCount = 0;
    dataObject2->valueField.value = malloc(sizeof(uint8_t));
    dataObject2->valueField.value[0] = 0x75;

    FIXTURE_CREATE(2);
    FIXTURE_INDEX(0) = dataObjectArray;
    FIXTURE_INDEX(1) = &arraySize;
    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvConstructedDataObjectArray) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvSingleByteTagPrimitiveDataObject) {
    static uint8_t appControlTag[] = { 0xD5, 0x00 };
    static size_t byteBlockSize = sizeof(appControlTag);
    static BTLV_DataObject expectedResult = {
        .class = BTLV_CLASS_PRIVATE,
        .type = BTLV_PRIMITIVE,
        .tag = { 0xD5 },
        .tagSize = 1,
        .length = 0,
        .childObjectsCount = 0,
        .valueField.value = NULL
    };

    FIXTURE_CREATE(3);
    FIXTURE_INDEX(0) = appControlTag;
    FIXTURE_INDEX(1) = &byteBlockSize;
    FIXTURE_INDEX(2) = &expectedResult;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvSingleByteTagPrimitiveDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvMultiByteTagPrimitiveDataObject) {
    static uint8_t issuerActionCodeOnlineTag[] = { 0x9F, 0x0F, 0x00 };
    static size_t byteBlockSize = sizeof(issuerActionCodeOnlineTag);
    static BTLV_DataObject expectedResult = {
        .class = BTLV_CLASS_CONTEXT_SPECIFIC,
        .type = BTLV_PRIMITIVE,
        .tag = { 0x9F, 0x0F },
        .tagSize = 2,
        .length = 0,
        .childObjectsCount = 0,
        .valueField.value = NULL
    };

    FIXTURE_CREATE(3);
    FIXTURE_INDEX(0) = issuerActionCodeOnlineTag;
    FIXTURE_INDEX(1) = &byteBlockSize;
    FIXTURE_INDEX(2) = &expectedResult;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvMultiByteTagPrimitiveDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvSingleByteLenPrimitiveDataObject) {
    static uint8_t transacCurrExp[] = { 0x5F, 0x36, 0x01, 0x04 };
    static size_t byteBlockSize = sizeof(transacCurrExp);
    static uint8_t value[] = { 0x04 };
    static BTLV_DataObject expectedResult = {
        .class = BTLV_CLASS_APPLICATION,
        .type = BTLV_PRIMITIVE,
        .tag = { 0x5F, 0x36 },
        .tagSize = 2,
        .length = 1,
        .childObjectsCount = 0,
        .valueField.value = value
    };

    FIXTURE_CREATE(3);
    FIXTURE_INDEX(0) = transacCurrExp;
    FIXTURE_INDEX(1) = &byteBlockSize;
    FIXTURE_INDEX(2) = &expectedResult;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvSingleByteLenPrimitiveDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvMultiByteLenPrimitiveDataObject) {
    static uint8_t appLabel[] = { 0x50, 0x04, 0x56, 0x49, 0x53, 0x41 };
    static size_t byteBlockSize = sizeof(appLabel);
    static uint8_t value[] = { 0x56, 0x49, 0x53, 0x41 };
    static BTLV_DataObject expectedResult = {
        .class = BTLV_CLASS_APPLICATION,
        .type = BTLV_PRIMITIVE,
        .tag = { 0x50 },
        .tagSize = 1,
        .length = 4,
        .childObjectsCount = 0,
        .valueField.value = value
    };

    FIXTURE_CREATE(3);
    FIXTURE_INDEX(0) = appLabel;
    FIXTURE_INDEX(1) = &byteBlockSize;
    FIXTURE_INDEX(2) = &expectedResult;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvMultiByteLenPrimitiveDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvSingleNestingByteBlockConstructedDataObject) {
    static uint8_t tlvObject[] = { 0xE1, 0x0B, 0xC1, 0x03, 0x01, 0x02, 0x03,
                                   0xC2, 0x00, 0xC3, 0x02, 0xAA, 0xBB };
    static size_t byteBlockSize = 13;

    static uint8_t child1_value[] = { 0x01, 0x02, 0x03 };
    static uint8_t child3_value[] = { 0xAA, 0xBB };

    static BTLV_DataObject children[] = {
        { // child 1
            .class = BTLV_CLASS_PRIVATE,
            .type = BTLV_PRIMITIVE,
            .tag = { 0xC1 },
            .tagSize = 1,
            .length = 3,
            .childObjectsCount = 0,
            .valueField.value = child1_value
        },
        { // child 2
            .class = BTLV_CLASS_PRIVATE,
            .type = BTLV_PRIMITIVE,
            .tag = { 0xC2 },
            .tagSize = 1,
            .length = 0,
            .childObjectsCount = 0,
            .valueField.value = NULL
        },
        { // child 3
            .class = BTLV_CLASS_PRIVATE,
            .type = BTLV_PRIMITIVE,
            .tag = { 0xC3 },
            .tagSize = 1,
            .length = 2,
            .childObjectsCount = 0,
            .valueField.value = child3_value
        }
    };

    static BTLV_DataObject expectedResult = {
        .class = BTLV_CLASS_PRIVATE,
        .type = BTLV_CONSTRUCTED,
        .tag = { 0xE1 },
        .tagSize = 1,
        .length = 11,
        .childObjectsCount = 3,
        .valueField.children = children
    };

    FIXTURE_CREATE(3);
    FIXTURE_INDEX(0) = tlvObject;
    FIXTURE_INDEX(1) = &byteBlockSize;
    FIXTURE_INDEX(2) = &expectedResult;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvSingleNestingByteBlockConstructedDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvMultiNestingByteBlockConstructedDataObject) {
    static uint8_t fciTemplate[] = {    0x6F, 0x1A, 0x84, 0x0E, 0x31, 0x50, 0x41, 0x59, 0x2E, 
                                        0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31,
                                        0xA5, 0x08, 0x88, 0x01, 0x02, 0x5F, 0x2D, 0x02, 0x65,
                                        0x6E };
    static size_t byteBlockSize = sizeof(fciTemplate);

    static uint8_t tag_0x88_value[] = { 0x02 };
    static uint8_t tag_0x5F_0x2D_value[] = { 0x65, 0x6E };

    static BTLV_DataObject tag_0xA5_children[] = {
        { // SFI
            .class = BTLV_CLASS_CONTEXT_SPECIFIC,
            .type = BTLV_PRIMITIVE,
            .tag = { 0x88 },
            .tagSize = 1,
            .length = 1,
            .childObjectsCount = 0,
            .valueField.value = tag_0x88_value
        },
        { // Lang preference
            .class = BTLV_CLASS_APPLICATION,
            .type = BTLV_PRIMITIVE,
            .tag = { 0x5F, 0x2D },
            .tagSize = 2,
            .length = 2,
            .childObjectsCount = 0,
            .valueField.value = tag_0x5F_0x2D_value
        }
    };

    static uint8_t tag_0x84_value[] = { 0x31, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59,
                                        0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31 };

    static BTLV_DataObject tag_0x6F_children[] = {
        { // Dedicated File (DF) Name
            .class = BTLV_CLASS_CONTEXT_SPECIFIC,
            .type = BTLV_PRIMITIVE,
            .tag = { 0x84},
            .tagSize = 1,
            .length = 14,
            .childObjectsCount = 0,
            .valueField.value = tag_0x84_value
        },
        { // FCI Proprietary
            .class = BTLV_CLASS_CONTEXT_SPECIFIC,
            .type = BTLV_CONSTRUCTED,
            .tag = { 0xA5 },
            .tagSize = 1,
            .length = 8,
            .childObjectsCount = 2,
            .valueField.children = tag_0xA5_children
        }
    };

    static BTLV_DataObject expectedResult = { // FCI
        .class = BTLV_CLASS_APPLICATION,
        .type = BTLV_CONSTRUCTED,
        .tag = { 0x6F },
        .tagSize = 1,
        .length = 26,
        .childObjectsCount = 2,
        .valueField.children = tag_0x6F_children
    };

    FIXTURE_CREATE(3);
    FIXTURE_INDEX(0) = fciTemplate;
    FIXTURE_INDEX(1) = &byteBlockSize;
    FIXTURE_INDEX(2) = &expectedResult;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvMultiNestingByteBlockConstructedDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvMultiRootByteBlockConstructedDataObject) {
    static uint8_t multiRoot[] = {  0x6F, 0x1A, 0x84, 0x0E, 0x31, 0x50, 0x41, 0x59, 0x2E, 
                                    0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31,
                                    0xA5, 0x08, 0x88, 0x01, 0x02, 0x5F, 0x2D, 0x02, 0x65,
                                    0x6E, 0xE1, 0x0B, 0xC1, 0x03, 0x01, 0x02, 0x03, 0xC2,
                                    0x00, 0xC3, 0x02, 0xAA, 0xBB };
    static size_t byteBlockSize = sizeof(multiRoot);

    static uint8_t tag_0x88_value[] = { 0x02 };
    static uint8_t tag_0x5F_0x2D_value[] = { 0x65, 0x6E };

    static BTLV_DataObject tag_0xA5_children[] = {
        { // SFI
            .class = BTLV_CLASS_CONTEXT_SPECIFIC,
            .type = BTLV_PRIMITIVE,
            .tag = { 0x88 },
            .tagSize = 1,
            .length = 1,
            .childObjectsCount = 0,
            .valueField.value = tag_0x88_value
        },
        { // Lang preference
            .class = BTLV_CLASS_APPLICATION,
            .type = BTLV_PRIMITIVE,
            .tag = { 0x5F, 0x2D },
            .tagSize = 2,
            .length = 2,
            .childObjectsCount = 0,
            .valueField.value = tag_0x5F_0x2D_value
        }
    };

    static uint8_t tag_0x84_value[] = { 0x31, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59,
                                        0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31 };

    static BTLV_DataObject tag_0x6F_children[] = {
        { // Dedicated File (DF) Name
            .class = BTLV_CLASS_CONTEXT_SPECIFIC,
            .type = BTLV_PRIMITIVE,
            .tag = { 0x84},
            .tagSize = 1,
            .length = 14,
            .childObjectsCount = 0,
            .valueField.value = tag_0x84_value
        },
        { // FCI Proprietary
            .class = BTLV_CLASS_CONTEXT_SPECIFIC,
            .type = BTLV_CONSTRUCTED,
            .tag = { 0xA5 },
            .tagSize = 1,
            .length = 8,
            .childObjectsCount = 2,
            .valueField.children = tag_0xA5_children
        }
    };

    static BTLV_DataObject expectedResult1 = { // FCI
        .class = BTLV_CLASS_APPLICATION,
        .type = BTLV_CONSTRUCTED,
        .tag = { 0x6F },
        .tagSize = 1,
        .length = 26,
        .childObjectsCount = 2,
        .valueField.children = tag_0x6F_children
    };

    static uint8_t child1_value[] = { 0x01, 0x02, 0x03 };
    static uint8_t child3_value[] = { 0xAA, 0xBB };

    static BTLV_DataObject children[] = {
        { // child 1
            .class = BTLV_CLASS_PRIVATE,
            .type = BTLV_PRIMITIVE,
            .tag = { 0xC1 },
            .tagSize = 1,
            .length = 3,
            .childObjectsCount = 0,
            .valueField.value = child1_value
        },
        { // child 2
            .class = BTLV_CLASS_PRIVATE,
            .type = BTLV_PRIMITIVE,
            .tag = { 0xC2 },
            .tagSize = 1,
            .length = 0,
            .childObjectsCount = 0,
            .valueField.value = NULL
        },
        { // child 3
            .class = BTLV_CLASS_PRIVATE,
            .type = BTLV_PRIMITIVE,
            .tag = { 0xC3 },
            .tagSize = 1,
            .length = 2,
            .childObjectsCount = 0,
            .valueField.value = child3_value
        }
    };

    static BTLV_DataObject expectedResult2 = {
        .class = BTLV_CLASS_PRIVATE,
        .type = BTLV_CONSTRUCTED,
        .tag = { 0xE1 },
        .tagSize = 1,
        .length = 11,
        .childObjectsCount = 3,
        .valueField.children = children
    };

    static BTLV_DataObject expectedResult[2];
    expectedResult[0] = expectedResult1;
    expectedResult[1] = expectedResult2;

    static size_t expectedArrayLength = 2;

    FIXTURE_CREATE(4);
    FIXTURE_INDEX(0) = multiRoot;
    FIXTURE_INDEX(1) = &byteBlockSize;
    FIXTURE_INDEX(2) = expectedResult;
    FIXTURE_INDEX(3) = &expectedArrayLength;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvMultiRootByteBlockConstructedDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvBadEncodedPrimitiveDataObject) {
    static uint8_t transacCurrExp[] = { 0x84, 0x0E, 0x31, 0x50, 0x41, 0x59, 0x2E, 0x53,
                                        0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31 };
    static size_t byteBlockSize = sizeof(transacCurrExp);

    FIXTURE_CREATE(2);
    FIXTURE_INDEX(0) = transacCurrExp;
    FIXTURE_INDEX(1) = &byteBlockSize;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvBadEncodedPrimitiveDataObject) {
    free(fixture);
}

DECLARE_SETUP_FUNC(btlvBadEncodedConstructedDataObject) {
    static uint8_t transacCurrExp[] = { 0x6F, 0x1A, 0x84, 0x0E, 0x31, 0x50, 0x41, 0x59, 0x2E,
                                        0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31,
                                        0xA5, 0x08, 0x88, 0x01, 0x02, 0x5F, 0x2D, 0x02, 0x65,
                                        0x6E };
    static size_t byteBlockSize = sizeof(transacCurrExp);

    FIXTURE_CREATE(2);
    FIXTURE_INDEX(0) = transacCurrExp;
    FIXTURE_INDEX(1) = &byteBlockSize;

    FIXTURE_RETURN;
}

DECLARE_TEARDOWN_FUNC(btlvBadEncodedConstructedDataObject) {
    free(fixture);
}