#include "gc_screen.h"
#include "gc_defs.h"

#include <stdexcept>

namespace core
{
gc_screen::gc_screen(std::string const& caption,
                     std::size_t const width,
                     std::size_t const height)
        : m_caption(caption),
          m_width(width),
          m_height(height),
          m_window(SDL_CreateWindow(m_caption.c_str(),
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    m_width, m_height,
                                    SDL_WINDOW_OPENGL))
{
        if (nullptr == m_window) {
                throw std::runtime_error("Couldn't Create Window: "
                                         + std::string(SDL_GetError()));
        }
}
gc_screen::gc_screen(std::string const& caption)
        : gc_screen(caption, def::w, def::h)
{
}

gc_screen::~gc_screen()
{
        SDL_DestroyWindow(m_window);
}

void gc_screen::set_caption(std::string const& caption)
{
        m_caption = caption;
        SDL_SetWindowTitle(m_window, m_caption.c_str());
}

SDL_Window* gc_screen::window() const
{
        return m_window;
}

void gc_screen::update() const
{
        SDL_UpdateWindowSurface(m_window);
}
} // namespace core
