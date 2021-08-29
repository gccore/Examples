#ifndef GC_SDL_BASICS_GC_TEXTURE_H
#define GC_SDL_BASICS_GC_TEXTURE_H

#include <string>

#include <SDL2/SDL.h>

namespace core
{
class gc_renderer;

class gc_texture
{
private:
        gc_renderer* m_renderer;
        SDL_Texture* m_texture;
        std::string m_path;

public:
        gc_texture();
        gc_texture(gc_renderer* renderer);
        gc_texture(gc_renderer* renderer, std::string const& path);
        ~gc_texture();

        gc_texture& load(std::string const& path);
        gc_texture& load();

        void render();

private:
        static std::string p_error();
        static std::string error();
};
} // namespace core

#endif // GC_SDL_BASICS_GC_TEXTURE_H
