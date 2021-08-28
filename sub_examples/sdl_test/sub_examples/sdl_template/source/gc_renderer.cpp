#include "gc_renderer.h"

#include <stdexcept>

#include "gc_screen.h"
#include "gc_defs.h"
#include "Logger.h"

namespace core
{
gc_renderer::gc_renderer(gc_screen& window)
        : m_screen(window),
          m_renderer(SDL_CreateRenderer(m_screen.window(), -1, SDL_RENDERER_PRESENTVSYNC))
{
        CHECK_NULL(m_renderer, "Couldn't Create Renderer: " + error());
}

gc_renderer::~gc_renderer()
{
        SDL_DestroyRenderer(m_renderer);
}

void gc_renderer::clear_to_blank()
{
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);
        SDL_RenderPresent(m_renderer);
}

SDL_Renderer* gc_renderer::renderer() const
{
        return m_renderer;
}

gc_screen& gc_renderer::screen() const
{
        return m_screen;
}

std::string gc_renderer::error()
{
        return SDL_GetError();
}
} // namespace core
