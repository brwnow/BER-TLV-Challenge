add_executable(customPrintFunction
    main.c
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