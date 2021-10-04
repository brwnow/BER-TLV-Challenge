#ifndef BTLV_LIB_SETUPS_H
#define BTLV_LIB_SETUPS_H

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

#endif // BTLV_LIB_SETUPS_H