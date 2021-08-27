#include "gc_util.h"

namespace core::util
{
std::string from_res(std::string const& path)
{
        return def::res + ("/" + path);
}
} // namespace core::util
