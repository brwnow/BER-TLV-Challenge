#include "testsdefs.h"

#include "bertlv.h"
#include "btlv_tests.h"
#include "btlv_test_setups.h"

static MunitTest btlvPrintingTests[] = {
    TEST_FUNC_ARRAY_END
};

static MunitSuite btlvPrintingTestsSuite = {
    "/printing",
    btlvPrintingTests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

MunitSuite btlvPrintingTestsGetSuite(void) {
    return btlvPrintingTestsSuite;
}