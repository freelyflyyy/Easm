#include <easm/core/codebuffer.h>

#include <cstring>

namespace Easm {

    Error CodeBuffer::reserve(
        usize minimum_capacity
    ) noexcept {
        return m_storage.reserve(
            minimum_capacity
        );
    }

    Error CodeBuffer::append_u8(
        u8 value
    ) noexcept {
        return m_storage.append(value);
    }

    Error CodeBuffer::append_data(
        const byte* data,
        usize size
    ) noexcept {
        return m_storage.append_data(
            data,
            size
        );
    }

    Error CodeBuffer::write_data(
        usize offset,
        const byte* data,
        usize size
    ) noexcept {
        const usize current_size =
            m_storage.size();

        if (offset > current_size) {
            return Error::InvalidArgument;
        }

        if (size == 0) {
            return Error::Success;
        }

        if (data == nullptr) {
            return Error::InvalidArgument;
        }

        if (size > current_size - offset) {
            return Error::InvalidArgument;
        }

        std::memmove(
            m_storage.data() + offset,
            data,
            size
        );

        return Error::Success;
    }

    Error CodeBuffer::truncate(
        usize new_size
    ) noexcept {
        return m_storage.truncate(
            new_size
        );
    }

} // namespace Easm