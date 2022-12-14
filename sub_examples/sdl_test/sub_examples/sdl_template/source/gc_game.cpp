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
	: m_state(states::unknown)
	, m_renderer(renderer)
	, m_screen(m_renderer.screen())
	, m_background(&m_renderer)
	, m_sprite_texture(&m_renderer, util::from_res("sprites.png"))
	, m_modulated_texture(&m_renderer)
	, m_alpha_texture(&m_renderer)
	, m_sprite_sheet_texture(&m_renderer)
{
}

void gc_game::execute()
{
	SDL_Event event;
	init_tagv2();

	double degree = 0.0;
	SDL_RendererFlip flip_mode = SDL_FLIP_NONE;

	while(states::running == m_state)
	{
		SDL_WaitEvent(&event);
		check_for_exit(event);
		handel_keyboard_flip_event(event, degree, flip_mode);
		render_white_background();
		m_head.render({(def::w - m_head.get_size().width) / 2,
			       (def::h - m_head.get_size().height) / 2},
			      nullptr,
			      degree,
			      nullptr,
			      flip_mode);
		m_renderer.update();
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
	for(std::size_t i = 0; i < m_textures.size(); ++i)
	{
		m_textures[i] = gc_texture(&m_renderer);
		m_textures[i].load(m_images_path[i]);
	}

	load_background_tagv1();
	m_renderer.update();
}

void gc_game::init_tagv2()
{
	LOG_INFO << "Initializing ...";
	CHECK_FAILED(SDL_Init(SDL_INIT_EVERYTHING), "Couldn't Initialize: " + error());
	int image_flag = IMG_INIT_PNG;
	CHECK_FAILED_2(!(IMG_Init(image_flag) & image_flag), "Couldn't Initialize: " + p_error());
	LOG_INFO << "Rendering Image ...";
	m_state = states::running;
	m_head = gc_texture(&m_renderer);
	m_head.load(m_images_path[0]);
	m_renderer.update();
}

void gc_game::process_events(SDL_Event const& event)
{
	switch(event.key.keysym.sym)
	{
	case SDLK_ESCAPE:
		m_state = states::stopped;
		break;
	}
}

void gc_game::handel_keyboard_events(SDL_Event const& event)
{
	switch(event.key.keysym.sym)
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

void gc_game::handel_keyboard_color_events(SDL_Event const& event, color_t& color)
{
	if(SDL_KEYDOWN == event.type)
	{
		auto constexpr step = 32U;
		switch(event.key.keysym.sym)
		{
		case SDLK_q:
			color.red += step;
			break;
		case SDLK_a:
			color.red -= step;
			break;
		case SDLK_w:
			color.green += step;
			break;
		case SDLK_s:
			color.green -= step;
			break;
		case SDLK_e:
			color.blue += step;
			break;
		case SDLK_d:
			color.blue -= step;
			break;
		}
	}
}

void gc_game::handel_keyboard_alpha_event(SDL_Event const& event, alpha_t& alpha)
{
	if(SDL_KEYDOWN == event.type)
	{
		auto constexpr step = 32U;
		switch(event.key.keysym.sym)
		{
		case SDLK_w:
			alpha = (0xFF <= alpha + step) ? 0xFF : alpha + step;
			break;
		case SDLK_s:
			alpha = (0 >= alpha - step) ? 0 : alpha - step;
			break;
		}
	}
}

void gc_game::handel_keyboard_flip_event(SDL_Event const& event,
					 double& degree,
					 SDL_RendererFlip& flip)
{
	if(SDL_KEYDOWN == event.type)
	{
		auto constexpr degree_step = 10;
		switch(event.key.keysym.sym)
		{
		case SDLK_a:
			degree -= degree_step;
			break;
		case SDLK_d:
			degree += degree_step;
			break;
		case SDLK_w:
			flip = SDL_FLIP_NONE;
			break;
		case SDLK_s:
			flip = SDL_FLIP_VERTICAL;
			break;
		}
	}
}

bool gc_game::is_quite_event_type(SDL_Event const& event)
{
	return SDL_QUIT == event.type;
}

void gc_game::check_for_exit(SDL_Event const& event)
{
	if(SDL_KEYDOWN == event.type)
	{
		if(SDLK_ESCAPE == event.key.keysym.sym)
		{
			m_state = states::stopped;
		}
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
	m_sprite_texture.render({def::w - m_sprite_clips[1].w, 0}, &m_sprite_clips[1]);
	m_sprite_texture.render({0, def::h - m_sprite_clips[2].h}, &m_sprite_clips[2]);
	m_sprite_texture.render({def::w - m_sprite_clips[3].w, def::h - m_sprite_clips[3].h},
				&m_sprite_clips[3]);
}

void gc_game::render_white_background()
{
	SDL_SetRenderDrawColor(m_renderer.renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	m_renderer.clear();
}

void gc_game::load_alpha_texture()
{
	m_alpha_texture.load(util::from_res("alpha100.png"));
	m_alpha_texture.set_blend_mode(SDL_BLENDMODE_BLEND);
}

void gc_game::load_foo_animation()
{
	m_sprite_sheet_texture.load(util::from_res("foo.png"));
	m_animation_sprite_clips[0] = {0, 0, 64, 205};
	m_animation_sprite_clips[1] = {64, 0, 64, 205};
	m_animation_sprite_clips[2] = {128, 0, 64, 205};
	m_animation_sprite_clips[3] = {196, 0, 64, 205};
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
	if(SDL_QUIT == event.type)
	{
		m_state = states::stopped;
	}
	else if(SDL_KEYDOWN == event.type)
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
	SDL_Rect constexpr fillRect = {def::w / 4, def::h / 4, def::w / 2, def::h / 2};
	SDL_SetRenderDrawColor(m_renderer.renderer(), 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(m_renderer.renderer(), &fillRect);
	SDL_SetRenderDrawColor(m_renderer.renderer(), 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(m_renderer.renderer(), 0, def::h / 2, def::w, def::h / 2);
	SDL_SetRenderDrawColor(m_renderer.renderer(), 0xFF, 0xFF, 0x00, 0xFF);
	for(std::size_t i = 0; i < def::h; i += 4)
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
