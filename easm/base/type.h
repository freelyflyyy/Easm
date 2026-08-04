#ifndef EASM_BASE_TYPE_H
#define EASM_BASE_TYPE_H

#include "config.h"

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

    static_assert(
        sizeof(usize) == sizeof(isize),
        "Easm requires usize and isize to have equal widths"
    );

    static_assert(
        sizeof(uptr) == sizeof(iptr),
        "Easm requires uptr and iptr to have equal widths"
    );

    inline constexpr u8 MaximumU8 = static_cast<u8>(-1);
    inline constexpr u16 MaximumU16 = static_cast<u16>(-1);
    inline constexpr u32 MaximumU32 = static_cast<u32>(-1);
    inline constexpr u64 MaximumU64 = static_cast<u64>(-1);

    inline constexpr i8 MaximumI8 = MaximumU8 >> 1U;
    inline constexpr i16 MaximumI16 = MaximumU16 >> 1U;
    inline constexpr i32 MaximumI32 = MaximumU32 >> 1U;
    inline constexpr i64 MaximumI64 = MaximumU64 >> 1U;

    inline constexpr usize MaximumUsize = static_cast<usize>(-1);
    inline constexpr isize MaximumIsize = MaximumUsize >> 1U;

    inline constexpr uptr MaximumUptr = static_cast<uptr>(-1);
    inline constexpr iptr MaximumIptr = MaximumUptr >> 1U;

    inline constexpr byte MaximumByte = MaximumU8;

} // namespace Easm

#endif // EASM_BASE_TYPE_H
