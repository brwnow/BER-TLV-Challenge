#include "btlv_test_setups.h"

#include <stdlib.h>

#include "btlvConfig.h"

// =======================
// Empty list
DECLARE_SETUP_FUNC(btlvVersionString) {
    static char *btlvVersionStr = BTLV_VERSION_MAJOR "." BTLV_VERSION_MINOR "." BTLV_VERSION_PATCH;

    FIXTURE_CREATE(fixture, 1);
    FIXTURE_INDEX(fixture, 0) = btlvVersionStr;

    FIXTURE_RETURN(fixture);
}

DECLARE_TEARDOWN_FUNC(btlvVersionString) {
    free(fixture);
}