#ifndef SIMDUTF_HASWELL_IMPLEMENTATION_H
#define SIMDUTF_HASWELL_IMPLEMENTATION_H

#include "simdutf/implementation.h"

// The constructor may be executed on any host, so we take care not to use SIMDUTF_TARGET_REGION
namespace simdutf {
namespace haswell {

using namespace simdutf;

class implementation final : public simdutf::implementation {
public:
  simdutf_really_inline implementation() : simdutf::implementation(
      "haswell",
      "Intel/AMD AVX2",
      internal::instruction_set::AVX2 | internal::instruction_set::PCLMULQDQ | internal::instruction_set::BMI1 | internal::instruction_set::BMI2
  ) {}
  simdutf_warn_unused bool validate_utf8(const char *buf, size_t len) const noexcept final;
  simdutf_warn_unused bool validate_ascii(const char *buf, size_t len) const noexcept final;
  simdutf_warn_unused bool validate_utf16(const char16_t *buf, size_t len) const noexcept final;
  simdutf_warn_unused size_t convert_utf8_to_utf16(const char * buf, size_t len, char16_t* utf16_output) const noexcept final;
  simdutf_warn_unused size_t convert_valid_utf8_to_utf16(const char * buf, size_t len, char16_t* utf16_buffer) const noexcept final;
  simdutf_warn_unused size_t convert_utf16_to_utf8(const char16_t * buf, size_t len, char* utf8_buffer) const noexcept final;
  simdutf_warn_unused size_t convert_valid_utf16_to_utf8(const char16_t * buf, size_t len, char* utf8_buffer) const noexcept final;
  simdutf_warn_unused size_t count_utf16(const char16_t * buf, size_t length) const noexcept;
  simdutf_warn_unused size_t count_utf8(const char * buf, size_t length) const noexcept;
  simdutf_warn_unused size_t utf8_length_from_utf16(const char16_t * input, size_t length) const noexcept;
  simdutf_warn_unused size_t utf16_length_from_utf8(const char * input, size_t length) const noexcept;
};

} // namespace haswell
} // namespace simdutf

#endif // SIMDUTF_HASWELL_IMPLEMENTATION_H
