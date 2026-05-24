set(EASM_BASE_HEADERS
    "base/base.h"
    "base/type.h"
    "base/version.h"
)

set(EASM_CORE_HEADERS
    "core/codebuffer.h"
)

set(EASM_CORE_SOURCES
    "core/codebuffer.cpp"
)

set(EASM_HEADERS
    ${EASM_BASE_HEADERS}
    ${EASM_CORE_HEADERS}
)

set(EASM_SOURCES
    ${EASM_CORE_SOURCES}
)


add_library(easm STATIC ${EASM_HEADERS} ${EASM_SOURCES})
set_target_properties(easm PROPERTIES LINKER_LANGUAGE CXX)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${EASM_HEADERS} ${EASM_SOURCES})

target_enable_utf8(easm)

target_include_directories(easm PUBLIC "${CMAKE_SOURCE_DIR}")
