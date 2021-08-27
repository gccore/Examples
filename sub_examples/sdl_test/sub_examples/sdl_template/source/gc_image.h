#ifndef GC_SDL_BASICS_GC_IMAGE_H
#define GC_SDL_BASICS_GC_IMAGE_H

#include <string>

#include <SDL2/SDL.h>

namespace core
{
class gc_screen;

class gc_image
{
private:
        gc_screen* m_screen;
        SDL_Surface* m_surface;
        SDL_Surface* m_image_sur;
        std::string m_path;

public:
        enum class loads_mod {
                immediate,
                wait
        };

public:
        gc_image();
        gc_image(gc_screen* screen);
        gc_image(gc_screen* screen, std::string const& path, loads_mod const mode);
        ~gc_image();

        void load_image(std::string const& path);
        void load_image();

};
} // namespace core

#endif // GC_SDL_BASICS_GC_IMAGE_H
