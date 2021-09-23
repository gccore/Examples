#include "gc_texture.h"

#include <SDL2/SDL_image.h>

#include "gc_renderer.h"
#include "gc_types.h"
#include "gc_defs.h"

namespace core
{
gc_texture::gc_texture()
	: m_renderer(nullptr)
	, m_texture(nullptr)
	, m_color({0xFF, 0xFF, 0xFF})
	, m_blend_mode(SDL_BLENDMODE_NONE)
	, m_alpha(0xFF)
{
}

gc_texture::gc_texture(gc_renderer* renderer)
	: m_renderer(renderer)
	, m_texture(nullptr)
	, m_color({0xFF, 0xFF, 0xFF})
	, m_blend_mode(SDL_BLENDMODE_NONE)
	, m_alpha(0xFF)
{
	CHECK_NULL(m_renderer, "Couldn't Accept NULL GC_Renderer.");
}

gc_texture::gc_texture(gc_renderer* renderer, std::string const& path)
	: m_renderer(renderer)
	, m_texture(nullptr)
	, m_path(path)
	, m_color({0xFF, 0xFF, 0xFF})
	, m_blend_mode(SDL_BLENDMODE_NONE)
	, m_alpha(0xFF)
{
	CHECK_NULL(m_renderer, "Couldn't Accept NULL GC_Renderer.");
	CHECK_PATH_EXIST(m_path);
	load();
}

gc_texture::~gc_texture()
{
	LOG_INFO << "Destroying Texture: " << m_path;
	SDL_DestroyTexture(m_texture);
}

gc_texture& gc_texture::load(std::string const& path)
{
	CHECK_PATH_EXIST(path);
	m_path = path;
	load();

	return *this;
}

gc_texture& gc_texture::load()
{
	LOG_INFO << "Loading Texture: " << m_path;

	CHECK_NULL(m_renderer, "Couldn't Load Renderer.");

	image_ptr_t surface(IMG_Load(m_path.c_str()));
	CHECK_NULL(surface, "Couldn't Load Texture: " + m_path + ". Error : " + p_error());

	m_texture = SDL_CreateTextureFromSurface(m_renderer->renderer(), surface.get());
	CHECK_NULL(m_texture, "Couldn't Load Texture: " + error());
	m_size.width = surface->w;
	m_size.height = surface->h;

	return *this;
}

void gc_texture::set_blend_mode(SDL_BlendMode const mode)
{
	m_blend_mode = mode;
	SDL_SetTextureBlendMode(m_texture, m_blend_mode);
}

SDL_BlendMode gc_texture::get_blend_mode() const
{
	return m_blend_mode;
}

void gc_texture::set_alpha(alpha_t const alpha)
{
	m_alpha = alpha;
	SDL_SetTextureAlphaMod(m_texture, m_alpha);
}

alpha_t gc_texture::get_alpha() const
{
	return m_alpha;
}

void gc_texture::set_color(color_t const& color)
{
	m_color = color;
	CHECK_FAILED(SDL_SetTextureColorMod(m_texture, m_color.red, m_color.green, m_color.blue),
		     "Couldn't Set Color Mode: " + error());
}

color_t gc_texture::get_color() const
{
	return m_color;
}

size_t gc_texture::get_size() const
{
	return m_size;
}

void gc_texture::render(pos_t const pos, gc_ptr<SDL_Rect> const& clip, double const angle,
			gc_ptr<SDL_Point> const& center, SDL_RendererFlip const flip_mode)
{
	LOG_INFO << "Rendering Texture: " << m_path;
	SDL_Rect render_quad = {pos.x, pos.y, m_size.width, m_size.height};
	if(nullptr != clip)
	{
		render_quad.w = clip->w;
		render_quad.h = clip->h;
	}
	CHECK_FAILED(SDL_RenderCopyEx(m_renderer->renderer(),
				      m_texture,
				      clip.data(),
				      &render_quad,
				      angle,
				      center.data(),
				      flip_mode),
		     "Couldn't Render Texture: " + m_path + ". Error: " + error());
}

void gc_texture::render(core::pos_t const pos, gc_ptr<SDL_Rect> const& rect)
{
	LOG_INFO << "Rendering Texture: " << m_path;
	SDL_Rect render_quad = {pos.x, pos.y, m_size.width, m_size.height};
	if(nullptr != rect)
	{
		render_quad.w = rect->w;
		render_quad.h = rect->h;
	}
	CHECK_FAILED(SDL_RenderCopy(m_renderer->renderer(), m_texture, rect.data(), &render_quad),
		     "Couldn't Render Texture: " + m_path + ". Error: " + error());
}

void gc_texture::render(gc_ptr<SDL_Rect> const& rect)
{
	LOG_INFO << "Rendering Texture: " << m_path;
	CHECK_FAILED(SDL_RenderCopy(m_renderer->renderer(), m_texture, rect.data(), nullptr),
		     "Couldn't Render Texture: " + m_path + ". Error: " + error());
}

std::string gc_texture::p_error()
{
	return IMG_GetError();
}

std::string gc_texture::error()
{
	return SDL_GetError();
}
} // namespace core
