#!/bin/bash

exitWithError() {
    echo -e "formatCodeFiles failed to execute\n"
    echo -e "reason: $1"

    exit 1
}

# $1 folder where to search for files
# $2 files name pattern
formatFiles() {
    for header in $(find ${1} -name "${2}" -type f)
    do
        clang-format -i -style=file $header
    done
}

# Checking if clang-format is available
clang-format --version 2>&1 1>/dev/null

if [ $? -ne 0 ]; then
    exitWithError "clang-format command is need and was not found."
fi

# BTLV Lib headers
formatFiles "src/include" "*.h"

# BTLV Lib sources
formatFiles "src" "*.c"

# Some tests headers and sources
formatFiles "tests" "tests.h"
formatFiles "tests" "tests.c"

# Examples headers and sources
formatFiles "examples" "*.c"
