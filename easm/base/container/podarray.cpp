#include "podarray.h"

#include <cstring>


namespace Easm::Details {

namespace {

constexpr usize InitialAllocationBytes = 64;

[[nodiscard]]
usize initial_capacity(
    usize element_size
) noexcept {
    const usize capacity =
        InitialAllocationBytes / element_size;

    return capacity == 0 ? 1 : capacity;
}

} // namespace

PodArrayStorage::PodArrayStorage(
    usize element_size,
    usize element_alignment
) noexcept
    : PodArrayStorage(
        element_size,
        element_alignment,
        default_allocator()
    ) {
}

PodArrayStorage::PodArrayStorage(
    usize element_size,
    usize element_alignment,
    Allocator allocator
) noexcept
    : m_allocator(allocator),
      m_element_size(element_size),
      m_element_alignment(element_alignment) {
}

PodArrayStorage::~PodArrayStorage() noexcept {
    release();
}

PodArrayStorage::PodArrayStorage(
    PodArrayStorage&& other
) noexcept
    : m_allocator(other.m_allocator),
      m_data(other.m_data),
      m_size(other.m_size),
      m_capacity(other.m_capacity),
      m_element_size(other.m_element_size),
      m_element_alignment(other.m_element_alignment) {
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

PodArrayStorage& PodArrayStorage::operator=(
    PodArrayStorage&& other
) noexcept {
    if (this == &other) {
        return *this;
    }

    release();

    m_allocator = other.m_allocator;
    m_data = other.m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_element_size = other.m_element_size;
    m_element_alignment = other.m_element_alignment;

    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;

    return *this;
}

Error PodArrayStorage::reserve(
    usize minimum_capacity
) noexcept {
    if (minimum_capacity <= m_capacity) {
        return Error::Success;
    }

    if (
        !m_allocator.valid() || m_element_size == 0
    ) {
        return Error::InvalidState;
    }

    const usize maximum_capacity = MaximumUsize / m_element_size;

    if (minimum_capacity > maximum_capacity) {
        return Error::BufferTooLarge;
    }

    usize new_capacity = m_capacity;

    if (new_capacity == 0) {
        new_capacity = initial_capacity(m_element_size);

        if (new_capacity > maximum_capacity) {
            new_capacity = maximum_capacity;
        }
    }

    while (new_capacity < minimum_capacity) {
        if (new_capacity > maximum_capacity / 2) {
            new_capacity = minimum_capacity;
            break;
        }

        new_capacity *= 2;
    }

    const usize new_allocation_size = new_capacity * m_element_size;

    byte* new_data = static_cast<byte*>(
        m_allocator.allocate(
            new_allocation_size,
            m_element_alignment
        )
    );

    if (new_data == nullptr) {
        return Error::OutOfMemory;
    }

    if (m_size != 0) {
        const usize used_size =
            m_size * m_element_size;

        std::memcpy(
            new_data,
            m_data,
            used_size
        );
    }

    if (m_data != nullptr) {
        const usize old_allocation_size = m_capacity * m_element_size;

        m_allocator.deallocate(
            m_data,
            old_allocation_size,
            m_element_alignment
        );
    }

    m_data = new_data;
    m_capacity = new_capacity;

    return Error::Success;
}

Error PodArrayStorage::append_data(
    const void* elements,
    usize count
) noexcept {
    if (count == 0) {
        return Error::Success;
    }

    if (elements == nullptr) {
        return Error::InvalidArgument;
    }

    if (m_element_size == 0) {
        return Error::InvalidState;
    }

    if (count > MaximumUsize - m_size) {
        return Error::BufferTooLarge;
    }

    if (count > MaximumUsize / m_element_size) {
        return Error::BufferTooLarge;
    }

    const usize old_size = m_size;
    const usize new_size = old_size + count;
    const usize copy_size = count * m_element_size;

    const byte* source = static_cast<const byte*>(elements);

    bool source_is_internal = false;
    usize source_offset = 0;

    if (m_data != nullptr) {
        const usize allocated_size = m_capacity * m_element_size;

        const usize used_size = m_size * m_element_size;

        const uptr data_address = reinterpret_cast<uptr>(m_data);

        const uptr source_address = reinterpret_cast<uptr>(source);

        if (source_address >= data_address) {
            const uptr address_difference = source_address - data_address;

            if (
                address_difference <= static_cast<uptr>(allocated_size)
            ) {
                if (
                    address_difference >=
                    static_cast<uptr>(used_size)
                ) {
                    return Error::InvalidArgument;
                }

                source_offset = static_cast<usize>(address_difference);

                if (source_offset % m_element_size != 0 ||
                    copy_size > used_size - source_offset) {
                    return Error::InvalidArgument;
                }

                source_is_internal = true;
            }
        }
    }

    const Error reserve_error = reserve(new_size);

    if (failed(reserve_error)) {
        return reserve_error;
    }

    if (source_is_internal) {
        source = m_data + source_offset;
    }

    byte* destination =
        m_data + old_size * m_element_size;

    std::memmove(
        destination,
        source,
        copy_size
    );

    m_size = new_size;

    return Error::Success;
}

Error PodArrayStorage::truncate(
    usize new_size
) noexcept {
    if (new_size > m_size) {
        return Error::InvalidArgument;
    }

    m_size = new_size;

    return Error::Success;
}

void PodArrayStorage::release() noexcept {
    if (m_data != nullptr) {
        const usize allocation_size =m_capacity * m_element_size;

        m_allocator.deallocate(
            m_data,
            allocation_size,
            m_element_alignment
        );
    }

    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
}

} // namespace Easm::Details