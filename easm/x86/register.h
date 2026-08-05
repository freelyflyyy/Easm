#ifndef EASM_X86_REGISTER_H
#define EASM_X86_REGISTER_H

#include <easm/base/type.h>

namespace Easm::x86 {
    using RegisterId = u8;

    enum class GpType : u8 {
        None = 0,
        ByteLow,
        ByteHigh,
        Word,
        Dword,
        Qword
    };

    class Gp final {
    public:
        constexpr Gp() noexcept = default;

        constexpr Gp(GpType type, RegisterId id) noexcept
                : m_type(type), m_id(id) {
        }

        [[nodiscard]]
        constexpr bool valid() const noexcept {
            switch (m_type) {
                case GpType::None:
                    return false;
                case GpType::ByteHigh:
                    return m_id >= FirstHighByteId && m_id <= LastHighByteId;

                case GpType::ByteLow:
                case GpType::Word:
                case GpType::Dword:
                case GpType::Qword:
                    return m_id <= MaximumGpId;
            }
            return false;
        }

        [[nodiscard]]
        constexpr explicit operator bool() const noexcept {
            return valid();
        }

        [[nodiscard]]
        constexpr GpType type() const noexcept {
            return m_type;
        }

        [[nodiscard]]
        constexpr RegisterId id() const noexcept {
            return m_id;
        }

        [[nodiscard]]
        constexpr u8 size() const noexcept {
            switch (m_type) {
                case GpType::ByteLow:
                case GpType::ByteHigh:  return 1;
                case GpType::Word:      return 2;
                case GpType::Dword:     return 4;
                case GpType::Qword:     return 8;
                case GpType::None:      return 0;
            }
            return 0;
        }

        [[nodiscard]]
        constexpr bool is_high_byte() const noexcept {
            return valid() && m_type == GpType::ByteHigh;
        }

        [[nodiscard]]
        constexpr bool is_extended() const noexcept {
            return valid() && m_id >= 8;
        }

        [[nodiscard]]
        constexpr bool operator==(Gp other) const noexcept {
            return m_type == other.m_type && m_id == other.m_id;
        }

        [[nodiscard]]
        constexpr bool operator!=(Gp other) const noexcept {
            return !(*this == other);
        }

    private:
        static constexpr RegisterId MaximumGpId = 15;
        static constexpr RegisterId FirstHighByteId = 4;
        static constexpr RegisterId LastHighByteId = 7;

        GpType m_type = GpType::None;
        RegisterId m_id = 0;
    };

    // 低八位寄存器
    inline constexpr Gp al{GpType::ByteLow, 0};
    inline constexpr Gp cl{GpType::ByteLow, 1};
    inline constexpr Gp dl{GpType::ByteLow, 2};
    inline constexpr Gp bl{GpType::ByteLow, 3};
    inline constexpr Gp spl{GpType::ByteLow, 4};
    inline constexpr Gp bpl{GpType::ByteLow, 5};
    inline constexpr Gp sil{GpType::ByteLow, 6};
    inline constexpr Gp dil{GpType::ByteLow, 7};
    inline constexpr Gp r8b{GpType::ByteLow, 8};
    inline constexpr Gp r9b{GpType::ByteLow, 9};
    inline constexpr Gp r10b{GpType::ByteLow, 10};
    inline constexpr Gp r11b{GpType::ByteLow, 11};
    inline constexpr Gp r12b{GpType::ByteLow, 12};
    inline constexpr Gp r13b{GpType::ByteLow, 13};
    inline constexpr Gp r14b{GpType::ByteLow, 14};
    inline constexpr Gp r15b{GpType::ByteLow, 15};

    // 无法与REX前缀共存的高八位寄存器
    inline constexpr Gp ah{GpType::ByteHigh, 4};
    inline constexpr Gp ch{GpType::ByteHigh, 5};
    inline constexpr Gp dh{GpType::ByteHigh, 6};
    inline constexpr Gp bh{GpType::ByteHigh, 7};

    // 16位寄存器
    inline constexpr Gp ax{GpType::Word, 0};
    inline constexpr Gp cx{GpType::Word, 1};
    inline constexpr Gp dx{GpType::Word, 2};
    inline constexpr Gp bx{GpType::Word, 3};
    inline constexpr Gp sp{GpType::Word, 4};
    inline constexpr Gp bp{GpType::Word, 5};
    inline constexpr Gp si{GpType::Word, 6};
    inline constexpr Gp di{GpType::Word, 7};
    inline constexpr Gp r8w{GpType::Word, 8};
    inline constexpr Gp r9w{GpType::Word, 9};
    inline constexpr Gp r10w{GpType::Word, 10};
    inline constexpr Gp r11w{GpType::Word, 11};
    inline constexpr Gp r12w{GpType::Word, 12};
    inline constexpr Gp r13w{GpType::Word, 13};
    inline constexpr Gp r14w{GpType::Word, 14};
    inline constexpr Gp r15w{GpType::Word, 15};

    // 32位寄存器
    inline constexpr Gp eax{GpType::Dword, 0};
    inline constexpr Gp ecx{GpType::Dword, 1};
    inline constexpr Gp edx{GpType::Dword, 2};
    inline constexpr Gp ebx{GpType::Dword, 3};
    inline constexpr Gp esp{GpType::Dword, 4};
    inline constexpr Gp ebp{GpType::Dword, 5};
    inline constexpr Gp esi{GpType::Dword, 6};
    inline constexpr Gp edi{GpType::Dword, 7};
    inline constexpr Gp r8d{GpType::Dword, 8};
    inline constexpr Gp r9d{GpType::Dword, 9};
    inline constexpr Gp r10d{GpType::Dword, 10};
    inline constexpr Gp r11d{GpType::Dword, 11};
    inline constexpr Gp r12d{GpType::Dword, 12};
    inline constexpr Gp r13d{GpType::Dword, 13};
    inline constexpr Gp r14d{GpType::Dword, 14};
    inline constexpr Gp r15d{GpType::Dword, 15};

    // 64位寄存器
    inline constexpr Gp rax{GpType::Qword, 0};
    inline constexpr Gp rcx{GpType::Qword, 1};
    inline constexpr Gp rdx{GpType::Qword, 2};
    inline constexpr Gp rbx{GpType::Qword, 3};
    inline constexpr Gp rsp{GpType::Qword, 4};
    inline constexpr Gp rbp{GpType::Qword, 5};
    inline constexpr Gp rsi{GpType::Qword, 6};
    inline constexpr Gp rdi{GpType::Qword, 7};
    inline constexpr Gp r8{GpType::Qword, 8};
    inline constexpr Gp r9{GpType::Qword, 9};
    inline constexpr Gp r10{GpType::Qword, 10};
    inline constexpr Gp r11{GpType::Qword, 11};
    inline constexpr Gp r12{GpType::Qword, 12};
    inline constexpr Gp r13{GpType::Qword, 13};
    inline constexpr Gp r14{GpType::Qword, 14};
    inline constexpr Gp r15{GpType::Qword, 15};

}

#endif //EASM_X86_REGISTER_H
