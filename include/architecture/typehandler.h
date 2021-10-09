#ifndef BTLV_LIB_TYPE_HANDLER_H
#define BTLV_LIB_TYPE_HANDLER_H

#include <stddef.h>
#include <stdint.h>

#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ && \
    __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ && \
    __BYTE_ORDER__ != __ORDER_PDP_ENDIAN__
#   error "Host platform endianness is not supported"
#endif

/**
 * @brief Receives a pointer to a block of memory with big endian encoded integer and cast it
 * to size_t, considering the proper endianness of host platform.
 *
 * @param[in] memblock Pointer to block of memory with big endian encoded integer.
 *
 * @return Returns given memory block properly casted to size_t.
 *
 */
size_t
BTLV_castBigEndianBlockToSizeT(const void *const memblock);

#endif // BTLV_LIB_TYPE_HANDLER_H