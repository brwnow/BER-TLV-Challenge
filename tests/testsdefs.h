#ifndef BTLV_LIB_TESTS_DEFS_H
#define BTLV_LIB_TESTS_DEFS_H

#include <munit.h>

// Macros that gives the complete name for several kind of test functions
// this allows to work with a symbolic function name which keeps it easier
// also make it possible to automate some declarations

#define GET_SETUP_FUNC_NAME(funcName) funcName ## _setup
#define GET_TEARDOWN_FUNC_NAME(funcName) funcName ## _teardown

#define GET_TEST_FUNC_NAME(funcName) funcName ## _test

#define GET_FULL_TEST_FUNC_ARRAY_ENTRY(testName, funcName, setupTeardownName) { \
    testName, \
    GET_TEST_FUNC_NAME(funcName), \
    GET_SETUP_FUNC_NAME(setupTeardownName), \
    GET_TEARDOWN_FUNC_NAME(setupTeardownName), \
    MUNIT_TEST_OPTION_NONE, \
    NULL }

#define GET_STANDALONE_TEST_FUNC_ARRAY_ENTRY(testName, funcName) { \
    testName, \
    GET_TEST_FUNC_NAME(funcName), \
    NULL, \
    NULL, \
    MUNIT_TEST_OPTION_NONE, \
    NULL }

#define TEST_FUNC_ARRAY_END { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

// Macros for declaring some kinds of test functions
// setup - prepare the test data structures
// teardown - clean up what setup allocated
#define DECLARE_SETUP_FUNC(funcName) void* GET_SETUP_FUNC_NAME(funcName)( \
                                                            const MunitParameter params[] MUNIT_UNUSED, \
                                                            void* user_data MUNIT_UNUSED)
#define DECLARE_TEARDOWN_FUNC(funcName) void GET_TEARDOWN_FUNC_NAME(funcName)(void* fixture)

// Declares the test function itself
#define DECLARE_TEST_FUNC(funcName) static MunitResult GET_TEST_FUNC_NAME(funcName)( \
                                                            const MunitParameter params[] MUNIT_UNUSED, \
                                                            void* fixture MUNIT_UNUSED )

// Macros to facilitate working with fixture arrays
#define FIXTURE_CREATE(size) void *fixture = malloc(sizeof(void*) * size)
#define FIXTURE_INDEX(index) (((void**)fixture)[index])
#define FIXTURE_RETURN return fixture

#endif // BTLV_LIB_TESTS_DEFS_H