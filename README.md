# BTLV Lib

A library handful for parsing and printing BER-TLV objects.

## Summary
1. [Building](#building)
    - [Native Linux building](#native-linux-building)
    - [Cross-compiling building](#cross-compiling-building)
1. [Documentation](#documentation)
1. [Formating source code properly](#formating-source-code-properly)

## Building

BTLV Lib build is based on camke. This build was tested for cmake 3.16, for this reason this version is set as minimum  required, which doesn't mean it wont work on older cmake versions. Also it was tested for Linux (Ubuntu 20.04) on x86 archtecture and gcc 9.3.0

### Native Linux building

1. Create a `build` folder within BTLV project root path `mkdir build` + `cd build`
1. Generate the Makefile running `cmake ..`
1. Compile and link binaries running `cmake --build .`
1. Install final build binaries and headers running `cmake --install`

### Cross-compiling building

1. TODO

## Documentation

The BTLV Lib is documented with doxygen. The documentation is versioned together with the code everytime the API changes. You can check the documentation at the location `\doc\generated\html\index.html` whithin BTLV Lib project.

If you have to change the contract of the API and need to update the documentation, you must rebuild the documentation and commit new documentation version. Check the instructions bellow on how to update the documentation

1. Update `PROJECT_NUMBER` in `doc/Doxyfile` to the new version of BTLV Lib
1. At the root of BTLV Lib project folder, run `doxygen doc/Doxyfile`
1. Commit everything that has been modified inside `doc/generated`

## Formating source code properly

You must install clang-format in order to use code formatting utilities of this project. It can be installed on Ubuntu by running `sudo apt install clang-format` on terminal.

There is a `.clang-format` file with specifications for code style in the rootpath of the project. There are two scripts related to code linting, a script for checking the code format that presents a diff between current code format and expected code format, and a script that fixes the code format automatically (if you trust it won't break your code). Both scripts must be ran from project's rootpath.

* Checking code format: `./scripts/checkFormat.sh`
* Fixing code format: `./scripts/formatCodeFiles.sh`