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
	  m_background(&m_renderer),
	  m_sprite_texture(&m_renderer, util::from_res("sprites.png"))
{
}

void gc_game::execute()
{
	init_tagv1();
	SDL_Event event;
	load_back_sprite();
	while (states::running == m_state)
	{
		SDL_WaitEvent(&event);
		if (is_valid_event_type(event))
		{
			handel_keyboard_events(event);
		}
		render_white_background();
		render_sprites();
		m_renderer.update();
#if 0
		load_background_tagv1();
		SDL_WaitEvent(&event);
		check_for_exit(event);
		if (is_valid_event_type(event))
		{
			handel_keyboard_events(event);
			m_renderer.update();
		}
#endif
	}
	clean_up();
}

void gc_game::init()
{
	CHECK_WARNING(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"),
		      "Linear Texture Filtering Not Enabled.");
	CHECK_WARNING(0 != SDL_SetRenderDrawColor(m_renderer.renderer(), 0xFF, 0xFF, 0xFF, 0xFF),
		      "Couldn't Set Render Draw Color: " + error());
	load_background();
	m_renderer.clear();
	m_state = states::running;
	m_background.load(util::from_res("background.bmp"));
}

void gc_game::init_tagv1()
{
	LOG_INFO << "Initializing ...";
	CHECK_FAILED(SDL_Init(SDL_INIT_EVERYTHING), "Couldn't Initialize: " + error());
	int image_flag = IMG_INIT_PNG;
	CHECK_FAILED_2(!(IMG_Init(image_flag) & image_flag), "Couldn't Initialize: " + p_error());
	LOG_INFO << "Rendering Images ... ";
	m_state = states::running;
	for (std::size_t i = 0; i < m_textures.size(); ++i)
	{
		m_textures[i] = gc_texture(&m_renderer);
		m_textures[i].load(m_images_path[i]);
	}

	load_background_tagv1();
	m_renderer.update();
}

void gc_game::process_events(SDL_Event const& event)
{
	switch (event.key.keysym.sym)
	{
		case SDLK_ESCAPE:
			m_state = states::stopped;
			break;
	}
}

void gc_game::handel_keyboard_events(SDL_Event const& event)
{
	switch (event.key.keysym.sym)
	{
		case SDLK_w:
			m_head_pos.y -= 10;
			m_textures[keys::up].render(m_head_pos);
			break;
		case SDLK_a:
			m_head_pos.x -= 10;
			m_textures[keys::left].render(m_head_pos);
			break;
		case SDLK_s:
			m_head_pos.y += 10;
			m_textures[keys::down].render(m_head_pos);
			break;
		case SDLK_d:
			m_head_pos.x += 10;
			m_textures[keys::rigth].render(m_head_pos);
			break;
		case SDLK_q:
			m_head_pos.y = def::h / 2;
			m_head_pos.x = def::w / 2;
			break;
		case SDLK_ESCAPE:
			m_state = states::stopped;
			break;
		default:
			m_background.render();
			break;
	}
}

bool gc_game::is_quite_event_type(SDL_Event const& event)
{
	return SDL_QUIT == event.type;
}

void gc_game::check_for_exit(SDL_Event const& event)
{
	if (is_quite_event_type(event))
	{
		m_state = states::stopped;
	}
}

bool gc_game::is_valid_event_type(SDL_Event const& event)
{
	return SDL_KEYDOWN == event.type;
}

void gc_game::load_back_sprite()
{
	m_sprite_clips[0] = {0, 0, 100, 100};
	m_sprite_clips[1] = {100, 0, 100, 100};
	m_sprite_clips[2] = {0, 100, 100, 100};
	m_sprite_clips[3] = {100, 100, 100, 100};
}

void gc_game::render_sprites()
{
	m_sprite_texture.render({0, 0}, &m_sprite_clips[0]);
	m_sprite_texture.render({static_cast<int>(def::w - m_sprite_clips[1].w), 0},
				&m_sprite_clips[1]);
	m_sprite_texture.render({0, static_cast<int>(def::h - m_sprite_clips[2].h)},
				&m_sprite_clips[2]);
	m_sprite_texture.render({static_cast<int>(def::w - m_sprite_clips[3].w),
				 static_cast<int>(def::h - m_sprite_clips[3].h)},
				&m_sprite_clips[3]);
}

void gc_game::render_white_background()
{
	SDL_SetRenderDrawColor(m_renderer.renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	m_renderer.clear();
}

std::string gc_game::error()
{
	return SDL_GetError();
}

std::string gc_game::p_error()
{
	return IMG_GetError();
}

void gc_game::event_tagv1(SDL_Event const& event)
{
	if (SDL_QUIT == event.type)
	{
		m_state = states::stopped;
	}
	else if (SDL_KEYDOWN == event.type)
	{
		handel_keyboard_events(event);
	}
}

void gc_game::clean_up()
{
	IMG_Quit();
	SDL_Quit();
}

void gc_game::render_rectangle()
{
	SDL_Rect constexpr fillRect = { def::w / 4, def::h / 4, def::w / 2, def::h / 2 };
	SDL_SetRenderDrawColor(m_renderer.renderer(), 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(m_renderer.renderer(), &fillRect);
	SDL_SetRenderDrawColor(m_renderer.renderer(), 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(m_renderer.renderer(), 0, def::h / 2, def::w, def::h / 2);
	SDL_SetRenderDrawColor(m_renderer.renderer(), 0xFF, 0xFF, 0x00, 0xFF);
	for (std::size_t i = 0; i < def::h; i += 4)
	{
		SDL_RenderDrawPoint(m_renderer.renderer(), def::w / 2, i);
	}
}

void gc_game::render_viewport()
{
	SDL_Rect constexpr topleft = {0, def::h / 2, def::w, def::h / 2};
	SDL_RenderSetViewport(m_renderer.renderer(), &topleft);
	m_background.render();
}

void gc_game::load_background()
{
	SDL_SetRenderDrawColor(m_renderer.renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
}

void gc_game::load_background_tagv1()
{
	m_background.load(util::from_res("background.bmp")).render();
}
} // namespace core
