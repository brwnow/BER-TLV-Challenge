#!/bin/bash

redfont='\033[0;31m'
greenfont='\033[0;32m'
nocolor='\033[0m'

badFilesCounter=0
badFilesList=

exitWithError() {
    echo -e "checkFormat failed to execute\n"
    echo -e "reason: $1"

    exit 1
}

showFileFormatIssues() {
    TEMP_DIFF_FILE="${1}.tempdiff"
    
    clang-format -style=file $1 > $TEMP_DIFF_FILE

    diff -pu --color $1 $TEMP_DIFF_FILE

    if [ $? -ne 0 ]; then
        badFilesCounter=$(expr $badFilesCounter + 1)
        badFilesList="$badFilesList $1"
    fi

    rm -f $TEMP_DIFF_FILE
}

showCheckingResult() {
    echo -e "----------------------------"

    if [ $badFilesCounter -gt 0 ]; then
        echo -e "   ${redfont}$badFilesCounter files bad formatted\n"

        for file in $badFilesList; do
            echo -e $file
        done
    else
        echo -e "      ${greenfont}Everything is OK"
    fi

    echo -e "${nocolor}----------------------------"
}

# Checking if clang-format is available
clang-format --version 2>&1 1>/dev/null

if [ $? -ne 0 ]; then
    exitWithError "clang-format command is need and was not found."
fi

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

showCheckingResult