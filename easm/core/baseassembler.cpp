#include <easm/core/baseassembler.h>
#include <easm/core/codepack.h>

EASM_NAMESPACE_BEGIN
    BaseAssembler::BaseAssembler(CodePack& code) noexcept
    : BaseEmitter(code){
}

usize BaseAssembler::offset() const noexcept{
    const CodePack* pack = code();
    return pack ? pack->size() : 0;
}

void BaseAssembler::emit_u8(u8 value){
    code_ref().append_u8(value);
}

void BaseAssembler::emit_bytes(const void* data, usize size){
    code_ref().append_bytes(data, size);
}

EASM_NAMESPACE_END