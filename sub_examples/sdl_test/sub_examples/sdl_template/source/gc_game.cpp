#include "gc_game.h"

#include <filesystem>
#include <stdexcept>

#include "gc_renderer.h"
#include "gc_screen.h"
#include "gc_util.h"
#include "Logger.h"

namespace core
{
gc_game::gc_game(gc_renderer& renderer)
        : m_state(states::unknown),
          m_renderer(renderer),
          m_screen(m_renderer.screen()),
          m_background(&m_screen)
{
}

void gc_game::execute()
{
        init();

        m_state = states::running;
        m_renderer.clear_to_blank();

        colorize_background();
        load_background();

        SDL_Event events;
        while (states::running == m_state) {
                while (0 != SDL_PollEvent(&events)) {
                        event(events);
                }

                render();
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

        LOG_INFO << "Rendering Images ... ";
        for (std::size_t i = 0; i < m_images.size(); ++i) {
                m_images[i] = gc_image(&m_screen);
                m_images[i].load_image(m_images_path[i]);
        }
}

void gc_game::handel_keyboard_events(SDL_Event const& event)
{
        m_background.render();
        switch (event.key.keysym.sym) {
                case SDLK_w:
                        m_images[keys::up].render();
                        break;
                case SDLK_a:
                        m_images[keys::left].render();
                        break;
                case SDLK_s:
                        m_images[keys::down].render();
                        break;
                case SDLK_d:
                        m_images[keys::rigth].render();
                        break;
                default:
                        m_background.render();
                        break;
        }
}

void gc_game::event(SDL_Event const& event)
{
        if (SDL_QUIT == event.type) {
                m_state = states::stopped;
        } else if (SDL_KEYDOWN == event.type) {
                handel_keyboard_events(event);
        }
}

void gc_game::render()
{
        m_screen.update();
}

void gc_game::clean_up()
{
        SDL_Quit();
}

void gc_game::load_background()
{
        m_background.load_image(util::from_res("background.bmp")).render();
}

void gc_game::colorize_background()
{
        auto const surface = SDL_GetWindowSurface(m_screen.window());
        SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, 0x0, 0x0, 0x0, 0x0));
}
} // namespace core
