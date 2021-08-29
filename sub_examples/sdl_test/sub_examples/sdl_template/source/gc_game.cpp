#include "gc_game.h"

#include <filesystem>
#include <stdexcept>

#include "gc_renderer.h"
#include "gc_screen.h"
#include "gc_defs.h"
#include "gc_util.h"
#include "Logger.h"

namespace core
{
gc_game::gc_game(gc_renderer& renderer)
        : m_state(states::unknown),
          m_renderer(renderer),
          m_screen(m_renderer.screen()),
          m_background(&m_renderer)
{
}

void gc_game::execute()
{
        init();
        m_state = states::running;
        load_background();

        SDL_Event events;
        while (states::running == m_state) {
                SDL_WaitEvent(&events);
                if (is_valid_event_type(events)) {
                        m_renderer.clear();
                        event(events);
                        m_renderer.update();
                }
        }

        clean_up();
}

void gc_game::init()
{
        LOG_INFO << "Initializing ...";
        CHECK_FAILED(SDL_Init(SDL_INIT_EVERYTHING), "Couldn't Initialize: " + error());

        int image_flag = IMG_INIT_PNG;
        CHECK_FAILED_2(!(IMG_Init(image_flag) & image_flag), "Couldn't Initialize: " + p_error());

        LOG_INFO << "Rendering Images ... ";
        for (std::size_t i = 0; i < m_textures.size(); ++i) {
                m_textures[i] = gc_texture(&m_renderer);
                m_textures[i].load(m_images_path[i]);
        }
}

void gc_game::handel_keyboard_events(SDL_Event const& event)
{
        switch (event.key.keysym.sym) {
                case SDLK_w:
                        m_textures[keys::up].render();
                        break;
                case SDLK_a:
                        m_textures[keys::left].render();
                        break;
                case SDLK_s:
                        m_textures[keys::down].render();
                        break;
                case SDLK_d:
                        m_textures[keys::rigth].render();
                        break;
                case SDLK_ESCAPE:
                        m_state = states::stopped;
                        break;
                default:
                        m_background.render();
                        break;
        }
}

bool gc_game::is_valid_event_type(const SDL_Event& event)
{
        return SDL_QUIT == event.type || SDL_KEYDOWN == event.type;
}

std::string gc_game::error()
{
        return SDL_GetError();
}

std::string gc_game::p_error()
{
        return IMG_GetError();
}

void gc_game::event(SDL_Event const& event)
{
        if (SDL_QUIT == event.type) {
                m_state = states::stopped;
        } else if (SDL_KEYDOWN == event.type) {
                handel_keyboard_events(event);
        }
}

void gc_game::clean_up()
{
        SDL_Quit();
}

void gc_game::load_background()
{
        m_background.load(util::from_res("background.bmp")).render();
}
} // namespace core
