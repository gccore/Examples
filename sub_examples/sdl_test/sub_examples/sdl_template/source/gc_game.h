#ifndef GC_SDL_BASICS_GAME_H
#define GC_SDL_BASICS_GAME_H

#include <array>

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
        template <std::size_t Length>
        using gc_image_list = std::array<gc_image, Length>;

        static inline constexpr
        std::array<char const*, keys_length> m_images_path = {
                PROJECT_BINARY_PATH "/res/up.bmp",
                PROJECT_BINARY_PATH "/res/down.bmp",
                PROJECT_BINARY_PATH "/res/left.bmp",
                PROJECT_BINARY_PATH "/res/right.bmp",
        };

private:
        states m_state;
        gc_renderer& m_renderer;
        gc_screen& m_screen;
        gc_image m_background;
        gc_image_list<keys_length> m_images;

public:
        gc_game(gc_renderer& renderer);
        void execute();

private:
        void init();
        void event(SDL_Event const& event);
        void render();
        void clean_up();
        void load_background();
        void colorize_background();
        void handel_keyboard_events(SDL_Event const& event);

        static std::string error();
};
} // namespace core

#endif // GC_SDL_BASICS_GAME_H
