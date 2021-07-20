#pragma once

#include <type_traits>
#include <array>

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
} // namespace core::util
