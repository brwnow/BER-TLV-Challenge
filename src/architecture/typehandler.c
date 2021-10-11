#include "architecture/typehandler.h"

size_t
BTLV_castBigEndianBlockToSizeT(const void *const memblock)
{
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    return (*(const size_t *)(memblock))
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    size_t castedResult = 0;
    uint8_t *resultBytes = (uint8_t *)(&castedResult);

    // loop unwinding may occurr and optimize this
    for (register size_t i = 0; i < sizeof(size_t); ++i) {
        resultBytes[sizeof(size_t) - i - 1] = ((const uint8_t *)memblock)[i];
    }

    return castedResult;
#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
    size_t castedResult = 0;
    uint8_t *resultBytes = (uint8_t *)(&castedResult);

    resultBytes[0] = ((const uint8_t *)memblock)[1];
    resultBytes[1] = ((const uint8_t *)memblock)[0];
    resultBytes[2] = ((const uint8_t *)memblock)[3];
    resultBytes[3] = ((const uint8_t *)memblock)[2];

    return castedResult;
#else
    return 0;
#endif
}