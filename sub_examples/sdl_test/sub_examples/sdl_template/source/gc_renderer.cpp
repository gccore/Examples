#include "gc_renderer.h"

#include "gc_screen.h"

namespace core
{
gc_renderer::gc_renderer(gc_screen& window)
        : m_screen(window),
          m_renderer(SDL_CreateRenderer(m_screen.window(), -1, SDL_RENDERER_PRESENTVSYNC))
{
}

gc_renderer::~gc_renderer()
{
        SDL_DestroyRenderer(m_renderer);
}

SDL_Renderer* gc_renderer::renderer() const
{
        return m_renderer;
}

gc_screen& gc_renderer::screen() const
{
        return m_screen;
}
} // namespace core
