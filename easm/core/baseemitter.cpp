#include "baseemitter.h"

namespace Easm {
    BaseEmitter::BaseEmitter(CodeHolder &code_holder) noexcept
        : m_code_holder(code_holder){
    }

    bool BaseEmitter::valid() const noexcept {
        return m_code_holder.valid();
    }

    usize BaseEmitter::offset() const noexcept {
        return code_buffer().size();
    }

    Environment BaseEmitter::environment() const noexcept {
        return m_code_holder.environment();
    }

    Label BaseEmitter::new_label() noexcept {
        Label label{};
        if (has_error()) {
            return label;
        }

        set_error(
            m_code_holder.create_label(label)
        );

        return label;
    }

    Error BaseEmitter::reserve(usize minimum_capacity) noexcept {
        if (has_error()) {
            return m_error;
        }

        return set_error(
            code_buffer().reserve(minimum_capacity)
        );
    }

    Error BaseEmitter::append_u8(u8 value) noexcept {
        if (has_error()) {
            return m_error;
        }

        return set_error(
            code_buffer().append_u8(value)
        );
    }

    Error BaseEmitter::append_data(const byte *data, usize size) noexcept {
        if (has_error()) {
            return m_error;
        }

        return set_error(
            code_buffer().append_data(data, size)
        );
    }

    Error BaseEmitter::write_data(usize offset, const byte *data, usize size) noexcept {
        if (has_error()) {
            return m_error;
        }

        return set_error(
            code_buffer().write_data(offset, data, size)
        );
    }

    Error BaseEmitter::bind_label(Label label) noexcept {
        if (has_error()) {
            return m_error;
        }

        return set_error(
            m_code_holder.bind_label(label)
        );
    }


    Error BaseEmitter::query_label_offset(Label label, usize &out_offset) const noexcept {
        if (has_error()) {
            out_offset = 0;
            return m_error;
        }

        return m_code_holder.label_offset(label, out_offset);
    }

    Error BaseEmitter::set_error(Error error) noexcept {
        if (has_error()) {
            return m_error;
        }

        m_error = error;
        return m_error;
    }
} // Easm