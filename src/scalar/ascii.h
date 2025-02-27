#ifndef SIMDUTF_ASCII_H
#define SIMDUTF_ASCII_H

namespace simdutf {
namespace scalar {
namespace {
namespace ascii {

    inline simdutf_warn_unused bool validate(const char *buf, size_t len) noexcept {
    const uint8_t *data = reinterpret_cast<const uint8_t *>(buf);
    uint64_t pos = 0;
    // process in blocks of 16 bytes when possible
    for (;pos + 16 < len; pos += 16) {
        uint64_t v1;
        std::memcpy(&v1, data + pos, sizeof(uint64_t));
        uint64_t v2;
        std::memcpy(&v2, data + pos + sizeof(uint64_t), sizeof(uint64_t));
        uint64_t v{v1 | v2};
        if ((v & 0x8080808080808080) != 0) { return false; }
    }
    // process the tail byte-by-byte
    for (;pos < len; pos ++) {
        if (data[pos] >= 0b10000000) { return false; }
    }
    return true;
    }

} // ascii namespace
} // unnamed namespace
} // namespace scalar
} // namespace simdutf

#endif