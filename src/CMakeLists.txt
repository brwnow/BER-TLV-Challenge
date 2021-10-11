add_library(btlv SHARED
    bertlv.c
    tlvparser.c
    architecture/typehandler.c
    io/printinghelper.c
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