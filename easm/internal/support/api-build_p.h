#ifndef EASM_API_BUILD_P_H
#define EASM_API_BUILD_P_H

// Suppresses MSVC CRT warnings while compiling Easm implementation files.
#ifdef _MSC_VER
    #ifndef _CRT_SECURE_NO_WARNINGS
        #define _CRT_SECURE_NO_WARNINGS
    #endif

    #ifndef _CRT_SECURE_NO_DEPRECATE
        #define _CRT_SECURE_NO_DEPRECATE
    #endif
#endif

// Reduces Windows header surface area and prevents min/max macro pollution.
#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    #ifndef NOMINMAX
        #define NOMINMAX
    #endif

    #include <windows.h>
#endif

// Includes the shared API configuration after private build settings are ready.
#include <easm/internal/support/api-config.h>

#endif // EASM_API_BUILD_P_H
