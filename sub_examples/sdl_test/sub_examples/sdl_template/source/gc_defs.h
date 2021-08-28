#ifndef GC_SDL_BASICS_DEFS_H
#define GC_SDL_BASICS_DEFS_H

#include <cstddef>

namespace core
{
/*!
 * \brief Indicating the object state.
 */
enum class states {
        waiting, /*!< Waiting for something, e.g. Rendering */
        stopped, /*!< Stopped by something */
        running, /*!< On the way */
        unknown, /*!< Initial state */
        failed,  /*!< Failed operation */
        success  /*!< Successed operation */
};

namespace keys
{
enum keys_t {
        up,
        down,
        left,
        rigth
};
} // namespace keys
auto constexpr keys_length = keys::rigth + 1;
} // namespace core

namespace core::def
{
auto constexpr w = 900ULL;
auto constexpr h = 550ULL;
auto constexpr res = PROJECT_BINARY_PATH "/res";
} // namespace core

#define CHECK_NULL(x, m) \
        if (nullptr == x) { \
                LOG_FATAL << m; \
                throw std::runtime_error(m); \
        }

#define CHECK_FAILED(x, m) \
        if (0 != x) { \
                LOG_ERROR << m; \
                throw std::runtime_error(m); \
        }

#define CHECK_PATH_EXIST(x) \
        if (!std::filesystem::exists(x)) { \
                LOG_ERROR << "Path Not Found: " + x; \
                throw std::runtime_error("Path Not Found: " + x); \
        }

#endif // GC_SDL_BASICS_DEFS_H
