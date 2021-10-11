# INTRODUCTION

BTLV Lib is a simple and small lib to help parsing BER-TLV data objects. In this document you will find BTLV Lib API reference. For detailed information about lib API functions visit file **bertlv.h**.

Although there is documentation for several headers files, it's recommended to use in your project only **bertlv.h** header file and the API exposed on it. The other header files are more for the core of lib implementation.

### API Files

#### Main Header

* bertlv.h

#### Secondary Headers

* tlvparser.h
* printinghelper.h
* typehandler.h

### Examples

You can find usage examples for BTLV Lib in the project repository. Take a look that the folder examples, at the root of the project folder, there are several usage examples that may help you quickstart on BTLV Lib usage.

### Basic instruction

BTLV Lib does not protect its function for thread safety for the sake of keep its implementation as simple as possible, also avoid portability issues. So when using the lib API, consider that the lib's user must guarantee thread safety for all data given to lib's API.

Most important functions of lib's API are `BTLV_decodeTlvObject`, `BTLV_depthFirstNavigateObject` and `BTLV_destroyTlvObjectArray`.

With `BTLV_decodeTlvObject` you can parse a BER-TLV data object. It returns an array of data objects through an output parameter. This decision was made as a handful resource to parse at once a memory block that contains more than one data object. This way the given memory block is parsed whole at once and the algorithm extract all data objects that was encoded in that.

With `BTLV_depthFirstNavigateObject` in conjuntction with a callback function (check `BTLV_objectPrintCallback` documentation) you can navigatin each of the data objects returned by `BTLV_decodeTlvObject`. This callback has an signture that give the lib's user controls over the navigation through return codes (which are commands to the navigator algorithm).

And for the last, with `BTLV_destroyTlvObjectArray` you can free all memory that was allocated by `BTLV_decodeTlvObject` at once.