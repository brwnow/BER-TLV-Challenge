cmake_minimum_required(VERSION 3.16)

project(btlv VERSION 0.0.2 DESCRIPTION "BER-TLV parsing library")

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
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(BTLV_SOURCES_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(BTLV_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/libbtlv/${CMAKE_BUILD_TYPE_LOWERCASE})

add_library(btlv SHARED
    ${BTLV_SOURCES_PATH}/bertlv.c
    ${BTLV_SOURCES_PATH}/tlvparser.c
    ${BTLV_SOURCES_PATH}/architecture/typehandler.c
    ${BTLV_SOURCES_PATH}/io/printinghelper.c
)

set_target_properties(btlv PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(btlv PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(btlv PROPERTIES PUBLIC_HEADER ${BTLV_HEADERS_PATH}/bertlv.h)

if(MSVC)
    target_compile_options(btlv PRIVATE /W4 /WX)
else()
    target_compile_options(btlv PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_include_directories(btlv PRIVATE "${PROJECT_BINARY_DIR}" "${BTLV_HEADERS_PATH}")

install(TARGETS btlv
    LIBRARY DESTINATION ${BTLV_INSTALL_PATH}
    PUBLIC_HEADER DESTINATION ${BTLV_INSTALL_PATH}/include
)

if(${BUILD_UNIT_TESTS})
    set(UNIT_TESTS_HEADERS_PATHS
        ${CMAKE_CURRENT_SOURCE_DIR}/tests
        ${CMAKE_CURRENT_SOURCE_DIR}/munit
    )

    set(UNIT_TESTS_SOURCES_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    set(MUNIT_FRAMEWORK_SOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/munit)

    SET(CMAKE_INSTALL_RPATH ${BTLV_INSTALL_PATH})

    add_executable(unitTests
        ${MUNIT_FRAMEWORK_SOURCES_PATH}/munit.c
        ${UNIT_TESTS_SOURCES_PATHS}/btlv_test_setups.c
        ${UNIT_TESTS_SOURCES_PATHS}/btlv_test_helpers.c
        ${UNIT_TESTS_SOURCES_PATHS}/btlv_version_tests.c
        ${UNIT_TESTS_SOURCES_PATHS}/btlv_trytocrash_tests.c
        ${UNIT_TESTS_SOURCES_PATHS}/btlv_parsing_tests.c
        ${UNIT_TESTS_SOURCES_PATHS}/btlv_printing_tests.c
        ${UNIT_TESTS_SOURCES_PATHS}/main.c
    )

    target_link_libraries(unitTests btlv)

    target_include_directories(unitTests PRIVATE "${PROJECT_BINARY_DIR}" "${BTLV_HEADERS_PATH}" "${UNIT_TESTS_HEADERS_PATHS}")

    if(MSVC)
        target_compile_options(unitTests PRIVATE /W4 /WX)
    else()
        target_compile_options(unitTests PRIVATE
            -Wall -Wextra -Wpedantic -Werror
            $<$<CONFIG:DEBUG>:-g3>
            $<$<CONFIG:DEBUG>:-Og>
            $<$<CONFIG:RELEASE>:-O3>
        )
    endif()

    install(TARGETS unitTests
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/tests/${CMAKE_BUILD_TYPE_LOWERCASE}
    )
endif()

if(${BUILD_EXAMPLES})
    set(EXAMPLES_SOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/examples)

    set(EXAMPLES_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/examples/${CMAKE_BUILD_TYPE_LOWERCASE})

    # Default Print Function
    add_executable(defaultPrintFunction
        ${EXAMPLES_SOURCES_PATH}/DefaultPrintFunction/main.c
    )

    target_link_libraries(defaultPrintFunction btlv)
    target_include_directories(defaultPrintFunction PRIVATE "${BTLV_HEADERS_PATH}")

    if(MSVC)
        target_compile_options(defaultPrintFunction PRIVATE /W4 /WX)
    else()
        target_compile_options(defaultPrintFunction PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()

    install(TARGETS defaultPrintFunction
        RUNTIME DESTINATION ${EXAMPLES_INSTALL_PATH}
    )

    # Custom Print Function
    add_executable(customPrintFunction
        ${EXAMPLES_SOURCES_PATH}/CustomPrintFunction/main.c
    )

    target_link_libraries(customPrintFunction btlv)
    target_include_directories(customPrintFunction PRIVATE "${BTLV_HEADERS_PATH}")

    if(MSVC)
        target_compile_options(customPrintFunction PRIVATE /W4 /WX)
    else()
        target_compile_options(customPrintFunction PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()

    install(TARGETS customPrintFunction
        RUNTIME DESTINATION ${EXAMPLES_INSTALL_PATH}
    )

    # Statistics Navigator
    add_executable(statisticsNavigator
        ${EXAMPLES_SOURCES_PATH}/StatisticsNavigator/main.c
    )

    target_link_libraries(statisticsNavigator btlv)
    target_include_directories(statisticsNavigator PRIVATE "${BTLV_HEADERS_PATH}")

    if(MSVC)
        target_compile_options(statisticsNavigator PRIVATE /W4 /WX)
    else()
        target_compile_options(statisticsNavigator PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()

    install(TARGETS statisticsNavigator
        RUNTIME DESTINATION ${EXAMPLES_INSTALL_PATH}
    )

    # Custom Navigator
    add_executable(customNavigator
        ${EXAMPLES_SOURCES_PATH}/CustomNavigator/main.c
    )

    target_link_libraries(customNavigator btlv)
    target_include_directories(customNavigator PRIVATE "${BTLV_HEADERS_PATH}")

    if(MSVC)
        target_compile_options(customNavigator PRIVATE /W4 /WX)
    else()
        target_compile_options(customNavigator PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()

    install(TARGETS customNavigator
        RUNTIME DESTINATION ${EXAMPLES_INSTALL_PATH}
    )
endif()