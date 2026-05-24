#ifndef EASM_BASE_VERSION_H
#define EASM_BASE_VERSION_H

#define EASM_VERSION_MAJOR 0
#define EASM_VERSION_MINOR 1
#define EASM_VERSION_PATCH 0

#define EASM_MAKE_VERSION(major, minor, patch)                               \
    (((major) << 16) | ((minor) << 8) | (patch))

#define EASM_VERSION                                                         \
    EASM_MAKE_VERSION(EASM_VERSION_MAJOR, EASM_VERSION_MINOR, EASM_VERSION_PATCH)

namespace Easm {

struct Version {
    unsigned major;
    unsigned minor;
    unsigned patch;
};

inline constexpr Version CurrentVersion{
    EASM_VERSION_MAJOR,
    EASM_VERSION_MINOR,
    EASM_VERSION_PATCH
};

inline constexpr unsigned CurrentVersionPacked = EASM_VERSION;

} // namespace Easm

#endif // EASM_BASE_VERSION_H
