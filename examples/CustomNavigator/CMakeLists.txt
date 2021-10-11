add_executable(customNavigator
    main.c
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