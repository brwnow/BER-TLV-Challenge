#include "testsdefs.h"

#include "bertlv.h"
#include "btlv_test_setups.h"
#include "btlv_tests.h"

#include <stdio.h>

DECLARE_TEST_FUNC(printgComplexTlvDataObject)
{
    BTLV_DataObject *const tlvObject = FIXTURE_INDEX(0);
    const size_t tlvObjectSize = *(size_t *)(FIXTURE_INDEX(1));
    char *expectedResult = FIXTURE_INDEX(2);

    const char *tempStdoutFilename = "tempstdout";
    FILE *tempStdout = freopen(tempStdoutFilename, "w", stdout);

    munit_assert_int(BTLV_printObjectArray(tlvObject, tlvObjectSize), ==, BTLV_RET_OK);

    fclose(tempStdout);
    tempStdout = fopen(tempStdoutFilename, "r");

    // getting the size of outputed content and malloc memory to load it
    fseek(tempStdout, 0, SEEK_END);
    long outputLength = ftell(tempStdout);
    char *result = malloc(outputLength);
    fseek(tempStdout, 0, SEEK_SET);

    // not enough memory to load printed content from file
    if (result == NULL) {
        fclose(tempStdout);
        remove(tempStdoutFilename);
        return MUNIT_ERROR;
    }

    fread(result, 1, outputLength, tempStdout);

    fclose(tempStdout);
    remove(tempStdoutFilename); // not so portable, but working only for linux for while

    munit_assert_string_equal(result, expectedResult);

    free(result);

    return MUNIT_OK;
}

static MunitTest btlvPrintingTests[] = {GET_FULL_TEST_FUNC_ARRAY_ENTRY("/BTLV_printObjectArrayComplexDataObject",
                                                                       printgComplexTlvDataObject,
                                                                       btlvPrintingMockedOutputStream),

                                        TEST_FUNC_ARRAY_END};

static MunitSuite btlvPrintingTestsSuite = {"/printing", btlvPrintingTests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

MunitSuite
btlvPrintingTestsGetSuite(void)
{
    return btlvPrintingTestsSuite;
}