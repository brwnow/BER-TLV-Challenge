cmake_minimum_required(VERSION 3.16)

project(btlv VERSION 0.0.3 DESCRIPTION "BER-TLV parsing library")

option(BUILD_UNIT_TESTS "Enable/Disable build of unit tests" ON)
option(BUILD_EXAMPLES "Enable/Disable build of lib usage examples" ON)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install" CACHE PATH "Destination path where to install build products" FORCE)
endif()

# Trick extracted from internet
# source: https://blog.kitware.com/cmake-and-the-default-build-type/
set(DEFAULT_BUILD_TYPE "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")

    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}"
        CACHE STRING "Choose the type of build." FORCE
    )

    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release"
    )
endif()

string( TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWERCASE)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

configure_file(btlvConfig.h.in btlvConfig.h)

set(BTLV_HEADERS_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

set(BTLV_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/libbtlv/${CMAKE_BUILD_TYPE_LOWERCASE})

# BTLV Lib sources dir
add_subdirectory(src)

# Tests dir, if enabled
if(${BUILD_UNIT_TESTS})
    add_subdirectory(tests)
endif()

# Examples dir, if enabled
if(${BUILD_EXAMPLES})
    add_subdirectory(examples)
endif()