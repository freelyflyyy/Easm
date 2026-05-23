#ifndef EASM_API_CONFIG_H
#define EASM_API_CONFIG_H

#define EASM_MAKE_VERSION(major, minor, patch)                               \
    (((major) << 16) | ((minor) << 8) | (patch))

#define EASM_VERSION EASM_MAKE_VERSION(0, 1, 0)

#if !defined(EASM_ABI_NAMESPACE)
    #define EASM_ABI_NAMESPACE v0_1
#endif

#include <cstddef>
#include <cstdint>
#include <type_traits>

// Documents build-time configuration macros without changing normal compilation.
#if defined(_DOXYGEN)
    #define EASM_SHARED
    #undef EASM_SHARED

    #define EASM_NO_ABI_NAMESPACE
    #undef EASM_NO_ABI_NAMESPACE
#endif

// Detects whether this translation unit is compiled in debug or release mode.
#if defined(NDEBUG)
    #define EASM_BUILD_RELEASE
#else
    #define EASM_BUILD_DEBUG
#endif

#if defined(_DOXYGEN)

// Documents architecture detection macros without binding them to the host that runs Doxygen.
#define EASM_ARCH_X86 __detected_at_compile_time__
#define EASM_ARCH_ARM __detected_at_compile_time__
#define EASM_ARCH_BITS __detected_at_compile_time__

#else

// Detects x86/x64 targets and encodes the result as 0, 32, or 64.
#if defined(_M_X64) || defined(__x86_64__)
    #define EASM_ARCH_X86 64
#elif defined(_M_IX86) || defined(__i386__)
    #define EASM_ARCH_X86 32
#else
    #define EASM_ARCH_X86 0
#endif

// Detects ARM/AArch64 targets and encodes the result as 0, 32, or 64.
#if defined(_M_ARM64) || defined(__aarch64__)
    #define EASM_ARCH_ARM 64
#elif defined(_M_ARM) || defined(__arm__)
    #define EASM_ARCH_ARM 32
#else
    #define EASM_ARCH_ARM 0
#endif

// Resolves the native pointer width from the detected architecture.
#define EASM_ARCH_BITS (EASM_ARCH_ARM | EASM_ARCH_X86)

// Falls back to generic platform macros when the CPU family is unknown.
#if EASM_ARCH_BITS == 0
    #undef EASM_ARCH_BITS
    #if defined(_WIN64) || defined(__LP64__) || defined(_LP64)
        #define EASM_ARCH_BITS 64
    #else
        #define EASM_ARCH_BITS 32
    #endif
#endif

#endif

// Decorates public symbols when Easm is built or consumed as a shared library.
#if defined(_WIN32) && defined(EASM_SHARED)
    #if defined(EASM_EXPORTS)
        #define EASM_API __declspec(dllexport)
    #else
        #define EASM_API __declspec(dllimport)
    #endif
#else
    #define EASM_API
#endif

#if !defined(EASM_NO_ABI_NAMESPACE) && !defined(_DOXYGEN)
    #define EASM_BEGIN_NAMESPACE                                             \
        namespace Easm {                                                     \
        inline namespace EASM_ABI_NAMESPACE {

    #define EASM_END_NAMESPACE                                               \
        }                                                                    \
        }
#else
    #define EASM_BEGIN_NAMESPACE                                             \
        namespace Easm {

    #define EASM_END_NAMESPACE                                               \
        }
#endif

#define EASM_BEGIN_SUB_NAMESPACE(Namespace)                                  \
    EASM_BEGIN_NAMESPACE                                                     \
    namespace Namespace {

#define EASM_END_SUB_NAMESPACE                                               \
    }                                                                        \
    EASM_END_NAMESPACE


// Marks resource-owning types as non-copyable.
#define EASM_NONCOPYABLE(Type)                                               \
    Type(const Type& other) = delete;                                        \
    Type& operator=(const Type& other) = delete;

// Marks utility-only types as non-default-constructible and non-copyable.
#define EASM_NONCONSTRUCTION(Type)                                           \
    Type() = delete;                                                         \
    Type(const Type& other) = delete;                                        \
    Type& operator=(const Type& other) = delete;

// Defines bitwise operators for enum classes that represent flag sets.
#define EASM_DEFINE_ENUM_FLAGS(T)                                            \
    inline constexpr T operator~(T a) noexcept {                             \
        using U = std::underlying_type_t<T>;                                 \
        return static_cast<T>(~static_cast<U>(a));                           \
    }                                                                        \
                                                                             \
    inline constexpr T operator|(T a, T b) noexcept {                        \
        using U = std::underlying_type_t<T>;                                 \
        return static_cast<T>(static_cast<U>(a) | static_cast<U>(b));        \
    }                                                                        \
                                                                             \
    inline constexpr T operator&(T a, T b) noexcept {                        \
        using U = std::underlying_type_t<T>;                                 \
        return static_cast<T>(static_cast<U>(a) & static_cast<U>(b));        \
    }                                                                        \
                                                                             \
    inline constexpr T& operator|=(T& a, T b) noexcept {                     \
        return a = a | b;                                                    \
    }                                                                        \
                                                                             \
    inline constexpr T& operator&=(T& a, T b) noexcept {                     \
        return a = a & b;                                                    \
    }

#endif // EASM_API_CONFIG_H
