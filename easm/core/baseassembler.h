#ifndef EASM_CORE_BASEASSEMBLER_H
#define EASM_CORE_BASEASSEMBLER_H

#include <easm/base/base.h>
#include <easm/core/baseemitter.h>

EASM_NAMESPACE_BEGIN

class BaseAssembler : public BaseEmitter {
public:
    BaseAssembler() = default;
    explicit BaseAssembler(CodePack& code) noexcept;
    ~BaseAssembler() override = default;

    EASM_DISABLE_COPY_AND_MOVE(BaseAssembler);

    [[nodiscard]] usize offset() const noexcept;

protected:
    void emit_u8(u8 value);
    void emit_bytes(const void* data, usize size);
};

EASM_NAMESPACE_END

#endif // EASM_CORE_BASEASSEMBLER_H