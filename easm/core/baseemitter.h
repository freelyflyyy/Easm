#ifndef EASM_CORE_BASEEMITTER_H
#define EASM_CORE_BASEEMITTER_H

#include <easm/base/error.h>
#include <easm/base/type.h>
#include <easm/core/codeholder.h>

namespace Easm {

    class EASM_API BaseEmitter {
    public:
        EASM_DELETE_COPY(BaseEmitter);
        EASM_DELETE_MOVE(BaseEmitter);

        [[nodiscard]]
        bool valid() const noexcept;

        [[nodiscard]]
        Error error() const noexcept {
            return m_error;
        }

        [[nodiscard]]
        bool has_error() const noexcept {
            return failed(m_error);
        }

        void reset_error() noexcept {
            m_error = Error::Success;
        }

        [[nodiscard]]
        usize offset() const noexcept;

        [[nodiscard]]
        Environment environment() const noexcept;

        [[nodiscard]]
        Label new_label() noexcept;

    protected:
        explicit BaseEmitter(CodeHolder& code_holder) noexcept;

        ~BaseEmitter() noexcept = default;

        [[nodiscard]]
        CodeHolder& code_holder() noexcept {
            return m_code_holder;
        }

        [[nodiscard]]
        const CodeHolder& code_holder() const noexcept {
            return m_code_holder;
        }

        [[nodiscard]]
        CodeBuffer& code_buffer() noexcept {
            return m_code_holder.code();
        }

        [[nodiscard]]
        const CodeBuffer& code_buffer() const noexcept {
            return m_code_holder.code();
        }

        Error reserve(usize minimum_capacity) noexcept;

        Error append_u8(u8 value) noexcept;

        Error append_data(const byte* data, usize size) noexcept;

        Error write_data(usize offset, const byte* data, usize size) noexcept;

        Error truncate(usize new_size) noexcept;

        Error bind_label(Label label) noexcept;

        [[nodiscard]]
        bool label_bound(Label label) const noexcept;

        [[nodiscard]]
        Error label_offset(Label label, usize& out_offset) noexcept;

        Error set_error(Error error) noexcept;

    private:
        CodeHolder& m_code_holder;
        Error m_error = Error::Success;
    };
} // Easm

#endif //EASM_CORE_BASEEMITTER_H
