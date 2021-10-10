#include "io/printinghelper.h"

#include <stdio.h>

// 32 white spaces buffered for speed up printing routines
static char spacesArray[] = "                                ";

// 8 line spacing buffered for speed up printing
static char lineSpacingArray[] = "\n\n\n\n\n\n\n\n";

static char *classNames[] = {
    "universal",
    "application",
    "context-specific",
    "private"
};

static char *typeNames[] = {
    "primitive",
    "constructed"
};

static uint8_t defaultTabSize = 4;
static uint8_t defaultLineSpacing = 0;
static uint8_t defaultElementSpacing = 1;

static void
printWhiteSpaces(uint8_t amount)
{
    const size_t maxAmount = sizeof(spacesArray) / sizeof(char);

    if (amount == 0)
        return;

    if (amount > maxAmount)
        amount = maxAmount;

    spacesArray[amount] = '\0';
    printf("%s", spacesArray);
    spacesArray[amount] = amount == maxAmount ? '\0' : ' ';
}

static void
printfLineSpacing(uint8_t amount)
{
    const size_t maxAmount = sizeof(lineSpacingArray) / sizeof(char);

    if (amount == 0)
        return;

    if (amount > maxAmount)
        amount = maxAmount;

    lineSpacingArray[amount] = '\0';
    printf("%s", lineSpacingArray);
    lineSpacingArray[amount] = amount == maxAmount ? '\0' : '\n';
}

static void
printTag(const BTLV_DataObject *const object)
{
    if (object == NULL)
        return;

    printf("TAG - ");
    printf("0x%02X ", object->tag[0]);
    if(object->tagSize > 1)
        printf("0x%02X ", object->tag[1]);

    printf("(%s class, %s)\n", classNames[object->class], typeNames[object->type]);

}

static void
printPrimitiveVal(const uint8_t *const byteArray, const size_t arraySize)
{
    if (byteArray == NULL || arraySize == 0)
        return;

    printf("VAL -");

    for(size_t i = 0; i < arraySize; ++i)
        printf(" 0x%02X", byteArray[i]);

    printf("\n");
}

static BTLV_ObjectPrintCallbackRetVal
defaultNavigatorPrinter(const BTLV_DataObject *const object, const uint8_t nestingLevel)
{
    const uint8_t tab = nestingLevel * defaultTabSize; 

    printWhiteSpaces(tab);
    printTag(object);
    printfLineSpacing(defaultLineSpacing);
    printWhiteSpaces(tab);
    printf("LEN - %zu %s\n", object->length, (object->length == 1 ? "byte" : "bytes"));
    printfLineSpacing(defaultLineSpacing);

    if (object->type == BTLV_PRIMITIVE && object->length > 0) {
        printWhiteSpaces(tab);
        printPrimitiveVal(object->valueField.value, object->length);
    }

    printfLineSpacing(defaultElementSpacing);

    return BTLV_DEPTH_NAVIGATION_STEP_INTO;
}

BTLV_objectPrintCallback
BTLV_getDefaultNavigatorPrinter(void)
{
    return defaultNavigatorPrinter;
}

void
BTLV_setDefaultNavigatorPrinterTabSize(const uint8_t tabSize)
{
    defaultTabSize = tabSize;
}

void
BTLV_setDefaultNavigatorPrinterLineSpacing(const uint8_t lineSpacing)
{
    defaultLineSpacing = lineSpacing;
}

void
BTLV_setDefaultNavigatorPrinterElementSpacing(const uint8_t elementSpacing)
{
    defaultElementSpacing = elementSpacing;
}