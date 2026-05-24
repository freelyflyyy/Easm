#ifndef EASM_BASE_BASE_H
#define EASM_BASE_BASE_H

#include <easm/base/type.h>
#include <easm/base/version.h>

#define EASM_NAMESPACE_BEGIN                                                 \
    namespace Easm {

#define EASM_NAMESPACE_END                                                   \
    }

#define EASM_X64_NAMESPACE_BEGIN                                             \
    namespace Easm::x64 {

#define EASM_X64_NAMESPACE_END                                               \
    }

#define EASM_DISABLE_COPY(TypeName)                                          \
    TypeName(const TypeName&) = delete;                                      \
    TypeName& operator=(const TypeName&) = delete

#define EASM_DISABLE_MOVE(TypeName)                                          \
    TypeName(TypeName&&) = delete;                                           \
    TypeName& operator=(TypeName&&) = delete

#define EASM_DISABLE_COPY_AND_MOVE(TypeName)                                 \
    EASM_DISABLE_COPY(TypeName);                                             \
    EASM_DISABLE_MOVE(TypeName)

#endif // EASM_BASE_BASE_H
