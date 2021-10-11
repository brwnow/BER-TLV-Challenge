add_executable(defaultPrintFunction
    main.c
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