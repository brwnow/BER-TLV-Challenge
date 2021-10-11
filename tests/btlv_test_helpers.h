#ifndef BTLV_LIB_TESTS_HELPERS_H
#define BTLV_LIB_TESTS_HELPERS_H

#include <stdbool.h>

#include "bertlv.h"

bool
compareBtlvDataObjects(const BTLV_DataObject* const tlvObjectA, const BTLV_DataObject* const tlvObjectB);

#endif // BTLV_LIB_TESTS_HELPERS_H