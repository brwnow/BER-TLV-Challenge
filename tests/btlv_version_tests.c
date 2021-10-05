#include "testsdefs.h"

#include "bertlv.h"
#include "btlv_test_setups.h"
#include "btlv_tests.h"

DECLARE_TEST_FUNC(btlvGetVersion)
{
    const char *version = BTLV_getVersion();
    const char *fixtureVersion = FIXTURE_INDEX(0);

    munit_assert_ptr_not_null(version);
    munit_assert_string_equal(version, fixtureVersion);

    return MUNIT_OK;
}

static MunitTest btlvVersionTests[] = {
    GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_getVersion", btlvGetVersion, btlvVersionString),
    TEST_FUNC_ARRAY_END};

static MunitSuite btlvVersionTestsSuite = {"/version", btlvVersionTests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

MunitSuite
btlvVersionTestsGetSuite(void)
{
    return btlvVersionTestsSuite;
}