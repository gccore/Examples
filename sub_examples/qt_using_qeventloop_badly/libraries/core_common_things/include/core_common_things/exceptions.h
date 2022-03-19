#ifndef LIBRARY_CORE_COMMON_THINGS_EXCEPTIONS_H
#define LIBRARY_CORE_COMMON_THINGS_EXCEPTIONS_H

#include <stdexcept>

namespace core::exceptions {
#define CORE_COMMON_DEFINE_EXCEPTIONS(NAME)                                             \
  class NAME##Exception final : public std::exception {                                 \
  public:                                                                               \
    explicit NAME##Exception(std::string const& message) noexcept : message_(message) { \
    }                                                                                   \
    explicit NAME##Exception(char const* const message) noexcept : message_(message) {  \
    }                                                                                   \
    virtual ~NAME##Exception() = default;                                               \
                                                                                        \
    const char* what() const noexcept override {                                        \
      return message_.c_str();                                                          \
    }                                                                                   \
                                                                                        \
  private:                                                                              \
    std::string const message_;                                                         \
  }

CORE_COMMON_DEFINE_EXCEPTIONS(GlfwInit);
#undef CORE_COMMON_DEFINE_EXCEPTIONS
}  // namespace core::exceptions

#endif
