#ifndef EASM_CORE_LABEL_H
#define EASM_CORE_LABEL_H
#include <easm/base/type.h>

namespace Easm {

    using LabelId = u32;

    inline constexpr LabelId InvalidLabelId = MaximumU32;

    class CodeHolder;

    class Label final {
        public:
        constexpr Label() noexcept = default;

        [[nodiscard]]
        constexpr LabelId id() const noexcept {
            return m_id;
        }

        [[nodiscard]]
        constexpr bool valid() const noexcept {
            return m_id != InvalidLabelId;
        }

        [[nodiscard]]
        constexpr explicit operator bool() const noexcept {
            return valid();
        }

        [[nodiscard]]
        constexpr bool operator==(Label other) const noexcept {
            return m_id == other.m_id;
        }

        [[nodiscard]]
        constexpr bool operator!=(Label other) const noexcept {
            return !(*this == other);
        }


    private:
        explicit constexpr Label(LabelId id) noexcept
            : m_id(id) {
        }

        LabelId m_id = InvalidLabelId;

        friend class CodeHolder;
    };
}

#endif //EASM_CORE_LABEL_H
