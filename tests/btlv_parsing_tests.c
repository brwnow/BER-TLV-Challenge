#include "testsdefs.h"

#include "bertlv.h"
#include "btlv_test_helpers.h"
#include "btlv_test_setups.h"
#include "btlv_tests.h"
#include "tlvparser.h"

DECLARE_TEST_FUNC(parseTagFieldClass)
{
    const uint8_t *const tagByte = FIXTURE_INDEX(0);
    const BTLV_ObjectClass expectedResult = *(BTLV_ObjectClass *)(FIXTURE_INDEX(1));
    BTLV_DataObject outputParsedTag;

    BTLV_ReturnCode ret = BTLV_tagFieldParse(tagByte, 1, &outputParsedTag);

    munit_assert_int(ret, ==, BTLV_RET_OK);
    munit_assert_uint8(outputParsedTag.tag[0], ==, *tagByte);
    munit_assert_size(outputParsedTag.tagSize, ==, 1);
    munit_assert_int(outputParsedTag.class, ==, expectedResult);

    return MUNIT_OK;
}

DECLARE_TEST_FUNC(parseTagFieldType)
{
    const uint8_t *const tagByte = FIXTURE_INDEX(0);
    const BTLV_ObjectType expectedResult = *(BTLV_ObjectType *)(FIXTURE_INDEX(1));
    BTLV_DataObject outputParsedTag;

    munit_assert_int(BTLV_tagFieldParse(tagByte, 1, &outputParsedTag), ==, BTLV_RET_OK);
    munit_assert_uint8(outputParsedTag.tag[0], ==, *tagByte);
    munit_assert_size(outputParsedTag.tagSize, ==, 1);
    munit_assert_int(outputParsedTag.type, ==, expectedResult);

    return MUNIT_OK;
}

DECLARE_TEST_FUNC(parseLengthField)
{
    const uint8_t *const lengthBytes = FIXTURE_INDEX(0);
    const size_t fieldSize = *(size_t *)(FIXTURE_INDEX(1));
    const BTLV_ReturnCode expectedRet = *(BTLV_ReturnCode *)(FIXTURE_INDEX(2));
    const size_t expectedLength = *(size_t *)(FIXTURE_INDEX(3));
    const size_t expectedBytesCount = *(size_t *)(FIXTURE_INDEX(4));

    size_t outputLength;
    size_t outputBytesCount;

    munit_assert_int(BTLV_lengthFieldParse(lengthBytes, fieldSize, &outputLength, &outputBytesCount), ==, expectedRet);
    munit_assert_size(outputLength, ==, expectedLength);
    munit_assert_size(outputBytesCount, ==, expectedBytesCount);

    return MUNIT_OK;
}

DECLARE_TEST_FUNC(decodeSuccessfullySingleElement)
{
    const uint8_t *const objectBytes = FIXTURE_INDEX(0);
    const size_t objectSize = *(size_t *)(FIXTURE_INDEX(1));
    const BTLV_DataObject *const expectedResult = FIXTURE_INDEX(2);

    BTLV_DataObject *decodedObject;
    size_t arrayLength = 0;

    BTLV_ReturnCode ret = BTLV_decodeTlvObject(objectBytes, objectSize, &decodedObject, &arrayLength);

    munit_assert_int(ret, ==, BTLV_RET_OK);
    munit_assert_size(arrayLength, ==, 1);
    munit_assert_int(compareBtlvDataObjects(decodedObject, expectedResult), ==, true);

    BTLV_destroyTlvObjectArray(decodedObject, 1);

    return MUNIT_OK;
}

DECLARE_TEST_FUNC(decodeBadEncodedSingleElement)
{
    const uint8_t *const objectBytes = FIXTURE_INDEX(0);
    const size_t objectSize = *(size_t *)(FIXTURE_INDEX(1));

    BTLV_DataObject *decodedObject;
    size_t arrayLength = 0;

    // Checking how the function handles buffers that ends before the data object reachs its
    // last tag. Starting from a buffer slightly smaller than the real data object (1 byte
    // smaller) and continuing reducing the buffer until size 0 bytes
    for (int decrementalObjectSize = (int)objectSize - 1; decrementalObjectSize >= 0; --decrementalObjectSize) {
        BTLV_ReturnCode ret = BTLV_decodeTlvObject(objectBytes, decrementalObjectSize, &decodedObject, &arrayLength);

        munit_assert_int(ret, ==, BTLV_BAD_TLV_ENCODING);
        munit_assert_ptr_null(decodedObject);
    }

    return MUNIT_OK;
}

static MunitTest btlvParsingTests[] = {
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_tagFieldParseUniversalClass",
                                   parseTagFieldClass,
                                   btlvUniversalClassDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_tagFieldParseApplicationClass",
                                   parseTagFieldClass,
                                   btlvApplicationClassDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_tagFieldParseContextSpecificClass",
                                   parseTagFieldClass,
                                   btlvContextSpecificClassDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_tagFieldParsePrivateClass", parseTagFieldClass, btlvPrivateClassDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_tagFieldParsePrimitiveType",
                                   parseTagFieldType,
                                   btlvTagPrimitiveTypeDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_tagFieldParseConstructedType",
                                   parseTagFieldType,
                                   btlvTagConstructedTypeDataObject),

    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_lengthFieldParseSingleByte",
                                   parseLengthField,
                                   btlvLengthFieldSingleByteDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_lengthFieldParseTwoBytes",
                                   parseLengthField,
                                   btlvLengthFieldTwoBytesDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_lengthFieldParseShortIntWide",
                                   parseLengthField,
                                   btlvLengthFieldFillShortIntDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_lengthFieldParseForcedOverflow",
                                   parseLengthField,
                                   btlvLengthFieldForceOverflowDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_lengthFieldParseForcedBadEncoded",
                                   parseLengthField,
                                   btlvLengthFieldForceBadEncodedDataObject),

    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectArraySingleByteTag",
                                   decodeSuccessfullySingleElement,
                                   btlvSingleByteTagPrimitiveDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectArrayMultiByteTag",
                                   decodeSuccessfullySingleElement,
                                   btlvMultiByteTagPrimitiveDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectArraySingleByteLength",
                                   decodeSuccessfullySingleElement,
                                   btlvSingleByteLenPrimitiveDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectArrayMultiByteLength",
                                   decodeSuccessfullySingleElement,
                                   btlvMultiByteLenPrimitiveDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectArraySingleNested",
                                   decodeSuccessfullySingleElement,
                                   btlvSingleNestingByteBlockConstructedDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectArrayMultiNested",
                                   decodeSuccessfullySingleElement,
                                   btlvMultiNestingByteBlockConstructedDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectArrayBadEncodedPrimitive",
                                   decodeBadEncodedSingleElement,
                                   btlvBadEncodedPrimitiveDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectArrayBadEncodedConstructed",
                                   decodeBadEncodedSingleElement,
                                   btlvBadEncodedConstructedDataObject),
    TEST_FUNC_ARRAY_END};

static MunitSuite btlvParsingTestsSuite = {"/parsing", btlvParsingTests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

MunitSuite
btlvParsingTestsGetSuite(void)
{
    return btlvParsingTestsSuite;
}