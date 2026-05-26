#include <easm/core/codepack.h>

EASM_NAMESPACE_BEGIN

const byte *CodePack::data() const noexcept {
    return m_code.data();
}

byte *CodePack::data() noexcept {
    return m_code.data();
}

size_t CodePack::size() const noexcept {
    return m_code.size();
}

bool CodePack::empty() const noexcept {
    return m_code.empty();
}

size_t CodePack::capacity() const noexcept {
    return m_code.capacity();
}

void CodePack::clear() noexcept {
    m_code.clear();
}

void CodePack::reserve(size_t capacity) noexcept {
    m_code.reserve(capacity);
}

void CodePack::append_u8(byte value) noexcept {
    m_code.push_back(value);
}

void CodePack::append_bytes(const void *data, size_t size) noexcept {
    if (size == 0) {
        return;
    }
    const byte *bytes = static_cast<const byte *>(data);
    m_code.insert(m_code.end(), bytes, bytes + size);
}

EASM_NAMESPACE_END
