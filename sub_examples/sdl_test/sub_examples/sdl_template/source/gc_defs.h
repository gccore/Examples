#ifndef GC_SDL_BASICS_DEFS_H
#define GC_SDL_BASICS_DEFS_H

#include <filesystem>
#include <stdexcept>
#include <cstddef>

#include "Logger.h"

namespace core
{
/*!
 * \brief Indicating the object state.
 */
enum class states
{
	waiting, /*!< Waiting for something, e.g. Rendering */
	stopped, /*!< Stopped by something */
	running, /*!< On the way */
	unknown, /*!< Initial state */
	failed, /*!< Failed operation */
	success /*!< Successed operation */
};

namespace keys
{
enum keys_t
{
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
auto constexpr w = 900;
auto constexpr h = 550;
auto constexpr res = PROJECT_BINARY_PATH "/res";
} // namespace core::def

namespace core
{
using alpha_t = std::uint8_t;
struct size_t final
{
	int width = 0ULL;
	int height = 0ULL;
};
struct pos_t final
{
	int x = 0;
	int y = 0;

	pos_t() = default;
	pos_t(int const x_, int const y_)
		: x(x_)
		, y(y_)
	{
	}

	pos_t& operator*(int const i)
	{
		x *= i;
		y *= i;
		return *this;
	}
};
struct color_t final
{
	std::uint8_t red;
	std::uint8_t green;
	std::uint8_t blue;
};
} // namespace core

#define CHECK_NULL(x, m)                                                                           \
	if(nullptr == x)                                                                           \
	{                                                                                          \
		LOG_FATAL << m;                                                                    \
		throw std::runtime_error(m);                                                       \
	}

#define CHECK_FAILED(x, m)                                                                         \
	if(0 != x)                                                                                 \
	{                                                                                          \
		LOG_ERROR << m;                                                                    \
		throw std::runtime_error(m);                                                       \
	}

#define CHECK_FAILED_2(x, m)                                                                       \
	if(x)                                                                                      \
	{                                                                                          \
		LOG_ERROR << m;                                                                    \
		throw std::runtime_error(m);                                                       \
	}

#define CHECK_WARNING(x, m)                                                                        \
	if(x)                                                                                      \
	{                                                                                          \
		LOG_WARN << m;                                                                     \
	}

#define CHECK_PATH_EXIST(x)                                                                        \
	if(!std::filesystem::exists(x))                                                            \
	{                                                                                          \
		LOG_ERROR << "Path Not Found: " + x;                                               \
		throw std::runtime_error("Path Not Found: " + x);                                  \
	}

#define ERROR(x)                                                                                   \
	LOG_FATAL << x;                                                                            \
	throw std::runtime_error(x);

#endif // GC_SDL_BASICS_DEFS_H
