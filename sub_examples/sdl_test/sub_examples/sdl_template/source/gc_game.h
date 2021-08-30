#ifndef GC_SDL_BASICS_GAME_H
#define GC_SDL_BASICS_GAME_H

#include <array>

#include <SDL2/SDL.h>

#include "gc_texture.h"
#include "gc_image.h"
#include "gc_defs.h"

namespace core
{
class gc_renderer;
class gc_screen;

class gc_game
{
private:
        template <std::size_t Length>
        using gc_texture_list = std::array<gc_texture, Length>;

        static inline constexpr
        std::array<char const*, keys_length> m_images_path = {
                PROJECT_BINARY_PATH "/res/up.png",
                PROJECT_BINARY_PATH "/res/down.png",
                PROJECT_BINARY_PATH "/res/left.png",
                PROJECT_BINARY_PATH "/res/right.png",
        };

private:
        states m_state;
        gc_renderer& m_renderer;
        gc_screen& m_screen;
        gc_texture m_background;
        gc_texture_list<keys_length> m_textures;

public:
        gc_game(gc_renderer& renderer);
        void execute();

private:
        void init();
        void init_tagv1();
        void event(SDL_Event const& event);
        void event_tagv1(SDL_Event const& event);
        void clean_up();
        void load_background();
        void handel_keyboard_events(SDL_Event const& event);
        bool is_valid_event_type(SDL_Event const& event);

        static std::string error();
        static std::string p_error();
};
} // namespace core

#endif // GC_SDL_BASICS_GAME_H
