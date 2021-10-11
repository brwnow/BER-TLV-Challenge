#include "bertlv.h"

#include <stdio.h>

// Compound BER-TLV data object byte block to be printed
static const uint8_t fciTlvObject[] = {0x6F, 0x1A, 0x84, 0x0E, 0x31, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59,
                                       0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31, 0xA5, 0x08, 0x88, 0x01,
                                       0x02, 0x5F, 0x2D, 0x02, 0x65, 0x6E, 0xE1, 0x0B, 0xC1, 0x03, 0x01,
                                       0x02, 0x03, 0xC2, 0x00, 0xC3, 0x02, 0xAA, 0xBB};

int
main()
{
    // Pointer that will receive the address of array of root data objects extracted from ber-tlv block
    BTLV_DataObject *parsedObjects = NULL;

    // Count control to receive the amount of root data objects extracted
    size_t rootElementsCount = 0;

    // Extracting data objects from given encoded BER-TLV object
    BTLV_ReturnCode ret = BTLV_decodeTlvObject(fciTlvObject, sizeof(fciTlvObject), &parsedObjects, &rootElementsCount);

    if (ret == BTLV_RET_OK) {
        BTLV_printObjectArray(parsedObjects, rootElementsCount);
    } else {
        printf("Error parsing BER-TLV data object. Error code: %d\n", ret);
    }

    // Cleaning memory
    BTLV_destroyTlvObjectArray(parsedObjects, rootElementsCount);

    return 0;
}