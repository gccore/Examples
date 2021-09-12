#ifndef GC_SDL_BASICS_GC_TEXTURE_H
#define GC_SDL_BASICS_GC_TEXTURE_H

#include <string>

#include <SDL2/SDL.h>

#include "gc_ptr.hpp"
#include "gc_defs.h"

namespace core
{
class gc_renderer;

class gc_texture
{
    private:
	gc_renderer* m_renderer;
	SDL_Texture* m_texture;
	std::string m_path;
	core::size_t m_size;
	color_t m_color;
	SDL_BlendMode m_blend_mode;
	alpha_t m_alpha;

    public:
	gc_texture();
	gc_texture(gc_renderer* renderer);
	gc_texture(gc_renderer* renderer, std::string const& path);
	~gc_texture();

	gc_texture& load(std::string const& path);
	gc_texture& load();

	void set_blend_mode(SDL_BlendMode const mode);
	SDL_BlendMode get_blend_mode() const;

	void set_alpha(alpha_t const alpha);
	alpha_t get_alpha() const;

	void set_color(color_t const& color);
	color_t get_color() const;

	void render(core::pos_t const pos, gc_ptr<SDL_Rect> const& rect = nullptr);
	void render(gc_ptr<SDL_Rect> const& rect = nullptr);

    private:
	static std::string p_error();
	static std::string error();
};
} // namespace core

#endif // GC_SDL_BASICS_GC_TEXTURE_H
