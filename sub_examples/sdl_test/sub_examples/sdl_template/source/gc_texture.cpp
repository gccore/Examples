#include "gc_texture.h"

#include <SDL2/SDL_image.h>

#include "gc_renderer.h"
#include "gc_types.h"
#include "gc_defs.h"

namespace core
{
gc_texture::gc_texture()
        : m_renderer(nullptr),
          m_texture(nullptr)
{
}

gc_texture::gc_texture(gc_renderer* renderer)
        : m_renderer(renderer),
          m_texture(nullptr)
{
        CHECK_NULL(m_renderer, "Couldn't Accept NULL GC_Renderer.");
}

gc_texture::gc_texture(gc_renderer* renderer, std::string const& path)
        : m_renderer(renderer),
          m_texture(nullptr),
          m_path(path)
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

        image_ptr_t surface(IMG_Load(m_path.c_str()));
        CHECK_NULL(surface, "Couldn't Load Texture: " + m_path + ". Error : " + p_error());

        m_texture = SDL_CreateTextureFromSurface(m_renderer->renderer(), surface.get());
        CHECK_NULL(m_texture, "Couldn't Load Texture: " + error());

        return *this;
}

void gc_texture::render()
{
        LOG_INFO << "Rendering Texture: " << m_path;
        CHECK_FAILED(SDL_RenderCopy(m_renderer->renderer(), m_texture, nullptr, nullptr),
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
