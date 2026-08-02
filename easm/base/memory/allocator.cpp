#include <cstdlib>
#include "allocator.h"

namespace Easm {

    namespace {

        struct AllocationHeader final {
            void* original_memory;
        };

        /**
         * 获取 usize 能表达的最大值。
         */
        [[nodiscard]]
        constexpr usize maximum_usize() noexcept {
            return static_cast<usize>(-1);
        }

        [[nodiscard]]
        constexpr usize normalize_alignment(usize alignment) noexcept {
            constexpr usize HeaderAlignment = alignof(AllocationHeader);
            return alignment < HeaderAlignment ? HeaderAlignment : alignment;
        }


        /**
         * 默认内存申请函数。
         *
         * 在malloc上增加对齐
         *
         */
        [[nodiscard]]
        void* default_allocate(
            void* context,
            usize size,
            usize alignment
        ) noexcept {
            //默认分配器不使用context
            static_cast<void>(context);

            const usize actual_alignment = normalize_alignment(alignment);
            constexpr usize MetadataSize = alignof(AllocationHeader);
            const usize alignment_padding = actual_alignment - 1;
            const usize metadata_with_padding = MetadataSize + alignment_padding;

            if (EASM_UNLIKELY(size > maximum_usize() - metadata_with_padding)) {
                return nullptr;
            }
            const usize total_size = size + metadata_with_padding;
            void* original_memory = std::malloc(total_size);

            if (EASM_UNLIKELY(original_memory == nullptr)) {
                return nullptr;
            }

            const uptr original_address = reinterpret_cast<uptr>(original_memory);
            const uptr first_available = original_address + static_cast<uptr>(MetadataSize);
            const uptr aligned_address = (first_available + alignment_padding) & ~alignment_padding;

            auto* header = reinterpret_cast<AllocationHeader*>(aligned_address - MetadataSize);
            header->original_memory = original_memory;
            return reinterpret_cast<void*>(aligned_address);
        }

        void default_deallocate(
            void* context,
            void* memory,
            usize size,
            usize alignment
        ) noexcept {
            static_cast<void>(context);
            static_cast<void>(size);
            static_cast<void>(alignment);

            if (memory == nullptr) {
                return;
            }
            const uptr aligned_address = reinterpret_cast<uptr>(memory);
            constexpr uptr MetadataSize = sizeof(AllocationHeader);

            auto* header = reinterpret_cast<AllocationHeader*>(aligned_address - MetadataSize);
            std::free(header->original_memory);
        }
    }

    Allocator default_allocator() noexcept {
        return Allocator{
            nullptr,
            default_allocate,
            default_deallocate
        };
    }
}
