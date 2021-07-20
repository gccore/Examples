#pragma once

#include <exception>
#include <string>

namespace core {
struct exception final: std::exception {
  std::string message;
  exception(std::string const& message_)
    : message(message_) {
  }
  const char* what() const noexcept override {
    return message.c_str();
  }
};
} // namespace core
