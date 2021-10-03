# BTLV Lib

A library handful for parsing and printing BER-TLV objects.

## Summary
1. [Building](#building)
    - [Info](#info)
    - [Options](#options)
    - [Native Linux building](#native-linux-building)
    - [Cross-compiling building](#cross-compiling-building)
    - [Installing](#installing)
2. [Documentation](#documentation)
3. [Formating source code properly](#formating-source-code-properly)
4. [Testing](#testing)

## Building

### Info

BTLV Lib build is based on camke. This build was tested for cmake 3.16, for this reason this version is set as minimum  required, which doesn't mean it wont work on older cmake versions. Also it was tested for Linux (Ubuntu 20.04) on x86 archtecture, compiled and linked with gcc 9.3.0

### Options

There are build options that may be enabled/disabled through cmake CLI or cmake-gui. Following there is a list of build options and a briefing explanation about them

* `BUILD_UNIT_TESTS` Option to enable/disable build of unit tests. This option is `OFF` by default.

### Native Linux building

1. Create a `build` folder within BTLV project root path `mkdir build` + `cd build`
1. Generate the Makefile running `cmake ..` or `cmake-gui ..`
1. Compile and link binaries running `make`
1. Install final build binaries and headers running `make install`

### Cross-compiling building

1. TODO

### Installing

The artifacts produced at the end of the building proccess are installed by default at the folder `install` located at the rootpath of BTLV project. It's possible to customize the install location by setting cmake's variable `CMAKE_INSTALL_PREFIX` through CLI or cmake-gui.

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

## Testing

There are unit tests implemented for most of BTLV Lib functions. In order to test your additions on lib's code, you must build unit tests (see instructions at section [Building](#building)) and install it (see [Installing](#installing)). At install folder, you can find unit tests executable at `tests` folder. Run `unitTests` and check it out the result of unit tests run.