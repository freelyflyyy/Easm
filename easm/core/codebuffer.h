#ifndef EASM_CORE_CODEBUFFER_H
#define EASM_CORE_CODEBUFFER_H

#include <easm/base/container/podarray.h>
#include <easm/base/error.h>
#include <easm/base/memory/allocator.h>

namespace Easm {

    class EASM_API CodeBuffer final {
    public:
        CodeBuffer() noexcept = default;

        explicit CodeBuffer(
            Allocator allocator
        ) noexcept
            : m_storage(allocator) {
        }

        ~CodeBuffer() noexcept = default;

        EASM_DELETE_COPY(CodeBuffer);

        CodeBuffer(
            CodeBuffer&& other
        ) noexcept = default;

        CodeBuffer& operator=(
            CodeBuffer&& other
        ) noexcept = default;

        [[nodiscard]]
        byte* data() noexcept {
            return m_storage.data();
        }

        [[nodiscard]]
        const byte* data() const noexcept {
            return m_storage.data();
        }

        [[nodiscard]]
        usize size() const noexcept {
            return m_storage.size();
        }

        [[nodiscard]]
        usize capacity() const noexcept {
            return m_storage.capacity();
        }

        [[nodiscard]]
        bool empty() const noexcept {
            return m_storage.empty();
        }

        [[nodiscard]]
        Allocator allocator() const noexcept {
            return m_storage.allocator();
        }

        Error reserve(
            usize minimum_capacity
        ) noexcept;

        Error append_u8(
            u8 value
        ) noexcept;

        Error append_data(
            const byte* data,
            usize size
        ) noexcept;

        Error write_data(
            usize offset,
            const byte* data,
            usize size
        ) noexcept;

        Error truncate(
            usize new_size
        ) noexcept;

        void clear() noexcept {
            m_storage.clear();
        }

        void release() noexcept {
            m_storage.release();
        }

    private:
        PodArray<byte> m_storage;
    };

} // namespace Easm

#endif // EASM_CORE_CODEBUFFER_H