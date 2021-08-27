#ifndef GC_SDL_BASICS_DEFS_H
#define GC_SDL_BASICS_DEFS_H

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
} // namespace core

namespace core::def
{
auto constexpr w = 800ULL;
auto constexpr h = 600ULL;
auto constexpr res = PROJECT_BINARY_PATH "/res";
} // namespace core

#endif // GC_SDL_BASICS_DEFS_H
