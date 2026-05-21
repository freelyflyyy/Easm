

add_library(easm STATIC "easm.cpp" "easm.h")

target_enable_utf8(easm)

target_include_directories(easm PUBLIC "${CMAKE_SOURCE_DIR}")
