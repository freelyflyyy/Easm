#ifndef EASM_BASE_CONTAINER_PODARRAY_H
#define EASM_BASE_CONTAINER_PODARRAY_H

#include <type_traits>
#include <easm/base/error.h>
#include <easm/base/memory/allocator.h>

namespace Easm {

    namespace Details {
        class EASM_API PodArrayStorage final {
        public:
            PodArrayStorage(usize element_size, usize element_alignment) noexcept;

            PodArrayStorage(usize element_size, usize element_alignment, Allocator allocator) noexcept;

            ~PodArrayStorage() noexcept;

            EASM_DELETE_COPY(PodArrayStorage);

            PodArrayStorage(PodArrayStorage&& other) noexcept;
            PodArrayStorage& operator=(PodArrayStorage&& other) noexcept;

            [[nodiscard]]
            void* data() noexcept {
                return m_data;
            }

            [[nodiscard]]
            const void* data() const noexcept {
                return m_data;
            }

            [[nodiscard]]
            usize size() const noexcept {
                return m_size;
            }

            [[nodiscard]]
            usize capacity() const noexcept {
                return m_capacity;
            }

            [[nodiscard]]
            bool empty() const noexcept {
                return m_size == 0;
            }

            [[nodiscard]]
            Allocator allocator() const noexcept {
                return m_allocator;
            }

            [[nodiscard]]
            Error reserve(usize minimum_capacity) noexcept;

            [[nodiscard]]
            Error append_data(const void* elements, usize count) noexcept;

            [[nodiscard]]
            Error truncate(usize new_size) noexcept;

            void clear() noexcept {
                m_size = 0;
            }

            void release() noexcept;

        private:
            Allocator m_allocator;
            byte* m_data = nullptr;
            usize m_size = 0;
            usize m_capacity = 0;

            usize m_element_size = 0;
            usize m_element_alignment = 0;
        };
    }

    template <typename T>
    class PodArray final {
        static_assert(
            std::is_trivially_copyable_v<T>,
            "PodArray requires a trivially copyable type"
        );

        static_assert(
            std::is_trivially_destructible_v<T>,
            "PodArray requires a trivially destructible type"
        );

        static_assert(
            !std::is_const_v<T>,
            "PodArray does not support const element types"
        );

        static_assert(
            !std::is_volatile_v<T>,
            "PodArray does not support volatile element types"
        );
    public:
        PodArray() noexcept
            : m_storage(sizeof(T), alignof(T)){
        }

        explicit PodArray(Allocator allocator) noexcept
            : m_storage(sizeof(T), alignof(T), allocator) {
        }

        ~PodArray() noexcept = default;

        EASM_DELETE_COPY(PodArray);

        PodArray(PodArray&& other) noexcept = default;
        PodArray& operator=(PodArray&& other) noexcept = default;

        [[nodiscard]]
        T* data() noexcept {
            return static_cast<T*>(m_storage.data());
        }

        [[nodiscard]]
        const T* data() const noexcept {
            return static_cast<const T*>(m_storage.data());
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

        T& operator[](usize index) noexcept {
            return data()[index];
        }

        const T& operator[](usize index) const noexcept {
            return data()[index];
        }

        [[nodiscard]]
        Error reserve(usize minimum_capacity) noexcept {
            return m_storage.reserve(minimum_capacity);
        }

        [[nodiscard]]
        Error append(const T& element) noexcept {
            return m_storage.append_data(&element, 1);
        }

        [[nodiscard]]
        Error append_data(const T* elements, usize count) noexcept {
            return m_storage.append_data(elements, count);
        }

        [[nodiscard]]
        Error truncate(usize new_size) noexcept {
            return m_storage.truncate(new_size);
        }

        void clear() noexcept {
            m_storage.clear();
        }

        void release() noexcept {
            m_storage.release();
        }

    private:
        Details::PodArrayStorage m_storage;
    };
}

#endif //EASM_BASE_CONTAINER_PODARRAY_H
