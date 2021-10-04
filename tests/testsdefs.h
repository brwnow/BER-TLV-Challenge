#ifndef BTLV_LIB_TESTS_DEFS_H
#define BTLV_LIB_TESTS_DEFS_H

#include <munit.h>

// Macros that gives the complete name for several kind of test functions
// this allows to work with a symbolic function name what keep it easier
// also make it possible to automate some declarations

#define GET_SETUP_FUNC_NAME(funcName) funcName ## _setup
#define GET_TEARDOWN_FUNC_NAME(funcName) funcName ## _teardown

#define GET_TEST_FUNC_NAME(funcName) funcName ## _test
#define GET_TEST_FUNC_SETUP_PTR(funcName) funcName ## _test_setup_ptr
#define GET_TEST_FUNC_TEARDOWN_PTR(funcName) funcName ## _test_teardown_ptr

#define GET_TEST_FUNC_ARRAY_ENTRY(testName, funcName) { \
    testName, \
    GET_TEST_FUNC_NAME(funcName), \
    GET_TEST_FUNC_SETUP_PTR(funcName), \
    GET_TEST_FUNC_TEARDOWN_PTR(funcName), \
    MUNIT_TEST_OPTION_NONE, \
    NULL }

#define TEST_FUNC_ARRAY_END { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

#define RETURN_EXISTING_SETUP_FUNC(funcName) return GET_SETUP_FUNC_NAME(funcName)(params, user_data)

// Macros for declaring some kinds of test functions
// setup - prepare the test data structures
// teardown - clean up what setup allocated
#define DECLARE_SETUP_FUNC(funcName) void* GET_SETUP_FUNC_NAME(funcName)( \
                                                            const MunitParameter params[] MUNIT_UNUSED, \
                                                            void* user_data MUNIT_UNUSED)
#define DECLARE_TEARDOWN_FUNC(funcName) void GET_TEARDOWN_FUNC_NAME(funcName)(void* fixture)

// these following macos declare the test function itsel and pointers to itsel and its setup and teardown
#define DECLARE_TEST_FUNC(funcName) static MunitResult GET_TEST_FUNC_NAME(funcName)( \
                                                            const MunitParameter params[] MUNIT_UNUSED, \
                                                            void* fixture MUNIT_UNUSED )
#define DECLARE_TEST_FUNC_SETUP_PTR(funcName) static void* (*const GET_TEST_FUNC_SETUP_PTR(funcName))( \
                                                                const MunitParameter params[] MUNIT_UNUSED, \
                                                                void* user_data MUNIT_UNUSED )
#define DECLARE_TEST_FUNC_TEARDOWN_PTR(funcName) static void (*const GET_TEST_FUNC_TEARDOWN_PTR(funcName))( \
                                                                void* fixture )

// Define a standalone test function (with not setup and teardown)
// this macros define the function and also pointers related to it to be added to
// munit test framework data structures
#define DEFINE_STANDALONE_TEST_FUNC(funcName) \
    DECLARE_TEST_FUNC_SETUP_PTR(funcName) = NULL; \
    DECLARE_TEST_FUNC_TEARDOWN_PTR(funcName) = NULL; \
    DECLARE_TEST_FUNC(funcName)

// Define a full test function (it needs a setup and a teardown)
// setupTeardownPairName is the name of one of the setup/teardown function prefix
// in the source for setups of the test module
#define DEFINE_FULL_TEST_FUNC(funcName, setupTeardownPairName) \
    DECLARE_TEST_FUNC_SETUP_PTR(funcName) = GET_SETUP_FUNC_NAME(setupTeardownPairName); \
    DECLARE_TEST_FUNC_TEARDOWN_PTR(funcName) = GET_TEARDOWN_FUNC_NAME(setupTeardownPairName); \
    DECLARE_TEST_FUNC(funcName)

// Macros to facilitate working with fixture array
#define FIXTURE_CREATE(size) void *fixture = malloc(sizeof(void*) * size)
#define FIXTURE_INDEX(index) (((void**)fixture)[index])
#define FIXTURE_RETURN return fixture

#endif // BTLV_LIB_TESTS_DEFS_H