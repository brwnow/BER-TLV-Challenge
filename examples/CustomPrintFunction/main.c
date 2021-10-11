#include "bertlv.h"

#include <stdio.h>

// Compound BER-TLV data object byte block to be printed
static const uint8_t fciTlvObject[] = {0x6F, 0x1A, 0x84, 0x0E, 0x31, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59,
                                       0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31, 0xA5, 0x08, 0x88, 0x01,
                                       0x02, 0x5F, 0x2D, 0x02, 0x65, 0x6E, 0xE1, 0x0B, 0xC1, 0x03, 0x01,
                                       0x02, 0x03, 0xC2, 0x00, 0xC3, 0x02, 0xAA, 0xBB};

static void
myPrintTab(const uint8_t tab, const char tabChar)
{
    for (uint8_t i = 0; i < tab; ++i)
        printf("%c", tabChar);
}

static BTLV_ObjectPrintCallbackRetVal
myNavigatorPrinter(const BTLV_DataObject *const object, const uint8_t nestingLevel)
{
    // My custom tabbing style
    const uint8_t tab = nestingLevel * 3;
    const char tabChar = '.';

    myPrintTab(tab, tabChar);

    // my way of printing tag
    for (size_t i = 0; i < object->tagSize; ++i)
        printf(" %02X", object->tag[i]);

    printf(" | ");

    switch (object->class) {
    case BTLV_CLASS_UNIVERSAL:
        printf("UNIVERSAL");
        break;

    case BTLV_CLASS_APPLICATION:
        printf("APPLICATION");
        break;

    case BTLV_CLASS_CONTEXT_SPECIFIC:
        printf("CONTEXT SPECIFIC");
        break;

    case BTLV_CLASS_PRIVATE:
        printf("PRIVATE");
        break;
    }

    printf(" | %s\n", object->type == BTLV_PRIMITIVE ? "PRIMITIVE" : "CONSTRUCTED");

    if (object->type == BTLV_PRIMITIVE && object->length > 0) {
        myPrintTab(tab, tabChar);

        if (object->length > 0)
            printf(" ");

        // my custom style of printing value field
        for (size_t i = 0; i < object->length; ++i)
            printf("%02X", object->valueField.value[i]);

        printf(" (%zu %s)\n", object->length, (object->length == 1 ? "byte" : "bytes"));
    } else if (object->type == BTLV_CONSTRUCTED) {
        myPrintTab(tab, tabChar);
        printf(" %zu %s\n", object->length, (object->length == 1 ? "byte" : "bytes"));
    }

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
        ret = BTLV_depthFirstNavigateObject(&(parsedObjects[i]), myNavigatorPrinter);

        if (ret != BTLV_RET_OK) {
            printf("An error has occurred printing of root element #%lu.\nError code: %d\n", i, ret);
        }
    }

    // Cleaning memory
    BTLV_destroyTlvObjectArray(parsedObjects, rootElementsCount);

    return 0;
}