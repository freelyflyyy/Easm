#ifndef EASM_CORE_ENVIRONMENT_H
#define EASM_CORE_ENVIRONMENT_H

#include <easm/base/type.h>

namespace Easm {
    enum class Architecture : u8 {
        None = 0,
        X86,
        Arm
    };

    enum class Bitness : u8 {
        None = 0,
        Bits32,
        Bits64
    };

    enum class Endianness : u8 {
        None = 0,
        Little,
        Big
    };

    class Environment final {
    public:
        constexpr Environment() noexcept = default;

        constexpr Environment(
            Architecture architecture,
            Bitness bitness,
            Endianness endianness
        ) noexcept :
            m_architecture(architecture),
            m_bitness(bitness),
            m_endianness(endianness){
        }
        [[nodiscard]]
        constexpr Architecture architecture() const noexcept {
            return m_architecture;
        }

        [[nodiscard]]
        constexpr Bitness bitness() const noexcept {
            return m_bitness;
        }

        [[nodiscard]]
        constexpr Endianness endianness() const noexcept {
            return m_endianness;
        }

        [[nodiscard]]
        constexpr bool valid() const noexcept {
            return m_architecture != Architecture::None &&
                    m_bitness != Bitness::None &&
                    m_endianness != Endianness::None;
        }

        [[nodiscard]]
        constexpr explicit operator bool() const noexcept {
            return valid();
        }

        [[nodiscard]]
        constexpr bool is_32_bit() const noexcept {
            return m_bitness == Bitness::Bits32;
        }

        [[nodiscard]]
        constexpr bool is_64_bit() const noexcept {
            return m_bitness == Bitness::Bits64;
        }

        [[nodiscard]]
        constexpr usize pointer_size() const noexcept {
            if (is_32_bit()) {
                return 4;
            }
            if (is_64_bit()) {
                return 8;
            }
            return 0;
        }

        [[nodiscard]]
        constexpr bool operator==(const Environment& other) const noexcept {
            return m_architecture == other.m_architecture &&
                    m_bitness == other.m_bitness &&
                    m_endianness == other.m_endianness;
        }

        [[nodiscard]]
        constexpr bool operator!=(const Environment& other) const noexcept {
            return !(*this == other);
        }

    private:
        Architecture m_architecture = Architecture::None;
        Bitness m_bitness = Bitness::None;
        Endianness m_endianness = Endianness::None;
    };
} // Easm

#endif //EASM_CORE_ENVIRONMENT_H
