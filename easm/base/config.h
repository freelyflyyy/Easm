#ifndef EASM_BASE_CONFIG_H
#define EASM_BASE_CONFIG_H

// --------------------------------------------------------------------------
// C++ language requirement
// --------------------------------------------------------------------------

#if defined(_MSVC_LANG)
#   define EASM_CXX_VERSION _MSVC_LANG
#else
#   define EASM_CXX_VERSION __cplusplus
#endif

#if EASM_CXX_VERSION < 201703L
#  error "Easm requires C++17 or newer"
#endif

// --------------------------------------------------------------------------
// Symbol visibility
//
// Static library:
//   Do not define EASM_SHARED_LIBRARY.
//
// Building shared library:
//   Define EASM_SHARED_LIBRARY and EASM_BUILDING_LIBRARY.
//
// Consuming shared library:
//   Define EASM_SHARED_LIBRARY only.
// --------------------------------------------------------------------------

#if defined(EASM_SHARED_LIBRARY)

#   if defined(_WIN32)

#    if defined(EASM_BUILDING_LIBRARY)
#       define EASM_API __declspec(dllexport)
#    else
#       define EASM_API __declspec(dllimport)
#    endif

#   elif defined(__GNUC__) || defined(__clang__)
#     define EASM_API __attribute__((visibility("default")))
#   else
#     define EASM_API
#   endif

#else

#   define EASM_API

#endif

// --------------------------------------------------------------------------
// Compiler attributes
// --------------------------------------------------------------------------

#if defined(_MSC_VER)

#       define EASM_FORCE_INLINE __forceinline
#       define EASM_NOINLINE __declspec(noinline)
#       define EASM_LIKELY(expression) (!!(expression))
#       define EASM_UNLIKELY(expression) (!!(expression))

#   elif defined(__GNUC__) || defined(__clang__)
#       define EASM_FORCE_INLINE inline __attribute__((always_inline))
#       define EASM_NOINLINE __attribute__((noinline))
#       define EASM_LIKELY(expression) \
            (__builtin_expect(!!(expression), 1))
#       define EASM_UNLIKELY(expression) \
            (__builtin_expect(!!(expression), 0))

#   else

#       define EASM_FORCE_INLINE inline
#       define EASM_NOINLINE
#       define EASM_LIKELY(expression) (!!(expression))
#       define EASM_UNLIKELY(expression) (!!(expression))

#endif

// --------------------------------------------------------------------------
// Special member helpers
// --------------------------------------------------------------------------

#define EASM_DELETE_COPY(Type)        \
    Type(const Type&) = delete;       \
    Type& operator=(const Type&) = delete

#define EASM_DELETE_MOVE(Type)        \
    Type(Type&&) = delete;            \
    Type& operator=(Type&&) = delete

#endif //EASM_BASE_CONFIG_H