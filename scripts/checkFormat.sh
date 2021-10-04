#!/bin/bash

badFilesCounter=0

showFileFormatIssues() {
    TEMP_DIFF_FILE="${1}.tempdiff"
    
    clang-format -style=file $1 > $TEMP_DIFF_FILE

    diff -pu --color $1 $TEMP_DIFF_FILE

    if [ $? -ne 0 ]; then
        badFilesCounter=$(expr $badFilesCounter + 1)
    fi

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

for file in $(find tests -name "*tests.*")
do
    showFileFormatIssues $file
done

echo -e "\n"
echo -e "----------------------------"
echo -e "   $badFilesCounter files bad formatted"
echo -e "----------------------------"
echo -e "\n"
