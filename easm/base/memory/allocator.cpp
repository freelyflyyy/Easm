#include "allocator.h"

#include <cstdlib>
#include <cstring>

namespace Easm {

    namespace {

        constexpr usize MetadataSize = sizeof(void*);

        /**
         * 默认内存申请函数。
         *
         * 在malloc上增加对齐
         */
        [[nodiscard]]
        void* default_allocate(
            void* /*context*/,
            usize size,
            usize alignment
        ) noexcept {
            const usize alignment_padding = alignment - 1;

            if (EASM_UNLIKELY(alignment_padding > MaximumUsize - MetadataSize)) {
                return nullptr;
            }

            const usize allocation_overhead = MetadataSize + alignment_padding;

            if (EASM_UNLIKELY(size > MaximumUsize - allocation_overhead)) {
                return nullptr;
            }

            void* original_memory = std::malloc(size + allocation_overhead);

            if (EASM_UNLIKELY(original_memory == nullptr)) {
                return nullptr;
            }

            const uptr original_address = reinterpret_cast<uptr>(original_memory);
            const uptr first_available_address = original_address + MetadataSize;
            const uptr alignment_mask = static_cast<uptr>(alignment_padding);
            const uptr aligned_address = (first_available_address + alignment_mask) & ~alignment_mask;

            byte* aligned_memory = reinterpret_cast<byte*>(aligned_address);

            std::memcpy(aligned_memory - MetadataSize, &original_memory, MetadataSize);

            return aligned_memory;
        }

        /**
         * 默认内存释放函数。
         */
        void default_deallocate(
            void* /*context*/,
            void* memory,
            usize /*size*/,
            usize /*alignment*/
        ) noexcept {
            if (EASM_UNLIKELY(memory == nullptr)) {
                return;
            }

            void* original_memory = nullptr;
            const byte* metadata = static_cast<const byte*>(memory) - MetadataSize;

            std::memcpy(&original_memory, metadata, MetadataSize);

            std::free(original_memory);
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
