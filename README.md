# BTLV Lib

A library handful for parsing and printing BER-TLV objects.

![CI status](https://app.travis-ci.com/brwnow/BER-TLV-Challenge.svg?branch=develop)

## Summary
1. [First steps after cloning](#first-steps-after-cloning)
2. [Environment Setup](#environment-setup)
3. [Building](#building)
    - [Info](#info)
    - [Type](#type)
    - [Options](#options)
    - [Native Linux building](#native-linux-building)
    - [Installing](#installing)
4. [API Documentation](#api-documentation)
5. [Formating source code properly](#formating-source-code-properly)
6. [Testing](#testing)
7. [Version Bumping](#version-bumping)
8. [Contributing](#contributing)
9. [CI/CD](#cicd)

## First steps after cloning

It's quite important that you guarantee that submodule `munit` is ready to be built along with unit tests. After cloning this repo, you must run the following command to initialize submodule:

`git submodule update --init`

## Environment Setup

In order to use all project tools and scripts, you must prepare your environment installing some packages

* **clang-format** `sudo apt install clang-format` (only version 6.0.0 was tested)
* **doxygen** `sudo apt-get install -y doxygen` (tested for version 1.8.13)
## Building

### Info

BTLV Lib build is based on Cmake meta-maker. This build was tested for cmake 3.16, for this reason this version is set as minimum  required, which doesn't mean it wont work on older Cmake versions. Also it was tested for `Linux (Ubuntu 20.04 and 18.04)` on `x86 architecture`, compiled and linked with `gcc 9.3.0 and 7.5.0`

### Type

To build for `release` or `debug` you must set the Cmake variable `CMAKE_BUILD_TYPE` to `RELEASE` or `DEBUG` through CLI by calling `cmake -DCMAKE_BUILD_TYPE=RELEASE|DEBUG .....` or through cmake-gui setting `RELEASE` or `DEBUG` on `CMAKE_BUILD_TYPE` field.

### Options

There are build options that may get enabled/disabled through cmake CLI or cmake-gui. Following there is a list of build options and a briefing explanation about them

* `BUILD_UNIT_TESTS` Option to enable/disable build of unit tests. This option is `ON` by default.
* `BUILD_EXAMPLES` Option to enable/disable build of examples of lib usage. This option is `ON` by default.

### Native Linux building

1. Create a `build` folder within BTLV project root path `mkdir build` + `cd build`
1. Generate the Makefile running `cmake ..` or `cmake-gui ..`
1. Compile and link binaries running `make` + `make install`

### Installing

The command `make install` move artifacts produced at the end of the building proccess to the folder `install` located at the rootpath of BTLV project. It's possible to customize the install location by setting cmake's variable `CMAKE_INSTALL_PREFIX` through CLI or cmake-gui.

The final BTLV Lib binary (`.so`) and its header are installed at install folder inside `libbtlv` folder. Unit tests are installed at subfolder `tests` and all usage examples are installed at subfolder `examples`. All final executables are installed with `RUNPATH` set to the location of installment of `libbtlv`

## API Documentation

The BTLV Lib is documented with doxygen. The documentation is versioned together with the code everytime the API changes. You can check the documentation at the location `doc\generated\html\index.html` whithin BTLV Lib project.

If you have to change the contract of the API and need to update the documentation, you must rebuild the documentation and commit new documentation version. Check the instructions bellow on how to update the documentation

1. Update `PROJECT_NUMBER` in `doc/Doxyfile` to the new version of BTLV Lib
1. At the root of BTLV Lib project folder, run `doxygen doc/Doxyfile`
1. Commit everything that has been modified inside `doc/generated`

## Formating source code properly

You must install clang-format in order to use code formatting utilities of this project. Check section [Environment Setup](#environment-setup) for instruction about how to install clang-format and versions that was tested for this project.

There is a `.clang-format` file with specifications for code style in the rootpath of the project. There are two scripts related to code linting, a script for checking the code format that presents a diff between current code format and expected code format, and a script that fixes the code format automatically (if you trust it won't break your code). Both scripts must be ran from project's rootpath.

* Checking code format: `./scripts/checkFormat.sh`
* Fixing code format: `./scripts/formatCodeFiles.sh`

## Testing

There are unit tests implemented for most of BTLV Lib functions. In order to test your additions on lib's code, you must build unit tests (see instructions at section [Building](#building)) and install it (see [Installing](#installing)). At install folder, you can find unit tests executable at `tests` folder. Run `unitTests` and check it out the result of unit tests run.

## Version Bumping

Version bumping is quite simple, just update the version of the project at `CMakeLists.txt` at the root of the project and `PROJECT_NUMBER` at `doc/Doxyfile` to the new version and generated the documentation again (check [API Documentation](#api-documentation) section).

## Contributing

For this project i'm using simplified gitflow-based workflow. It's up to you istalling a tool to help on this workflow or not.

There are two special branches:

* **develop** that's the branch from which you should open branches for features and bugfixes and merge back to it
* **main** that's the branch to merge develop when a version is ready

I don't have releases branchs for while.

Following there is the types of branches to work on worfkflow of this project:

* **features** `feature/branchNameCamelCased` branches for new features or update/refactor of existing features
* **bugfix** `bugfix/branchNameCamelCased` branches for bugfix that will be merged into `develop` branch
* **hotfix** `hotfix/branchNameCamelCased` branches for bugfix that will be opened from and merged dinto `main` branch (a cherry-pick to develop may occurr). This is used when some bugfix is quite important to fix a critical bug.

## CI/CD

For while it's only CI, there is no CD yet.

CI performs some verifications before allowing a pull request to be merged. Following there is a list of verifications CI performs

* **Sources files linting** check if for some reason the files bypassed the githook for pre-push which run the checkFormat script to guarantee that everything is being pushed is well formatted.
* **Building** check if project is building before allowing the PR to be merged.
* **Running Tests** check if unit tests are passing before allowing the PR to be merged.

At the beginning of this README you can find the CI status for develop branch.