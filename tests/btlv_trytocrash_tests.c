#include "testsdefs.h"

#include "bertlv.h"
#include "btlv_tests.h"
#include "btlv_test_setups.h"

static BTLV_ObjectPrintCallbackRetVal stubPrintCallback(const BTLV_DataObject *const object, const uint8_t nestingLevel)
{
    (void)object;
    (void)nestingLevel;

    return BTLV_DEPTH_NAVIGATION_STEP_INTO;
}

static uint8_t stubByteArray[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

static BTLV_DataObject stubDataObject;

DEFINE_STANDALONE_TEST_FUNC(decodeTlvObject) {
    munit_assert_ptr_null(BTLV_decodeTlvObject(NULL, 0));
    munit_assert_ptr_null(BTLV_decodeTlvObject(NULL, 50));
    munit_assert_ptr_null(BTLV_decodeTlvObject(stubByteArray, 0));

    return MUNIT_OK;
}

DEFINE_STANDALONE_TEST_FUNC(encodeTlvObject) {
    munit_assert_int(BTLV_encodeTlvObject(NULL, NULL, 0), ==, -1);
    munit_assert_int(BTLV_encodeTlvObject(&stubDataObject, NULL, 0), ==, -1);
    munit_assert_int(BTLV_encodeTlvObject(NULL, stubByteArray, 0), ==, -1);
    munit_assert_int(BTLV_encodeTlvObject(&stubDataObject, stubByteArray, 0), ==, -1);

    munit_assert_int(BTLV_encodeTlvObject(NULL, NULL, 50), ==, -1);
    munit_assert_int(BTLV_encodeTlvObject(&stubDataObject, NULL, 50), ==, -1);
    munit_assert_int(BTLV_encodeTlvObject(NULL, stubByteArray, 50), ==, -1);

    return MUNIT_OK;
}

DEFINE_STANDALONE_TEST_FUNC(printObject) {
    munit_assert_int(BTLV_printObject(NULL), ==, -1);

    return MUNIT_OK;
}

DEFINE_STANDALONE_TEST_FUNC(depthFirstNavigateObject) { 
    munit_assert_int(BTLV_depthFirstNavigateObject(NULL, NULL), ==, -1);
    munit_assert_int(BTLV_depthFirstNavigateObject(&stubDataObject, NULL), ==, -1);
    munit_assert_int(BTLV_depthFirstNavigateObject(NULL, stubPrintCallback), ==, -1);

    return MUNIT_OK;
}

DEFINE_STANDALONE_TEST_FUNC(blockOfBytesNavigateObject) {
    munit_assert_int(BTLV_blockOfBytesNavigateObject(NULL, 0, NULL), ==, -1);
    munit_assert_int(BTLV_blockOfBytesNavigateObject(stubByteArray, 0, NULL), ==, -1);
    munit_assert_int(BTLV_blockOfBytesNavigateObject(NULL, 0, stubPrintCallback), ==, -1);
    munit_assert_int(BTLV_blockOfBytesNavigateObject(stubByteArray, 0, stubPrintCallback), ==, -1);

    munit_assert_int(BTLV_blockOfBytesNavigateObject(NULL, 50, NULL), ==, -1);
    munit_assert_int(BTLV_blockOfBytesNavigateObject(stubByteArray, 50, NULL), ==, -1);
    munit_assert_int(BTLV_blockOfBytesNavigateObject(NULL, 50, stubPrintCallback), ==, -1);

    return MUNIT_OK;
}

DEFINE_STANDALONE_TEST_FUNC(destroyTlvObjectNullptr) {
    BTLV_destroyTlvObject(NULL);

    // Checking if crashes destroynig primitive data object
    BTLV_destroyTlvObject();

    // Checking if crashes destroying constructed data object
    BTLV_destroyTlvObject();

    return MUNIT_OK;
}

DEFINE_FULL_TEST_FUNC(destroyTlvObjectPrimitive, btlvPrimitiveDataObject) {
    BTLV_DataObject *object = FIXTURE_INDEX(user_data_or_fixture, 0);

    BTLV_destroyTlvObject(object);

    return MUNIT_OK;
}

DEFINE_FULL_TEST_FUNC(destroyTlvObjectConstructed, btlvConstructedDataObject) {
    BTLV_DataObject *object = FIXTURE_INDEX(user_data_or_fixture, 0);

    BTLV_destroyTlvObject(object);

    return MUNIT_OK;
}

static MunitTest btlvTryingToCrashTests[] = {
    GET_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObject", decodeTlvObject),
    GET_TEST_FUNC_ARRAY_ENTRY("/BTLV_encodeTlvObject", encodeTlvObject),
    GET_TEST_FUNC_ARRAY_ENTRY("/BTLV_printObject", printObject),
    GET_TEST_FUNC_ARRAY_ENTRY("/BTLV_depthFirstNavigateObject", depthFirstNavigateObject),
    GET_TEST_FUNC_ARRAY_ENTRY("/BTLV_blockOfBytesNavigateObject", blockOfBytesNavigateObject),
    GET_TEST_FUNC_ARRAY_ENTRY("/BTLV_destroyTlvObjectNullptr", destroyTlvObjectNullptr),
    GET_TEST_FUNC_ARRAY_ENTRY("/BTLV_destroyTlvObjectNullptr", destroyTlvObjectPrimitive),
    GET_TEST_FUNC_ARRAY_ENTRY("/BTLV_destroyTlvObjectNullptr", destroyTlvObjectConstructed),

    TEST_FUNC_ARRAY_END
};

static MunitSuite btlvTryingToCrashTestsSuite = {
    "/tryingToCrash",
    btlvTryingToCrashTests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

MunitSuite btlvTryingToCrashTestsGetSuite(void) {
    return btlvTryingToCrashTestsSuite;
}