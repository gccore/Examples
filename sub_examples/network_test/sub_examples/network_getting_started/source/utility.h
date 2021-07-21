#pragma once

#include <type_traits>
#include <string>
#include <array>

extern "C" {
#include <unistd.h>
#include <errno.h>
}

#include "exception.hpp"
#include "constant.h"

namespace core::util {
template <auto const Lower, auto const Upper,
          typename CommonType = std::common_type_t<decltype(Lower), decltype(Upper)>>
struct range final {
  std::array < CommonType, Upper - Lower > list;

  inline constexpr range() noexcept {
    for (std::size_t i = 0; i < list.size(); ++i) {
      list[i] = static_cast<CommonType>(i);
    }
  }

  inline auto constexpr begin() noexcept {
    return list.cbegin();
  }
  inline auto constexpr end() noexcept {
    return list.cend();
  }
};

inline auto host_name() {
  std::string result;
  result.resize(_SC_HOST_NAME_MAX, constant::string::nul);
  auto const ret_status = ::gethostname(result.data(), result.size());

  if (constant::socket::error == ret_status) {
    throw exception("gethostname() failed: " + std::string(strerror(errno)));
  }

  return result;
}
} // namespace core::util
