#include "gc_game.h"

#include <filesystem>
#include <stdexcept>

#include "gc_renderer.h"
#include "gc_screen.h"
#include "Logger.h"

namespace core
{
gc_game::gc_game(gc_renderer& renderer)
        : m_state(states::unknown),
          m_renderer(renderer),
          m_screen(m_renderer.screen()),
          m_background(m_screen)
{
}

void gc_game::execute()
{
        init();

        SDL_Event events;
        m_state = states::running;
        m_renderer.clear_to_blank();

        while (states::running == m_state) {
                render();
                SDL_WaitEvent(&events);

                while (0 != SDL_PollEvent(&events)) {
                        event(events);
                }
        }

        clean_up();
}

void gc_game::init()
{
        LOG_INFO << "Initializing ...";
        if (0 > SDL_Init(SDL_INIT_EVERYTHING)) {
                LOG_FATAL << "Couldn't Initialize: " << SDL_GetError();
                throw std::runtime_error("Couldn't Initialize: "
                                         + std::string(SDL_GetError()));
        }

        LOG_INFO << "Loading Background.";
        m_background.load_image(def::res + std::string("/avatar.bmp"));
}

void gc_game::event(SDL_Event const& event)
{
        if (SDL_QUIT == event.type) {
                m_state = states::stopped;
        }
}

void gc_game::render()
{
//        auto const surface = SDL_GetWindowSurface(m_screen.window());
//        SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
        m_screen.update();
}

void gc_game::clean_up()
{
        SDL_Quit();
}
} // namespace core
