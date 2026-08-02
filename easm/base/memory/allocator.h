#ifndef EASM_BASE_MEMORY_ALLOCATOR_H
#define EASM_BASE_MEMORY_ALLOCATOR_H
#include <easm/base/type.h>

namespace Easm {

    /**
     * @brief Easm的底层内存分配接口
     *
     * Allocator本身不拥有任何context指向的对象，也不负责
     * 管理context的生命周期
     *
     * 如果 Allocator使用了外部context，那么该context的生命周期
     * 必须长于所有使用该 Allocator 分配内存的对象。
     *
     * Allocator 是一个轻量句柄，可以安全地按值复制。
     *
     */
    class Allocator final {
    public:
        /**
         * @brief 原始内存申请函数类型。
         *
         * @param context   用户提供的分配器上下文，可以为空。
         * @param size      需要申请的字节数，必须大于 0。
         * @param alignment 对齐要求，必须是非零的 2 的幂。
         *
         * @return 成功时返回满足对齐要求的内存地址；
         *         失败时返回 nullptr。
         *
         * 返回的内存不要求初始化。
         */
        using AllocateFn = void* (*)(
            void* context,
            usize size,
            usize alignment
        ) noexcept;

        /**
         * @brief 原始内存释放函数类型。
         *
         * @param context   用户提供的分配器上下文，可以为空。
         * @param memory    需要释放的内存地址，必须由对应的
         *                  AllocateFn 返回。
         * @param size      申请该内存时使用的字节数。
         * @param alignment 申请该内存时使用的对齐值。
         *
         * size 和 alignment 必须与申请时一致。虽然某些系统分配器
         * 不需要它们，但固定内存池、Arena 和统计分配器可能需要。
         */
        using DeallocateFn = void (*)(
            void* context,
            void* memory,
            usize size,
            usize alignment
        ) noexcept;

        /**
         * @brief 构造一个无效分配器。
         *
         * 无效分配器不能申请内存。
         */
        constexpr Allocator() noexcept = default;

        /**
        * @brief 使用指定回调构造分配器。
        *
        * @param context       用户上下文。
        * @param allocate_fn   内存申请函数。
        * @param deallocate_fn 内存释放函数。
        */
        constexpr Allocator(
            void* context,
            AllocateFn allocate_fn,
            DeallocateFn deallocate_fn
        ) noexcept :
        m_context(context),
        m_allocate_fn(allocate_fn),
        m_deallocate_fn(deallocate_fn) {
        }

        /**
         * @brief 判断分配器是否完整有效。
         *
         * 申请函数和释放函数必须同时存在。
         */
        [[nodiscard]]
        constexpr bool valid() const noexcept {
            return m_allocate_fn != nullptr &&
                m_deallocate_fn != nullptr;
        }

        /**
         * @brief 提供更自然的布尔类型判断
         */
        [[nodiscard]]
        constexpr explicit operator bool() const noexcept {
            return valid();
        }
        /**
         * @brief 申请一块原始内存。
         *
         * @param size      申请的字节数。
         * @param alignment 对齐要求。
         *
         * 以下情况直接返回 nullptr：
         *
         * 1. 分配器无效；
         * 2. size 等于 0；
         * 3. alignment 不是非零的 2 的幂；
         * 4. 底层分配函数分配失败。
         *
         * @return 成功时返回内存地址，失败时返回 nullptr。
         */
        [[nodiscard]]
        void* allocate(
            usize size,
            usize alignment
        ) const noexcept {
            if (EASM_UNLIKELY(!valid() || size == 0 || !is_valid_alignment(alignment))) {
                return nullptr;
            }
            return m_allocate_fn(m_context, size, alignment);
        }

        /**
        * @brief 释放通过当前分配器申请的内存。
        *
        * memory 为 nullptr 时不执行任何操作。
        *
        * 正常情况下，memory、size 和 alignment 必须与 allocate()
        * 时完全一致。
        */
        void deallocate(
            void* memory,
            usize size,
            usize alignment
        ) const noexcept {
            if (EASM_UNLIKELY( memory == nullptr || !valid() || size == 0 || !is_valid_alignment(alignment))) {
                return;
            }
            m_deallocate_fn(m_context, memory, size, alignment);
        }

        /**
         * @brief 获取分配器的用户上下文。
         *
         * Allocator 不拥有该上下文。
         */
        [[nodiscard]]
        constexpr void* context() const noexcept {
            return m_context;
        }

    private:
        [[nodiscard]]
        static constexpr bool is_valid_alignment(
            usize alignment
        ) noexcept {
            return alignment != 0 &&
                (alignment & (alignment - 1)) == 0;
        }

        void* m_context = nullptr;
        AllocateFn m_allocate_fn = nullptr;
        DeallocateFn m_deallocate_fn = nullptr;
    };

    /**
     * @brief 创建 Easm 提供的默认分配器。
     *
     * 该函数返回一个轻量 Allocator 句柄，不返回全局可修改对象。
     *
     * 默认分配器的具体实现放在 allocator.cpp 中，allocator.h
     * 不依赖 malloc、Windows API 或任何平台头文件。
     */
    [[nodiscard]]
    EASM_API Allocator default_allocator() noexcept;
}
#endif //EASM_BASE_MEMORY_ALLOCATOR_H
