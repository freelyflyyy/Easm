#include <easm/core/baseemitter.h>

EASM_NAMESPACE_BEGIN

BaseEmitter::BaseEmitter(CodePack &code) noexcept
    : m_code(&code){
}

bool BaseEmitter::attached() const noexcept {
    return m_code!=nullptr;
}

CodePack * BaseEmitter::code() noexcept {
    return m_code;
}

const CodePack * BaseEmitter::code() const noexcept {
    return m_code;
}

void BaseEmitter::attach(CodePack &code) noexcept {
    m_code = &code;
}

void BaseEmitter::detach() {
    m_code = nullptr;
}

CodePack & BaseEmitter::code_ref() noexcept {
    return *m_code;
}

const CodePack & BaseEmitter::code_ref() const noexcept {
    return *m_code;
}

EASM_NAMESPACE_END
