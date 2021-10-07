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