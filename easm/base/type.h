#ifndef EASM_BASE_TYPE_H
#define EASM_BASE_TYPE_H

#include <easm/base/config.h>

#include <cstddef>
#include <cstdint>
#include <climits>

namespace Easm {

    using i8 = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    // 只用于当前进程内的内存大小、数组索引和缓冲区偏移。
    using usize = std::size_t;
    using isize = std::ptrdiff_t;

    // 只用于保存宿主进程中的地址值。
    using uptr = std::uintptr_t;
    using iptr = std::intptr_t;

    using byte = u8;

    static_assert(CHAR_BIT == 8, "Easm requires 8-bit bytes");

    static_assert(sizeof(i8) == 1);
    static_assert(sizeof(i16) == 2);
    static_assert(sizeof(i32) == 4);
    static_assert(sizeof(i64) == 8);

    static_assert(sizeof(u8) == 1);
    static_assert(sizeof(u16) == 2);
    static_assert(sizeof(u32) == 4);
    static_assert(sizeof(u64) == 8);
} // namespace Easm

#endif // EASM_BASE_TYPE_H
