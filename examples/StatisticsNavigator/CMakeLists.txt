add_executable(statisticsNavigator
    main.c
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