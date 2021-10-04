#include "btlv_tests.h"

static MunitSuite allTestSuites[BTLV_SUBSUITES_NUMBER];

static const MunitSuite suite = {
    "/BTLV",
    NULL,
    allTestSuites,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char *argv[]) {
    int btlvTestSuitesCounter = 0;
    allTestSuites[btlvTestSuitesCounter++] = btlvVersionTestsGetSuite();
    allTestSuites[btlvTestSuitesCounter++] = btlvTryingToCrashTestsGetSuite();
    allTestSuites[btlvTestSuitesCounter++] = btlvParsingTestsGetSuite();
    allTestSuites[btlvTestSuitesCounter++] = btlvPrintingTestsGetSuite();

    return munit_suite_main(&suite, NULL, argc, argv);
}