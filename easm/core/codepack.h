#ifndef EASM_CORE_CODEPACK_H
#define EASM_CORE_CODEPACK_H

#include <vector>
#include <easm/base/base.h>

EASM_NAMESPACE_BEGIN

class CodePack {
public:
    CodePack() = default;
    ~CodePack() = default;

    EASM_DISABLE_COPY(CodePack);

    [[nodiscard]]
    const byte* data() const noexcept;
    [[nodiscard]]
    byte* data() noexcept;
    [[nodiscard]]
    size_t size() const noexcept;
    [[nodiscard]]
    bool empty() const noexcept;
    [[nodiscard]]
    size_t capacity() const noexcept;

    void clear() noexcept;
    void reserve(size_t capacity) noexcept;

    void append_u8(byte value) noexcept;
    void append_bytes(const void* data, size_t size) noexcept;

private:
    std::vector<byte> m_code;
};

EASM_NAMESPACE_END

#endif // EASM_CORE_CODEPACK_H
