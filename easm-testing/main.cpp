#include <easm/base/base.h>
#include <easm/core/codebuffer.h>
#include <iostream>

int main()
{
    Easm::CodeBuffer buffer;
    (void)buffer;

    std::cout << "easm-testing: include easm/core/codebuffer.h ok" << std::endl;
    std::cout << "Easm version: "
              << Easm::CurrentVersion.major << '.'
              << Easm::CurrentVersion.minor << '.'
              << Easm::CurrentVersion.patch << std::endl;

    static_assert(EASM_VERSION == EASM_MAKE_VERSION(0, 1, 0));
    static_assert(Easm::CurrentVersionPacked == EASM_VERSION);
    return 0;
}
