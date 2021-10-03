#!/bin/bash

showFileFormatIssues() {
    TEMP_DIFF_FILE="${1}.tempdiff"
    
    clang-format -style=file $1 > $TEMP_DIFF_FILE
    diff -pu --color $1 $TEMP_DIFF_FILE
    
    rm -f $TEMP_DIFF_FILE
}

for header in $(find include -name "*.h")
do
    showFileFormatIssues $header
done

for source in $(find src -name "*.c")
do
    showFileFormatIssues $source
done

