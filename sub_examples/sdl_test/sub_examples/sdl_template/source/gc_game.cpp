#include "gc_game.h"

#include "gc_renderer.h"
#include "gc_screen.h"

namespace core
{
gc_game::gc_game(gc_renderer& renderer)
        : m_state(states::unknown),
          m_renderer(renderer),
          m_screen(m_renderer.screen())
{
}

states gc_game::execute()
{
        states state = this->init();

        if (states::success == state) {
                SDL_Event events;
                this->m_state = states::running;

                while (states::running == this->m_state) {
                        while (SDL_PollEvent(&events)) {
                                this->event(events);
                        }

                        this->loop();
                        this->render();
                }

                this->clean_up();
        }

        return state;
}

states gc_game::init()
{
        if (0 > SDL_Init(SDL_INIT_EVERYTHING)) {
                return states::failed;
        }
        if (nullptr == m_screen.window() ||
            nullptr == m_renderer.renderer()) {
                return states::failed;
        }



        return states::success;
}

void gc_game::event(SDL_Event& event)
{
}

void gc_game::loop()
{
}

void gc_game::render()
{
}

void gc_game::clean_up()
{
        SDL_Quit();
}
} // namespace core
