#include "bertlv.h"

#include <stdio.h>

#define PERCENT_FMT "%6.2f%%"

// Compound BER-TLV data object byte block to be printed
static const uint8_t fciTlvObject[] = {0x6F, 0x1A, 0x84, 0x0E, 0x31, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59,
                                       0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31, 0xA5, 0x08, 0x88, 0x01,
                                       0x02, 0x5F, 0x2D, 0x02, 0x65, 0x6E, 0xE1, 0x0B, 0xC1, 0x03, 0x01,
                                       0x02, 0x03, 0xC2, 0x00, 0xC3, 0x02, 0xAA, 0xBB};

static int tagClassCounter[4];
static int tagTypeCounter[2];
static uint8_t deepestNestingLevel = 0;
static size_t primitiveTagLenSum = 0;

static void
statisticsCleanup(void)
{
    for (size_t i = 0; i < sizeof(tagClassCounter) / sizeof(int); ++i)
        tagClassCounter[i] = 0;

    for (size_t i = 0; i < sizeof(tagTypeCounter) / sizeof(int); ++i)
        tagTypeCounter[i] = 0;

    deepestNestingLevel = 0;
    primitiveTagLenSum = 0;
}

static double
calcPercentage(double amount, double total)
{
    return amount * 100.0 / total;
}

static BTLV_ObjectPrintCallbackRetVal
statisticsNavigator(const BTLV_DataObject *const object, const uint8_t nestingLevel)
{
    ++(tagClassCounter[object->class]);
    ++(tagTypeCounter[object->type]);

    if (nestingLevel > deepestNestingLevel)
        deepestNestingLevel = nestingLevel;

    if (object->type == BTLV_PRIMITIVE)
        primitiveTagLenSum += object->length;

    return BTLV_DEPTH_NAVIGATION_STEP_INTO;
}

int
main()
{
    // Pointer that will receive the address of array of root data objects extracted from ber-tlv block
    BTLV_DataObject *parsedObjects = NULL;

    // Count control to receive the amount of root data objects extracted
    size_t rootElementsCount = 0;

    BTLV_ReturnCode ret = BTLV_decodeTlvObject(fciTlvObject, sizeof(fciTlvObject), &parsedObjects, &rootElementsCount);

    if (ret != BTLV_RET_OK) {
        printf("An error has occurred during BER-TLV data object parsing.\nError code: %d\n\nABORTING\n", ret);

        return 0;
    }

    for (size_t i = 0; i < rootElementsCount; ++i) {
        statisticsCleanup();

        ret = BTLV_depthFirstNavigateObject(&(parsedObjects[i]), statisticsNavigator);
        if (ret != BTLV_RET_OK) {
            printf("An error has occurred printing of root element #%lu.\nError code: %d\n", i, ret);
            continue;
        }

        int totalTagsFound = 0;
        for (int i = 0; i < 4; ++i)
            totalTagsFound += tagClassCounter[i];

        printf("----------------------\n");
        printf("---- ROOT TAG %03zu ----\n", i);
        printf("----------------------\n\n");

        printf("CLASS\n");
        printf("   UNIVERSAL    | %02d | " PERCENT_FMT "\n",
               tagClassCounter[BTLV_CLASS_UNIVERSAL],
               calcPercentage(tagClassCounter[BTLV_CLASS_UNIVERSAL], totalTagsFound));
        printf("   APPLICATION  | %02d | " PERCENT_FMT "\n",
               tagClassCounter[BTLV_CLASS_APPLICATION],
               calcPercentage(tagClassCounter[BTLV_CLASS_APPLICATION], totalTagsFound));
        printf("   CTX-SPECIFIC | %02d | " PERCENT_FMT "\n",
               tagClassCounter[BTLV_CLASS_CONTEXT_SPECIFIC],
               calcPercentage(tagClassCounter[BTLV_CLASS_CONTEXT_SPECIFIC], totalTagsFound));
        printf("   PRIVATE      | %02d | " PERCENT_FMT "\n",
               tagClassCounter[BTLV_CLASS_PRIVATE],
               calcPercentage(tagClassCounter[BTLV_CLASS_PRIVATE], totalTagsFound));
        printf("TYPE\n");
        printf("   PRIMITIVE    | %02d | " PERCENT_FMT "\n",
               tagTypeCounter[BTLV_PRIMITIVE],
               calcPercentage(tagTypeCounter[BTLV_PRIMITIVE], totalTagsFound));
        printf("   CONSTRUCTED  | %02d | " PERCENT_FMT "\n",
               tagTypeCounter[BTLV_CONSTRUCTED],
               calcPercentage(tagTypeCounter[BTLV_CONSTRUCTED], totalTagsFound));
        printf("\nDEEPEST NESTING LEVEL         -> %d\n", deepestNestingLevel);
        printf("AVERAGE PRIMITIVE TAGS LENGTH -> %.1f bytes\n\n",
               (double)primitiveTagLenSum / tagTypeCounter[BTLV_PRIMITIVE]);
    }

    // Cleaning memory
    BTLV_destroyTlvObjectArray(parsedObjects, rootElementsCount);

    return 0;
}