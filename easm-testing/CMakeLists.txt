add_executable (easm-testing "main.cpp")
target_enable_utf8(easm-testing)
target_include_directories(easm-testing PRIVATE "${CMAKE_SOURCE_DIR}")

target_link_libraries(easm-testing PRIVATE easm)

add_test(NAME Easm_Core_Function_Test COMMAND easm-testing)
