cmake_minimum_required (VERSION 3.10)
project ("Easm")

include(cmake_utils/auto_target_enable_utf8.cmake)
include(cmake_utils/setup_project_compile_options.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

enable_testing()

# 包含子项目。
add_subdirectory ("easm")
add_subdirectory ("easm-testing")

setup_project_compile_options(easm)
setup_project_compile_options(easm-testing)
