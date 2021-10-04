#ifndef BTLV_LIB_BTLV_TESTS_H
#define BTLV_LIB_BTLV_TESTS_H

#include <munit.h>

// Controls the amount of subsuites for btlv tests
#define BTLV_SUBSUITES_NUMBER 4

MunitSuite btlvVersionTestsGetSuite(void);
MunitSuite btlvTryingToCrashTestsGetSuite(void);
MunitSuite btlvParsingTestsGetSuite(void);
MunitSuite btlvPrintingTestsGetSuite(void);

#endif // BTLV_LIB_BTLV_TESTS_H