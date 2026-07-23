#ifndef EASM_BASE_ERROR_H
#define EASM_BASE_ERROR_H

#include <easm/base/type.h>

namespace Easm {

    enum class Error : u8 {
        Success = 0,

        // 通用错误
        InvalidArgument = 1,
        InvalidState = 2,

        //内存与缓冲区
        OutOfMemory = 3,
        BufferTooLarge = 4,

        //标签
        InvalidLabel = 5,
        LabelAlreadyBound = 6,
        LabelNotBound = 7,

        //指令编码
        InvalidInstruction = 8,
        InvalidOperand = 9,
        InvalidAddress = 10,
        InvalidImmediate = 11,
        UnsupportedInstruction = 12,
        UnsupportedMode = 13,

        //相对地址与重定位
        BranchOutOfRange = 14,
        RelocationOutOfRange = 15,

        Count = 16
    };

    [[nodiscard]]
    constexpr bool succeeded(Error error) noexcept {
        return error == Error::Success;
    }

    [[nodiscard]]
    constexpr bool failed(Error error) noexcept {
        return error != Error::Success;
    }
} // namespace Easm

#endif // EASM_BASE_ERROR_H
