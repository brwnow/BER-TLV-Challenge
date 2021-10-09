#include "tlvparser.h"

#include "architecture/typehandler.h"

BTLV_ReturnCode
BTLV_tagFieldParse(const uint8_t *const tlvObjectBuffer,
                   const size_t objectBufferSize,
                   BTLV_DataObject *const dataElement)
{
    if (tlvObjectBuffer == NULL || dataElement == NULL)
        return BTLV_INVALID_PARAMETER;

    if (objectBufferSize == 0)
        return BTLV_BAD_TLV_ENCODING;

    size_t currentByte = 0;

    dataElement->class = TAG_GET_CLASS(tlvObjectBuffer[currentByte]);
    dataElement->type = TAG_GET_TYPE(tlvObjectBuffer[currentByte]);
    dataElement->tag[0] = tlvObjectBuffer[currentByte];
    dataElement->tagSize = 1;

    // Check if there is subsequent byte at tag field
    if (TAG_HAS_SUBSEQUENT_BYTE(tlvObjectBuffer[currentByte])) {
        // Checking if input tlv buffer size supports one more byte in tag field
        if (objectBufferSize > 1) {
            ++currentByte;

            dataElement->tagSize = 2;
            dataElement->tag[1] = tlvObjectBuffer[currentByte];

            return BTLV_RET_OK;
        } else {
            // TAG has more bytes than input buffer size supports
            return BTLV_BAD_TLV_ENCODING;
        }
    } else {
        return BTLV_RET_OK;
    }
}

BTLV_ReturnCode
BTLV_lengthFieldParse(const uint8_t *const tlvObjectBuffer,
                      const size_t objectBufferSize,
                      size_t *const length,
                      size_t *const lengthFieldByteCount)
{
    if (tlvObjectBuffer == NULL || length == NULL || lengthFieldByteCount == NULL)
        return BTLV_INVALID_PARAMETER;

    // Clean up output parameters
    *lengthFieldByteCount = 0;
    *length = 0;

    // If there is no space in buffer, parsing is impossible
    if (objectBufferSize == 0)
        return BTLV_BAD_TLV_ENCODING;

    if (LENGTH_HAS_SUBSEQUENT_BYTES(tlvObjectBuffer[0])) {
        uint8_t fieldBytesCount = LENGTH_GET_SUBSEQUENT_BYTES_COUNT(tlvObjectBuffer[0]);

        // If there is not enough buffer to parse the length field, it's bad encoded
        if(fieldBytesCount + 1u > objectBufferSize) {
            *lengthFieldByteCount = objectBufferSize;

            return BTLV_BAD_TLV_ENCODING;
        }

        // Field bytes amount + Counting heading byte
        *lengthFieldByteCount = fieldBytesCount + 1u;

        // Amount of bytes in length field is greater than size_t size ?
        if(fieldBytesCount > sizeof(size_t)) {
            // Truncating bytes from length field that doesn't fit a size_t type
            *length = BTLV_castBigEndianBlockToSizeT(tlvObjectBuffer + (*lengthFieldByteCount - sizeof(size_t)));

            return BTLV_TYPE_OVERFLOW;
        } else {
            // Casting length bytes to size_t and adjusting its bytes position
            *length = BTLV_castBigEndianBlockToSizeT(tlvObjectBuffer + 1) >> ((sizeof(size_t) - fieldBytesCount) * 8);

            return BTLV_RET_OK;
        }
    } else {
        // If there is no subsequent bytes, return the heading byte as-is
        // also byte count can only be 1
        *length = tlvObjectBuffer[0];
        *lengthFieldByteCount = 1;

        return BTLV_RET_OK;
    }
}