set(UNIT_TESTS_HEADERS_PATHS
    ${CMAKE_SOURCE_DIR}/munit
)

set(MUNIT_FRAMEWORK_SOURCES_PATH ${CMAKE_SOURCE_DIR}/munit)

set(CMAKE_INSTALL_RPATH ${BTLV_INSTALL_PATH})

add_executable(unitTests
    ${MUNIT_FRAMEWORK_SOURCES_PATH}/munit.c
    btlv_test_setups.c
    btlv_test_helpers.c
    btlv_version_tests.c
    btlv_trytocrash_tests.c
    btlv_parsing_tests.c
    btlv_printing_tests.c
    main.c
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