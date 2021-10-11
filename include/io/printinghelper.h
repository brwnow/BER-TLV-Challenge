/**
 * @file printinghelper.h
 * @brief Core header for helping on printing TLV objects. Not recommended to use this API directly
 *
 * You'd better use only bertlv.h header and its exposed API. This file and its functions are
 * core functions for BTLV Lib working. Only use this directly if quite needed.
 *
 */

#ifndef BTLV_LIB_PRINTING_HELPER_H
#define BTLV_LIB_PRINTING_HELPER_H

#include <stdint.h>

#include "bertlv.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Gets a navigator callback for the default printer implementation of BTLV Lib.
 *
 * @return Returns the default navigator callback for printing.
 *
 */
BTLV_objectPrintCallback
BTLV_getDefaultNavigatorPrinter(void);

/**
 * @brief Set the tab size for the default navigator printer.
 *
 * @param[in] tabSize the size of tab in amount of whitespaces.
 *
 */
void
BTLV_setDefaultNavigatorPrinterTabSize(const uint8_t tabSize);

/**
 * @brief Set the line spacing between data object fields for the default navigator printer.
 *
 * @param[in] lineSpacing the line spacing in number of empty lines.
 *
 */
void
BTLV_setDefaultNavigatorPrinterLineSpacing(const uint8_t lineSpacing);

/**
 * @brief Set the line spacing between data objects.
 *
 * @param[in] elementSpacing the line spacing in number of empty lines.
 *
 */
void
BTLV_setDefaultNavigatorPrinterElementSpacing(const uint8_t elementSpacing);

#ifdef __cplusplus
}
#endif

#endif // BTLV_LIB_PRINTING_HELPER_H