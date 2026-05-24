#ifndef EASM_CORE_CODEBUFFER_H
#define EASM_CORE_CODEBUFFER_H

#include <easm/base/base.h>

#include <vector>

EASM_NAMESPACE_BEGIN

class CodeBuffer {
public:
    CodeBuffer() = default;
    ~CodeBuffer() = default;

    EASM_DISABLE_COPY(CodeBuffer);

    CodeBuffer(CodeBuffer&&) noexcept = default;
    CodeBuffer& operator=(CodeBuffer&&) noexcept = default;

    [[nodiscard]] const byte* data() const noexcept;
    [[nodiscard]] byte* data() noexcept;

    [[nodiscard]] usize size() const noexcept;
    [[nodiscard]] bool empty() const noexcept;

    void clear() noexcept;
    void reverse(usize size);

    void write_u8(u8 value);
    void write_u16(u16 value);
    void write_u32(u32 value);
    void write_u64(u64 value);

    void write_bytes(const void* data, usize size);

private:
    std::vector<byte> m_data;
};

EASM_NAMESPACE_END

#endif // EASM_CORE_CODEBUFFER_H
