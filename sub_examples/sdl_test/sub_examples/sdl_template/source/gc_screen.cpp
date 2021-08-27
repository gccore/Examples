#include "gc_screen.h"
#include "gc_defs.h"

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
        this->m_caption = caption;
        SDL_SetWindowTitle(this->m_window, this->m_caption.c_str());
}

SDL_Window* gc_screen::window() const
{
        return this->m_window;
}
} // namespace core
