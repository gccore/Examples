#ifndef GC_SDL_BASICS_GAME_H
#define GC_SDL_BASICS_GAME_H

#include <SDL2/SDL.h>

#include "gc_image.h"
#include "gc_defs.h"

namespace core
{
class gc_renderer;
class gc_screen;

class gc_game
{
private:
        states m_state;
        gc_renderer& m_renderer;
        gc_screen& m_screen;
        gc_image m_background;

public:
        gc_game(gc_renderer& renderer);
        void execute();

private:
        void init();
        void event(SDL_Event const& event);
        void render();
        void clean_up();
};
} // namespace core

#endif // GC_SDL_BASICS_GAME_H
