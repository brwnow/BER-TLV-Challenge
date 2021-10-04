#include "testsdefs.h"

#include "bertlv.h"
#include "btlv_tests.h"
#include "btlv_test_setups.h"

static MunitTest btlvParsingTests[] = {
    TEST_FUNC_ARRAY_END
};

static MunitSuite btlvParsingTestsSuite = {
    "/parsing",
    btlvParsingTests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

MunitSuite btlvParsingTestsGetSuite(void) {
    return btlvParsingTestsSuite;
}