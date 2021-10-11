#include "bertlv.h"

#include <stdio.h>

// Compound BER-TLV data object byte block to be printed
static const uint8_t fciTlvObject[] = {0x6F, 0x27, 0x84, 0x0E, 0x31, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59,
                                       0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31, 0xA5, 0x08, 0x88, 0x01,
                                       0x02, 0x5F, 0x2D, 0x02, 0x65, 0x6E, 0xE1, 0x0B, 0xC1, 0x03, 0x01,
                                       0x02, 0x03, 0xC2, 0x00, 0xC3, 0x02, 0xAA, 0xBB};

#include <termios.h>
#include <unistd.h>

// Code from internet. Getting input without echoing it
// not portable, works only on unix based systems
char
getch()
{
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

static void
myPrintTab(const uint8_t tab, const char tabChar)
{
    for (uint8_t i = 0; i < tab; ++i)
        printf("%c", tabChar);
}

BTLV_ObjectPrintCallbackRetVal
getControlCommand(void)
{
    char ch = getch();

    if (ch == 0x1B) {
        ch = getch();

        if (ch == 0x5B) {
            ch = getch();

            switch (ch) {
            case 0x41:
                return BTLV_DEPTH_NAVIGATION_STEP_OUT;
            case 0x42:
                return BTLV_DEPTH_NAVIGATION_STEP_OVER;
            case 0x43:
                return BTLV_DEPTH_NAVIGATION_STEP_INTO;
            case 0x44:
                return BTLV_DEPTH_NAVIGATION_HALT;
            default:
                return BTLV_DEPTH_NAVIGATION_STEP_INTO;
            }
        } else {
            return BTLV_DEPTH_NAVIGATION_HALT;
        }
    } else {
        return BTLV_DEPTH_NAVIGATION_STEP_INTO;
    }
}

static BTLV_ObjectPrintCallbackRetVal
controllerNavigator(const BTLV_DataObject *const object, const uint8_t nestingLevel)
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

    printf(" | %s | %zu bytes\n", object->type == BTLV_PRIMITIVE ? "PRIMITIVE" : "CONSTRUCTED", object->length);
    fflush(stdout);

    return getControlCommand();
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

    printf("NAVIGATE USING ARROWS\n");
    printf("LEFT:  HALT\n");
    printf("RIGHT: Step into (for constructed) | Step over (for primitive)\n");
    printf("DOWN:  Step over (don't expand constructed)\n");
    printf("UP:    Step out (go back 1 nesting level)\n\n");

    printf("ESC + ANY:     HALT\n");
    printf("ANYTHING ELSE: Step into\n\n");

    printf("Starting controlled navigation\n\n");

    for (size_t i = 0; i < rootElementsCount; ++i) {
        ret = BTLV_depthFirstNavigateObject(&(parsedObjects[i]), controllerNavigator);

        if (ret != BTLV_RET_OK) {
            printf("An error has occurred printing of root element #%lu.\nError code: %d\n", i, ret);
        }
    }

    // Cleaning memory
    BTLV_destroyTlvObjectArray(parsedObjects, rootElementsCount);

    return 0;
}