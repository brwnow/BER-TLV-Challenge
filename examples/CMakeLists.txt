set(CMAKE_INSTALL_RPATH ${BTLV_INSTALL_PATH})

set(EXAMPLES_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/examples/${CMAKE_BUILD_TYPE_LOWERCASE})

add_subdirectory(CustomNavigator)
add_subdirectory(CustomPrintFunction)
add_subdirectory(DefaultPrintFunction)
add_subdirectory(StatisticsNavigator)