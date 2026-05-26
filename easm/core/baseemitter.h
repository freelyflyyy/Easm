#ifndef EASM_CORE_BASEEMITTER_H
#define EASM_CORE_BASEEMITTER_H

#include <easm/base/base.h>

EASM_NAMESPACE_BEGIN

class CodePack;

class BaseEmitter {
public:
    BaseEmitter() = default;
    explicit BaseEmitter(CodePack& code) noexcept;
    virtual ~BaseEmitter() = default;

    EASM_DISABLE_COPY_AND_MOVE(BaseEmitter);

    [[nodiscard]]
    bool attached() const noexcept;
    [[nodiscard]]
    CodePack* code() noexcept;
    [[nodiscard]]
    const CodePack* code() const noexcept;

    void attach(CodePack& code) noexcept;
    void detach();

protected:
    [[nodiscard]]
    CodePack& code_ref() noexcept;
    [[nodiscard]]
    const CodePack& code_ref() const noexcept;
private:
    CodePack* m_code = nullptr;
};

EASM_NAMESPACE_END

#endif // EASM_CORE_BASEEMITTER_H
