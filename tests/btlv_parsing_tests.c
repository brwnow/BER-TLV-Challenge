#include "testsdefs.h"

#include "bertlv.h"
#include "btlv_test_helpers.h"
#include "btlv_test_setups.h"
#include "btlv_tests.h"

DECLARE_TEST_FUNC(decodeSuccessfully)
{
    const uint8_t *const objectBytes = FIXTURE_INDEX(0);
    const size_t objectSize = *(size_t *)(FIXTURE_INDEX(1));
    const BTLV_DataObject *const expectedResult = FIXTURE_INDEX(2);

    BTLV_DataObject *decodedObject;

    BTLV_ReturnCode ret = BTLV_decodeTlvObject(objectBytes, objectSize, &decodedObject);

    munit_assert_int(ret, ==, BTLV_RET_OK);
    munit_assert_int(compareBtlvDataObjects(decodedObject, expectedResult), ==, true);

    BTLV_destroyTlvObject(decodedObject);

    return MUNIT_OK;
}

DECLARE_TEST_FUNC(decodeBadEncoded)
{
    const uint8_t *const objectBytes = FIXTURE_INDEX(0);
    const size_t objectSize = *(size_t *)(FIXTURE_INDEX(1));

    BTLV_DataObject *decodedObject;

    // Checking how the function handles buffers that ends before the data object reachs its
    // last tag. Starting from a buffer slightly smaller than the real data object (1 byte
    // smaller) and continuing reducing the buffer until size 0 bytes
    for (int decrementalObjectSize = (int)objectSize - 1; decrementalObjectSize >= 0; --decrementalObjectSize) {
        BTLV_ReturnCode ret = BTLV_decodeTlvObject(objectBytes, decrementalObjectSize, &decodedObject);

        munit_assert_int(ret, ==, BTLV_BAD_TLV_ENCODING);
        munit_assert_ptr_null(decodedObject);
    }

    return MUNIT_OK;
}

static MunitTest btlvParsingTests[] = {GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectSingleByteTag",
                                                                      decodeSuccessfully,
                                                                      btlvSingleByteTagPrimitiveDataObject),
                                       GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectMultiByteTag",
                                                                      decodeSuccessfully,
                                                                      btlvMultiByteTagPrimitiveDataObject),
                                       GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectSingleByteLength",
                                                                      decodeSuccessfully,
                                                                      btlvSingleByteLenPrimitiveDataObject),
                                       GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectMultiByteLength",
                                                                      decodeSuccessfully,
                                                                      btlvMultiByteLenPrimitiveDataObject),
                                       GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectSingleNested",
                                                                      decodeSuccessfully,
                                                                      btlvSingleNestingByteBlockConstructedDataObject),
                                       GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectMultiNested",
                                                                      decodeSuccessfully,
                                                                      btlvMultiNestingByteBlockConstructedDataObject),
                                       GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectBadEncodedPrimitive",
                                                                      decodeBadEncoded,
                                                                      btlvBadEncodedPrimitiveDataObject),
                                       GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObjectBadEncodedConstructed",
                                                                      decodeBadEncoded,
                                                                      btlvBadEncodedConstructedDataObject),
                                       TEST_FUNC_ARRAY_END};

static MunitSuite btlvParsingTestsSuite = {"/parsing", btlvParsingTests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

MunitSuite
btlvParsingTestsGetSuite(void)
{
    return btlvParsingTestsSuite;
}