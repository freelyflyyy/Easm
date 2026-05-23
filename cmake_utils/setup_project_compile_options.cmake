include(CheckCXXCompilerFlag)

#检查编译器是否支持指定参数
function(add_supported_cxx_flags target scope)
    if (NOT scope MATCHES "^(PRIVATE|PUBLIC|INTERFACE)$")
        message(FATAL_ERROR "add_supported_cxx_flags: scope must be PRIVATE, PUBLIC, or INTERFACE")
    endif()

    foreach(flag ${ARGN})
        string(REGEX REPLACE "[^A-Za-z0-9]" "_" flag_var "${flag}")
        check_cxx_compiler_flag("${flag}" "CXX_FLAG_${flag_var}")

        if (CXX_FLAG_${flag_var})
            target_compile_options(${target} ${scope} "${flag}")
        endif()
    endforeach()
endfunction()

#添加为项目添加编译参数
function(setup_project_compile_options target)
    if (MSVC OR (DEFINED CMAKE_CXX_COMPILER_FRONTEND_VARIANT AND CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))
        target_compile_options(${target} PRIVATE
                /W4
                /MP
                /permissive-
                /EHsc
                /Zc:__cplusplus
                /Zc:inline
                /Zc:strictStrings
                /GS
                $<$<NOT:$<CONFIG:Debug>>:/O2>
                $<$<NOT:$<CONFIG:Debug>>:/Oi>
        )
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target} PRIVATE
                -Wall
                -Wextra
                -Wconversion
                -fno-math-errno
                $<$<NOT:$<CONFIG:Debug>>:-O2>
        )

        if (NOT APPLE)
            add_supported_cxx_flags(${target} PRIVATE -fno-semantic-interposition)
        endif ()

        add_supported_cxx_flags(${target} PRIVATE
                -Wdouble-promotion
                -Wduplicated-cond
                -Wduplicated-branches
                -Wlogical-op
                -Wrestrict
        )
    endif ()
endfunction()