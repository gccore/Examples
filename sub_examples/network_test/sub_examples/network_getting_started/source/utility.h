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

namespace core::util
{
template<std::size_t From, std::size_t To>
class range
{
public:
        // member typedefs provided through inheriting from std::iterator
        class iterator: public
                std::iterator<std::input_iterator_tag,std::size_t,
                std::size_t, const std::size_t*, std::size_t>
        {
                std::size_t num = From;
        public:
                explicit constexpr iterator(std::size_t _num = 0) : num(_num)
                {}
                inline iterator constexpr& operator++()
                {
                        num = To >= From ? num + 1: num - 1;
                        return *this;
                }
                inline auto constexpr operator++(int)
                {
                        iterator retval = *this;
                        ++(*this);
                        return retval;
                }
                inline auto constexpr operator==(iterator other) const
                {
                        return num == other.num;
                }
                inline auto constexpr operator!=(iterator other) const
                {
                        return !(*this == other);
                }
                inline reference constexpr operator*() const
                {
                        return num;
                }
        };
        inline auto constexpr begin() const
        {
                return iterator(From);
        }
        inline auto constexpr end() const
        {
                return iterator(To >= From? To+1 : To-1);
        }
};

template <std::size_t Length, typename Operator, typename ... Args>
constexpr void repeat_for(Operator ope, Args&& ... args)
{
        for (auto const _ : range<0, Length>()) {
                (void)_;
                ope(std::forward(args) ...);
        }
}

inline auto host_name()
{
        std::string result;
        result.resize(_SC_HOST_NAME_MAX, constant::string::nul);
        auto const ret_status = ::gethostname(result.data(), result.size());

        if (constant::socket::error == ret_status) {
                throw exception("gethostname() failed: " + std::string(strerror(errno)));
        }

        return result;
}
} // namespace core::util
