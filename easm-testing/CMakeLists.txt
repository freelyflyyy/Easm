# CMakeList.txt: easm-testing 的 CMake 项目。

add_executable (easm-testing "main.cpp")
target_enable_utf8(easm-testing)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET easm-testing PROPERTY CXX_STANDARD 20)
endif()
