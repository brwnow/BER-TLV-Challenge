#!/bin/bash

exitWithError() {
    echo -e "formatCodeFiles failed to execute\n"
    echo -e "reason: $1"

    exit 1
}

# Checking if clang-format is available
clang-format --version 2>&1 1>/dev/null

if [ $? -ne 0 ]; then
    exitWithError "clang-format command is need and was not found."
fi

for header in $(find include -name "*.h")
do
    clang-format -i -style=file $header
done

for source in $(find src -name "*.c")
do
    clang-format -i -style=file $source
done

for file in $(find tests -name "*tests.*")
do
    clang-format -i -style=file $file
done
