#ifndef GC_SDL_BASICS_RENDERER_H
#define GC_SDL_BASICS_RENDERER_H

#include <SDL2/SDL.h>

#include <string>

namespace core
{
class gc_screen;

class gc_renderer
{
private:
        gc_screen& m_screen;
        SDL_Renderer* m_renderer;

public:
        gc_renderer(gc_screen& window);
        ~gc_renderer();

        void clear_to_blank();

        SDL_Renderer* renderer() const;
        gc_screen& screen() const;

private:
        static std::string error();
};
} // namespace core

#endif // GC_SDL_BASICS_RENDERER_H
