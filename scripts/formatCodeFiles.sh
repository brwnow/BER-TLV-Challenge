#!/bin/bash

for header in $(find include -name "*.h")
do
    clang-format -i -style=file $header
done

for source in $(find src -name "*.c")
do
    clang-format -i -style=file $source
done

for source in $(find tests -name "*tests.*")
do
    showFileFormatIssues $source
done
