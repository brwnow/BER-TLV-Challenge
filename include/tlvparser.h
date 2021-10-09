#ifndef BTLV_LIB_TLV_PARSER_H
#define BTLV_LIB_TLV_PARSER_H

#include "bertlv.h"

// Bit mask to filter a TAG property
#define TAG_CLASS_MASK 0xC0
#define TAG_TYPE_MASK 0x20
#define TAG_NUMBER_MASK 0x1F

// Amount of bits to shift to right in order to get TAG property value
// after applying the property mask
#define TAG_CLASS_SHIFT 6
#define TAG_TYPE_SHIFT 5

// Get the value of specific property of given TAG
#define TAG_GET_CLASS(tag) (((tag)&TAG_CLASS_MASK) >> TAG_CLASS_SHIFT)
#define TAG_GET_TYPE(tag) (((tag)&TAG_TYPE_MASK) >> TAG_TYPE_SHIFT)

// Get the tag number for first byte of tag. Second byte is already only the number.
#define TAG_GET_NUMBER(tag) ((tag)&TAG_NUMBER_MASK)

// Tag number which means that there is subsequent byte.
// Basically the value of tag number mask. This macro exists
// to improve code readability
#define TAG_SUBSEQUENT_NUMBER 0x1F

// Check if TAG has a subsequent byte
#define TAG_HAS_SUBSEQUENT_BYTE(tag) (((tag)&TAG_NUMBER_MASK) == TAG_SUBSEQUENT_NUMBER)

// Useful mask to extract information of length field heading byte
#define LENGTH_HEADING_BYTE_MASK 0x80

// Mask to extract value of heading length byte when it indicates the amount
// of subsequent bytes of length field
#define LENGTH_HEADING_BYTE_VAL_MASK 0x7F

// Tells if length heading byte indicates that there is subsequent bytes
#define LENGTH_HAS_SUBSEQUENT_BYTES(headingByte) ((headingByte)&LENGTH_HEADING_BYTE_MASK)

// Extract number of subsequent bytes of length field
#define LENGTH_GET_SUBSEQUENT_BYTES_COUNT(headingByte) ((headingByte)&LENGTH_HEADING_BYTE_VAL_MASK)

// Shifts 1 byte to left (8 bits for most archtecture known to humankind)
#define BYTE_SHIFT_LEFT(X) ((X) << 8)

/**
 * @brief Parses the TAG field of a BER-TLV element
 *
 * @param[in] tlvObjectBuffer The address of the BER-TLV data object block of bytes in memory.
 * @param[in] objectBufferSize Size of the data object block of bytes.
 * @param[out] dataElement A BTLV_DataObject struct which to fill the fields related to TAG field
 *
 * @return Returns BTLV_RET_OK on success.
 * @return Returns BTLV_INVALID_PARAMETER if some problem is found on given arguments.
 * @return Returns BTLV_BAD_TLV_ENCODING if input TLV object byte block is bad encoded and the function
 * fails to extract TAG field properties.
 *
 */
BTLV_ReturnCode
BTLV_tagFieldParse(const uint8_t *const tlvObjectBuffer,
                   const size_t objectBufferSize,
                   BTLV_DataObject *const dataElement);

/**
 * @brief Parses the Length field of a BER-TLV element
 *
 * @param[in] tlvObjectBuffer The address of the BER-TLV data object block of bytes in memory.
 * @param[in] objectBufferSize Size of the data object block of bytes.
 * @param[out] length Output parameter to return the extracted length of the BER-TLV element. When its
 * detected that there is subsequent bytes, this parameter is cleaned to 0. If it fails right after
 * cleaning it up, it will return 0. This output may be overflowed, in this case the function will
 * return the code for type overflow.
 * @param[out] lengthFieldByteCount The amount of bytes of parsed length field, including the first
 * byte that indicates the length of length field in cases the first byte has the most significant
 * bit set on. Byte counting don't stop when an overflow occurs. It only stops if buffer limit is
 * reached.
 *
 * @return Returns BTLV_RET_OK on success.
 * @return Returns BTLV_INVALID_PARAMETER if some problem is found on given arguments.
 * @return Returns BTLV_BAD_TLV_ENCODING if input TLV object byte block is bad encoded and the function
 * fails to extract TAG field properties. If it fails for buffer limitation, it returns the amount of data
 * it was capable of parsing, also byte count returns the amount of byte it was possible to parse until
 * buffer limit.
 * @return Returns BTLV_TYPE_OVERFLOW if an overflow occur during extraction of length field. The length is return
 * anyway, but truncated. The byte count ignores overflow and return the encoded byte count.
 *
 */
BTLV_ReturnCode
BTLV_lengthFieldParse(const uint8_t *const tlvObjectBuffer,
                      const size_t objectBufferSize,
                      size_t *const length,
                      size_t *const lengthFieldByteCount);

#endif // BTLV_LIB_TLV_PARSER_H