#ifndef BTLV_LIB_TESTS_SETUPS_H
#define BTLV_LIB_TESTS_SETUPS_H

#include "testsdefs.h"

// =======================
/* Version string
 *
 * fixture format: pointer to a string with lib version
 */
DECLARE_SETUP_FUNC(btlvVersionString);
DECLARE_TEARDOWN_FUNC(btlvVersionString);

// =======================
/* Only TAG field with class of universal type
 *
 * fixture format: pointer to a single byte holding a TAG
 */
DECLARE_SETUP_FUNC(btlvUniversalClassDataObject);
DECLARE_TEARDOWN_FUNC(btlvUniversalClassDataObject);

// =======================
/* Only TAG field with class of application type
 *
 * fixture format: pointer to a single byte holding a TAG
 */
DECLARE_SETUP_FUNC(btlvApplicationClassDataObject);
DECLARE_TEARDOWN_FUNC(btlvApplicationClassDataObject);

// =======================
/* Only TAG field with class of context-specific type
 *
 * fixture format: pointer to a single byte holding a TAG
 */
DECLARE_SETUP_FUNC(btlvContextSpecificClassDataObject);
DECLARE_TEARDOWN_FUNC(btlvContextSpecificClassDataObject);

// =======================
/* Only TAG field with class of private type
 *
 * fixture format: pointer to a single byte holding a TAG
 */
DECLARE_SETUP_FUNC(btlvPrivateClassDataObject);
DECLARE_TEARDOWN_FUNC(btlvPrivateClassDataObject);

// =======================
/* Only TAG field with of type primitive
 *
 * fixture format: pointer to a single byte holding a TAG
 */
DECLARE_SETUP_FUNC(btlvTagPrimitiveTypeDataObject);
DECLARE_TEARDOWN_FUNC(btlvTagPrimitiveTypeDataObject);

// =======================
/* Only TAG field with of type constructed
 *
 * fixture format: pointer to a single byte holding a TAG
 */
DECLARE_SETUP_FUNC(btlvTagConstructedTypeDataObject);
DECLARE_TEARDOWN_FUNC(btlvTagConstructedTypeDataObject);

// =======================
/* Only LENGTH field 1-byte long
 *
 * fixture format: pointer to a single byte holding a LENGTH
 */
DECLARE_SETUP_FUNC(btlvLengthFieldSingleByteDataObject);
DECLARE_TEARDOWN_FUNC(btlvLengthFieldSingleByteDataObject);

// =======================
/* Only LENGTH field 2 bytes long
 *
 * fixture format: pointer to two bytes holding a LENGTH
 */
DECLARE_SETUP_FUNC(btlvLengthFieldTwoBytesDataObject);
DECLARE_TEARDOWN_FUNC(btlvLengthFieldTwoBytesDataObject);

// =======================
/* Only LENGTH field 3 bytes long
 *
 * fixture format: pointer to 3 bytes holding a LENGTH
 * which is enough to fill up 16 bits integer type
 */
DECLARE_SETUP_FUNC(btlvLengthFieldFillShortIntDataObject);
DECLARE_TEARDOWN_FUNC(btlvLengthFieldFillShortIntDataObject);

// =======================
/* Only LENGTH field 10 bytes long
 *
 * fixture format: pointer to 10 bytes holding a LENGTH
 * which is enough to cause overflow on 64 bits integer types
 */
DECLARE_SETUP_FUNC(btlvLengthFieldForceOverflowDataObject);
DECLARE_TEARDOWN_FUNC(btlvLengthFieldForceOverflowDataObject);

// =======================
/* Only LENGTH field, bad encoded
 *
 * fixture format: pointer to bad encoded length field byte block
 */
DECLARE_SETUP_FUNC(btlvLengthFieldForceBadEncodedDataObject);
DECLARE_TEARDOWN_FUNC(btlvLengthFieldForceBadEncodedDataObject);

// =======================
/* TLV data object of type primitive
 *
 * fixture format: pointer to a BTLV_DataObject primitive
 */
DECLARE_SETUP_FUNC(btlvPrimitiveDataObject);
DECLARE_TEARDOWN_FUNC(btlvPrimitiveDataObject);

// =======================
/* TLV data object of type constructed
 *
 * fixture format: pointer to a BTLV_DataObject constructed
 */
DECLARE_SETUP_FUNC(btlvConstructedDataObject);
DECLARE_TEARDOWN_FUNC(btlvConstructedDataObject);

// =======================
/* TLV data object array
 *
 * fixture format: pointer to a BTLV_DataObject array
 */
DECLARE_SETUP_FUNC(btlvConstructedDataObjectArray);
DECLARE_TEARDOWN_FUNC(btlvConstructedDataObjectArray);


// =======================
/* 1-byte TAG TLV data object of type primitive
 *
 * fixture format: pointer to byte holding primitive TLV object
 */
DECLARE_SETUP_FUNC(btlvSingleByteTagPrimitiveDataObject);
DECLARE_TEARDOWN_FUNC(btlvSingleByteTagPrimitiveDataObject);

// =======================
/* multi-byte TAG TLV data object of type primitive
 *
 * fixture format: pointer to byte block holding primitive TLV object
 */
DECLARE_SETUP_FUNC(btlvMultiByteTagPrimitiveDataObject);
DECLARE_TEARDOWN_FUNC(btlvMultiByteTagPrimitiveDataObject);

// =======================
/* 1-byte length TLV data object of type primitive
 *
 * fixture format: pointer to byte block holding primitive TLV object
 */
DECLARE_SETUP_FUNC(btlvSingleByteLenPrimitiveDataObject);
DECLARE_TEARDOWN_FUNC(btlvSingleByteLenPrimitiveDataObject);

// =======================
/* multi-byte length TLV data object of type primitive
 *
 * fixture format: pointer to byte block holding primitive TLV object
 */
DECLARE_SETUP_FUNC(btlvMultiByteLenPrimitiveDataObject);
DECLARE_TEARDOWN_FUNC(btlvMultiByteLenPrimitiveDataObject);

// =======================
/* byte block TLV data object of type constructed (1 nesting level)
 *
 * fixture format: pointer to byte block holding constructed TLV object
 */
DECLARE_SETUP_FUNC(btlvSingleNestingByteBlockConstructedDataObject);
DECLARE_TEARDOWN_FUNC(btlvSingleNestingByteBlockConstructedDataObject);

// =======================
/* byte block TLV data object of type constructed (several nesting levels)
 *
 * fixture format: pointer to byte block holding constructed TLV object
 */
DECLARE_SETUP_FUNC(btlvMultiNestingByteBlockConstructedDataObject);
DECLARE_TEARDOWN_FUNC(btlvMultiNestingByteBlockConstructedDataObject);

// =======================
/* byte block TLV data object of type constructed (several nesting levels
 * and more than one root)
 *
 * fixture format: pointer to byte block holding constructed TLV object with
 * more than one root
 */
DECLARE_SETUP_FUNC(btlvMultiRootByteBlockConstructedDataObject);
DECLARE_TEARDOWN_FUNC(btlvMultiRootByteBlockConstructedDataObject);

// =======================
/* byte block TLV data object of type primitive (without expected result)
 *
 * fixture format: pointer to byte block holding primitive TLV object
 */
DECLARE_SETUP_FUNC(btlvBadEncodedPrimitiveDataObject);
DECLARE_TEARDOWN_FUNC(btlvBadEncodedPrimitiveDataObject);

// =======================
/* byte block TLV data object of type constructed (without expected result)
 *
 * fixture format: pointer to byte block holding constructed TLV object
 */
DECLARE_SETUP_FUNC(btlvBadEncodedConstructedDataObject);
DECLARE_TEARDOWN_FUNC(btlvBadEncodedConstructedDataObject);

#endif // BTLV_LIB_TESTS_SETUPS_H