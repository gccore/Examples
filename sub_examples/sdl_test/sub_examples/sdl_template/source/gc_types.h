#ifndef GC_SDL_BASICS_GC_TYPES_H
#define GC_SDL_BASICS_GC_TYPES_H

#include <memory>

#include <SDL2/SDL.h>

namespace core
{
struct surface_deleter_t final
{
	inline void operator()(SDL_Surface* ptr) const
	{
		SDL_FreeSurface(ptr);
	}
};
using image_ptr_t = std::unique_ptr<SDL_Surface, surface_deleter_t>;
} // namespace core

#endif // GC_SDL_BASICS_GC_TYPES_H
