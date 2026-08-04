#include "codeholder.h"

namespace Easm {

    CodeHolder::CodeHolder(Environment environment) noexcept
        : CodeHolder(environment, default_allocator()){
    }

    CodeHolder::CodeHolder(Environment environment, Allocator allocator) noexcept
        : m_environment(environment),
        m_code(allocator),
        m_labels(allocator){
    }

    CodeHolder::~CodeHolder() noexcept = default;

    CodeHolder::CodeHolder(CodeHolder&& other) noexcept
        : m_environment(other.m_environment),
        m_code(
            static_cast<CodeBuffer &&>(
                other.m_code
            )
        ),
        m_labels(
            static_cast<PodArray<LabelEntry>&&>(
                other.m_labels
            )
        ) {
        other.m_environment = Environment{};
    }

    CodeHolder& CodeHolder::operator=(CodeHolder&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        m_environment = other.m_environment;

        m_code = static_cast<CodeBuffer&&>(
            other.m_code
        );

        m_labels = static_cast<PodArray<LabelEntry>&&>(
            other.m_labels
        );

        other.m_environment = Environment{};

        return *this;
    }

    bool CodeHolder::valid() const noexcept {
        return m_environment.valid() &&
                m_code.allocator().valid() &&
                m_labels.allocator().valid();
    }

    Error CodeHolder::create_label(Label &label) noexcept {
        label = {};

        if (!valid()) {
            return Error::InvalidState;
        }

        if (m_labels.size() >= static_cast<usize>(InvalidLabelId)) {
            return Error::BufferTooLarge;
        }

        constexpr LabelEntry entry{};

        const Error append_error = m_labels.append(entry);
        if (failed(append_error)) {
            return append_error;
        }

        label = Label{
            static_cast<LabelId>(m_labels.size() - 1)
        };

        return Error::Success;
    }

    Error CodeHolder::bind_label(Label label) noexcept {
        return bind_label(label, m_code.size());
    }

    Error CodeHolder::bind_label(Label label, usize offset) noexcept {
        if (!valid_label_id(label)) {
            return Error::InvalidLabel;
        }

        if (offset > m_code.size()) {
            return Error::InvalidArgument;
        }

        LabelEntry& entry = m_labels[static_cast<usize>(label.id())];

        if (entry.bound) {
            return Error::LabelAlreadyBound;
        }

        entry.offset = offset;
        entry.bound = true;

        return Error::Success;
    }

    bool CodeHolder::label_bound(Label label) const noexcept {
        if (!valid_label_id(label)) {
            return false;
        }
        return m_labels[static_cast<usize>(label.id())].bound;
    }

    Error CodeHolder::label_offset(Label label, usize &out_offset) const noexcept {
        out_offset = 0;

        if (!valid_label_id(label)) {
            return Error::InvalidLabel;
        }

        const LabelEntry& entry = m_labels[static_cast<usize>(label.id())];

        if (!entry.bound) {
            return Error::LabelNotBound;
        }

        out_offset = entry.offset;

        return Error::Success;
    }

    bool CodeHolder::valid_label_id(Label label) const noexcept {
        return label.valid() && static_cast<usize>(label.id()) < m_labels.size();
    }
}
