#ifndef GC_SDL_BASICS_SCREEN_H
#define GC_SDL_BASICS_SCREEN_H

#include <string>
#include <memory>

#include <SDL2/SDL.h>

namespace core
{
class gc_screen
{
private:
        std::string m_caption;
        std::size_t m_width;
        std::size_t m_height;
        SDL_Window* m_window;

public:
        gc_screen(std::string const& caption,
                  std::size_t const width,
                  std::size_t const height);
        gc_screen(std::string const& caption);
        ~gc_screen();

        void set_caption(std::string const& caption);
        std::string caption() const;

        SDL_Window* window() const;

        void update() const;
};
} // namespace core

#endif // GC_SDL_BASICS_SCREEN_H
