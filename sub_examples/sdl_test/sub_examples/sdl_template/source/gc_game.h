#ifndef GC_SDL_BASICS_GAME_H
#define GC_SDL_BASICS_GAME_H

#include <SDL2/SDL.h>

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

public:
        gc_game(gc_renderer& renderer);
        states execute();

private:
        states init();
        void event(SDL_Event& event);
        void loop();
        void render();
        void clean_up();
};
} // namespace core

#endif // GC_SDL_BASICS_GAME_H
