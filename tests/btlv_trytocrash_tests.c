#include "testsdefs.h"

#include "bertlv.h"
#include "btlv_test_setups.h"
#include "btlv_tests.h"
#include "tlvparser.h"

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

static size_t stubOutputLength;
static size_t stubOutputByteCount;

DECLARE_TEST_FUNC(decodeTlvObject)
{
    munit_assert_int(BTLV_decodeTlvObject(NULL, 0, NULL, NULL), ==, BTLV_INVALID_PARAMETER);

    munit_assert_int(BTLV_decodeTlvObject(stubByteArray, 0, NULL, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_decodeTlvObject(NULL, 0, &stubOutputObject, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_decodeTlvObject(NULL, 0, NULL, &stubOutputLength), ==, BTLV_INVALID_PARAMETER);

    munit_assert_int(BTLV_decodeTlvObject(stubByteArray, 0, &stubOutputObject, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_decodeTlvObject(stubByteArray, 0, NULL, &stubOutputLength), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_decodeTlvObject(NULL, 0, &stubOutputObject, &stubOutputLength), ==, BTLV_INVALID_PARAMETER);

    munit_assert_int(BTLV_decodeTlvObject(NULL, 50, NULL, NULL), ==, BTLV_INVALID_PARAMETER);

    munit_assert_int(BTLV_decodeTlvObject(stubByteArray, 50, NULL, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_decodeTlvObject(NULL, 50, &stubOutputObject, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_decodeTlvObject(NULL, 50, NULL, &stubOutputLength), ==, BTLV_INVALID_PARAMETER);

    munit_assert_int(BTLV_decodeTlvObject(stubByteArray, 50, &stubOutputObject, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_decodeTlvObject(stubByteArray, 50, NULL, &stubOutputLength), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_decodeTlvObject(NULL, 50, &stubOutputObject, &stubOutputLength), ==, BTLV_INVALID_PARAMETER);

    munit_assert_int(
        BTLV_decodeTlvObject(stubByteArray, 0, &stubOutputObject, &stubOutputLength), ==, BTLV_BAD_TLV_ENCODING);

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

DECLARE_TEST_FUNC(parseTagField)
{
    munit_assert_int(BTLV_tagFieldParse(NULL, 0, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_tagFieldParse(stubByteArray, 0, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_tagFieldParse(NULL, 0, &stubDataObject), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_tagFieldParse(NULL, 50, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_tagFieldParse(stubByteArray, 50, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_tagFieldParse(NULL, 50, &stubDataObject), ==, BTLV_INVALID_PARAMETER);

    munit_assert_int(BTLV_tagFieldParse(stubByteArray, 0, &stubDataObject), ==, BTLV_BAD_TLV_ENCODING);

    return MUNIT_OK;
}

DECLARE_TEST_FUNC(parseLengthField)
{
    munit_assert_int(BTLV_lengthFieldParse(NULL, 0, NULL, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_lengthFieldParse(stubByteArray, 0, NULL, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_lengthFieldParse(NULL, 0, &stubOutputLength, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_lengthFieldParse(NULL, 0, NULL, &stubOutputByteCount), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_lengthFieldParse(stubByteArray, 0, &stubOutputLength, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_lengthFieldParse(stubByteArray, 0, NULL, &stubOutputByteCount), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(
        BTLV_lengthFieldParse(NULL, 0, &stubOutputLength, &stubOutputByteCount), ==, BTLV_INVALID_PARAMETER);

    munit_assert_int(BTLV_lengthFieldParse(NULL, 50, NULL, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_lengthFieldParse(stubByteArray, 50, NULL, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_lengthFieldParse(NULL, 50, &stubOutputLength, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_lengthFieldParse(NULL, 50, NULL, &stubOutputByteCount), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_lengthFieldParse(stubByteArray, 50, &stubOutputLength, NULL), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(BTLV_lengthFieldParse(stubByteArray, 50, NULL, &stubOutputByteCount), ==, BTLV_INVALID_PARAMETER);
    munit_assert_int(
        BTLV_lengthFieldParse(NULL, 50, &stubOutputLength, &stubOutputByteCount), ==, BTLV_INVALID_PARAMETER);

    munit_assert_int(
        BTLV_lengthFieldParse(stubByteArray, 0, &stubOutputLength, &stubOutputByteCount), ==, BTLV_BAD_TLV_ENCODING);

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

DECLARE_TEST_FUNC(destroyTlvObjectArray)
{
    BTLV_DataObject *objectArray = FIXTURE_INDEX(0);
    size_t arraySize = *(size_t *)(FIXTURE_INDEX(1));

    BTLV_destroyTlvObjectArray(objectArray, arraySize);

    return MUNIT_OK;
}

static MunitTest btlvTryingToCrashTests[] = {
    GET_STANDALONE_TEST_FUNC_ARRAY_ENTRY("/BTLV_decodeTlvObject", decodeTlvObject),
    GET_STANDALONE_TEST_FUNC_ARRAY_ENTRY("/BTLV_printObject", printObject),
    GET_STANDALONE_TEST_FUNC_ARRAY_ENTRY("/BTLV_depthFirstNavigateObject", depthFirstNavigateObject),
    GET_STANDALONE_TEST_FUNC_ARRAY_ENTRY("/BTLV_destroyTlvObjectNullptr", destroyTlvObjectNullptr),
    GET_STANDALONE_TEST_FUNC_ARRAY_ENTRY("/BTLV_tagFieldParse", parseTagField),
    GET_STANDALONE_TEST_FUNC_ARRAY_ENTRY("/BTLV_legthFieldParse", parseLengthField),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_destroyTlvObjectPrimitive",
                                   destroyTlvObjectPrimitive,
                                   btlvPrimitiveDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_destroyTlvObjectConstructed",
                                   destroyTlvObjectConstructed,
                                   btlvPrimitiveDataObject),
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_destroyTlvObjectArray",
                                   destroyTlvObjectArray,
                                   btlvConstructedDataObjectArray),

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