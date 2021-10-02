cmake_minimum_required(VERSION 3.16)

project(btlv VERSION 0.0.1 DESCRIPTION "BER-TLV parsing library")

option(BUILD_UNIT_TESTS "Enable/Disable build of unit tests" OFF)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

configure_file(btlvConfig.h.in btlvConfig.h)

set(HEADERS_PATH
    ${HEADERS_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(btlv SHARED
    src/bertlv.c
)

set_target_properties(btlv PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(btlv PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(btlv PROPERTIES PUBLIC_HEADER ${HEADERS_PATH}/bertlv.h)

target_include_directories(btlv PUBLIC "${PROJECT_BINARY_DIR}" "${HEADERS_PATH}")

install(TARGETS btlv
    LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/install/lib
    PUBLIC_HEADER DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/install/include
)