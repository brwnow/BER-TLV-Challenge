#include "architecture/typehandler.h"

size_t
BTLV_castBigEndianBlockToSizeT(const void *const memblock)
{
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    return (*(const size_t *)(memblock))
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    uint8_t castedResult[sizeof(size_t)];

    // loop unwinding may occurr and optimize this
    for (register size_t i = 0; i < sizeof(size_t); ++i) {
        castedResult[sizeof(size_t) - i - 1] = ((const uint8_t *)memblock)[i];
    }

    return *((size_t *)castedResult);
#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
    uint8_t castedResult[sizeof(size_t)];

    castedResult[0] = ((const uint8_t *)memblock)[1];
    castedResult[1] = ((const uint8_t *)memblock)[0];
    castedResult[2] = ((const uint8_t *)memblock)[3];
    castedResult[3] = ((const uint8_t *)memblock)[2];

    return *((size_t *)castedResult);
#else
    return 0;
#endif
}