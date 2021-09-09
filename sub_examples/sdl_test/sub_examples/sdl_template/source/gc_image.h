#ifndef GC_SDL_BASICS_GC_IMAGE_H
#define GC_SDL_BASICS_GC_IMAGE_H

#include <memory>
#include <string>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "gc_types.h"

namespace core
{
class gc_screen;

class gc_image
{
    private:
	gc_screen* m_screen;
	SDL_Surface* m_surface;
	SDL_Surface* m_image_sur;
	std::string m_path;

    public:
	gc_image();
	gc_image(gc_screen* screen);
	gc_image(gc_screen* screen, std::string const& path);
	~gc_image();

	gc_image& load(std::string const& path);
	gc_image& load();

	void render();
	void render(int const width, int const heigth);

    private:
	void deallocate();
	void deallocate_previous_image();
	void set_path(std::string const& path);
	void load_by_prefix();
	image_ptr_t load_bmp();
	image_ptr_t load_png();
	void convert_surface(image_ptr_t&& image);

	static std::string error();
	static std::string p_error();
};
} // namespace core

#endif // GC_SDL_BASICS_GC_IMAGE_H
