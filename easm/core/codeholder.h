#ifndef EASM_CORE_CODEHOLDER_H
#define EASM_CORE_CODEHOLDER_H

#include <easm/base/container/podarray.h>
#include <easm/base/error.h>
#include <easm/base/memory/allocator.h>
#include <easm/base/type.h>
#include "codebuffer.h"
#include "environment.h"
#include "label.h"

namespace Easm {

    class BaseEmitter;

    class EASM_API CodeHolder final {
    public:
        explicit CodeHolder(Environment environment) noexcept;

        CodeHolder(Environment environment, Allocator allocator) noexcept;

        ~CodeHolder() noexcept;

        EASM_DELETE_COPY(CodeHolder);

        CodeHolder(CodeHolder&& other) noexcept;

        CodeHolder& operator=(CodeHolder&& other) noexcept;

        [[nodiscard]]
        bool valid() const noexcept;

        [[nodiscard]]
        Environment environment() const noexcept {
            return m_environment;
        }

        [[nodiscard]]
        Allocator allocator() const noexcept {
            return m_code.allocator();
        }

        [[nodiscard]]
        const CodeBuffer& code() const noexcept {
            return m_code;
        }

        [[nodiscard]]
        usize label_count() const noexcept {
            return m_labels.size();
        }

        [[nodiscard]]
        Error create_label(Label& label) noexcept;

        [[nodiscard]]
        bool label_bound(Label label) const noexcept;

        [[nodiscard]]
        Error label_offset(Label label, usize& out_offset) const noexcept;

    private:
        struct LabelEntry final {
            usize offset = 0;
            bool bound = false;
        };

        [[nodiscard]]
        Error bind_label(Label label) noexcept;

        [[nodiscard]]
        Error bind_label(Label label, usize offset) noexcept;

        [[nodiscard]]
        CodeBuffer& mutable_code() noexcept {
            return m_code;
        }

        [[nodiscard]]
        bool valid_label_id(Label label) const noexcept;

        Environment m_environment;
        CodeBuffer m_code;
        PodArray<LabelEntry> m_labels;

        friend class BaseEmitter;
    };
} // namespace Easm
#endif //EASM_CORE_CODEHOLDER_H
