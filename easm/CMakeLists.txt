set(EASM_INTERNAL_SUPPORT_HEADERS
    "internal/support/api-build_p.h"
    "internal/support/api-config.h"
)

set(EASM_INTERNAL_MEMORY_HEADERS
    "internal/memory/virtmem.h"
    "internal/memory/zone.h"
)

set(EASM_INTERNAL_MEMORY_SOURCES
    "internal/memory/virtmem.cpp"
    "internal/memory/zone.cpp"
)

set(EASM_HEADERS
    ${EASM_INTERNAL_SUPPORT_HEADERS}
    ${EASM_INTERNAL_MEMORY_HEADERS}
)

set(EASM_SOURCES
    ${EASM_INTERNAL_MEMORY_SOURCES}
)

add_library(easm STATIC ${EASM_HEADERS} ${EASM_SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${EASM_HEADERS} ${EASM_SOURCES})

target_enable_utf8(easm)

target_include_directories(easm PUBLIC "${CMAKE_SOURCE_DIR}")
