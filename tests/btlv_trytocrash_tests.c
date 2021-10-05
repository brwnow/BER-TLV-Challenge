#include "testsdefs.h"

#include "bertlv.h"
#include "btlv_test_setups.h"
#include "btlv_tests.h"

static BTLV_ObjectPrintCallbackRetVal
stubPrintCallback(const BTLV_DataObject *const object, const uint8_t nestingLevel)
{
    (void)object;
    (void)nestingLevel;

    return BTLV_DEPTH_NAVIGATION_STEP_INTO;
}

static uint8_t stubByteArray[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

static BTLV_DataObject stubDataObject;
static BTLV_DataObject *stubOutputObject;

DECLARE_TEST_FUNC(decodeTlvObject)
{
    munit_assert_int(BTLV_decodeTlvObject(NULL, 0, &stubOutputObject), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_decodeTlvObject(NULL, 50, &stubOutputObject), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_decodeTlvObject(stubByteArray, 0, &stubOutputObject), ==, BTLV_INVALID_PARAMETER);

    return MUNIT_OK;
}

DECLARE_TEST_FUNC(encodeTlvObject)
{
    munit_assert_int(BTLV_encodeTlvObject(NULL, NULL, 0), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_encodeTlvObject(&stubDataObject, NULL, 0), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_encodeTlvObject(NULL, stubByteArray, 0), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_encodeTlvObject(&stubDataObject, stubByteArray, 0), ==, BTLV_INVALID_PARAMETER);

    munit_assert_int(BTLV_encodeTlvObject(NULL, NULL, 50), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_encodeTlvObject(&stubDataObject, NULL, 50), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_encodeTlvObject(NULL, stubByteArray, 50), ==, BTLV_INVALID_PARAMETER);

    return MUNIT_OK;
}

DECLARE_TEST_FUNC(printObject)
{
    munit_assert_int(BTLV_printObject(NULL), ==, BTLV_INVALID_PARAMETER);

    return MUNIT_OK;
}

DECLARE_TEST_FUNC(depthFirstNavigateObject)
{
    munit_assert_int(BTLV_depthFirstNavigateObject(NULL, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_depthFirstNavigateObject(&stubDataObject, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_depthFirstNavigateObject(NULL, stubPrintCallback), ==, BTLV_INVALID_PARAMETER);

    return MUNIT_OK;
}

DECLARE_TEST_FUNC(blockOfBytesNavigateObject)
{
    munit_assert_int(BTLV_blockOfBytesNavigateObject(NULL, 0, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_blockOfBytesNavigateObject(stubByteArray, 0, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_blockOfBytesNavigateObject(NULL, 0, stubPrintCallback), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_blockOfBytesNavigateObject(stubByteArray, 0, stubPrintCallback), ==, BTLV_INVALID_PARAMETER);

    munit_assert_int(BTLV_blockOfBytesNavigateObject(NULL, 50, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_blockOfBytesNavigateObject(stubByteArray, 50, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_blockOfBytesNavigateObject(NULL, 50, stubPrintCallback), ==, BTLV_INVALID_PARAMETER);

    return MUNIT_OK;
}

DECLARE_TEST_FUNC(destroyTlvObjectNullptr)
{
    BTLV_destroyTlvObject(NULL);

    return MUNIT_OK;
}

DECLARE_TEST_FUNC(destroyTlvObjectPrimitive)
{
    BTLV_DataObject *object = FIXTURE_INDEX(0);

    BTLV_destroyTlvObject(object);

    return MUNIT_OK;
}

DECLARE_TEST_FUNC(destroyTlvObjectConstructed)
{
    BTLV_DataObject *object = FIXTURE_INDEX(0);

    BTLV_destroyTlvObject(object);

    return MUNIT_OK;
}

static MunitTest btlvTryingToCrashTests[] = {
    GET_STANDALONE_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObject", decodeTlvObject),
    GET_STANDALONE_TEST_FUNC_ARRAY_ENTRY("/BTLV_encodeTlvObject", encodeTlvObject),
    GET_STANDALONE_TEST_FUNC_ARRAY_ENTRY("/BTLV_printObject", printObject),
    GET_STANDALONE_TEST_FUNC_ARRAY_ENTRY("/BTLV_depthFirstNavigateObject", depthFirstNavigateObject),
    GET_STANDALONE_TEST_FUNC_ARRAY_ENTRY("/BTLV_blockOfBytesNavigateObject", blockOfBytesNavigateObject),
    GET_STANDALONE_TEST_FUNC_ARRAY_ENTRY("/BTLV_destroyTlvObjectNullptr", destroyTlvObjectNullptr),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_destroyTlvObjectPrimitive", destroyTlvObjectPrimitive, btlvPrimitiveDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_destroyTlvObjectConstructed", destroyTlvObjectConstructed, btlvPrimitiveDataObject),

    TEST_FUNC_ARRAY_END};

static MunitSuite btlvTryingToCrashTestsSuite = {"/tryingToCrash",
                                                 btlvTryingToCrashTests,
                                                 NULL,
                                                 1,
                                                 MUNIT_SUITE_OPTION_NONE};

MunitSuite
btlvTryingToCrashTestsGetSuite(void)
{
    return btlvTryingToCrashTestsSuite;
}