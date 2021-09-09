#include "gc_image.h"

#include <filesystem>
#include <array>

#include "gc_screen.h"
#include "gc_defs.h"
#include "Logger.h"

namespace core
{
gc_image::gc_image()
	: m_screen(nullptr)
	, m_surface(nullptr)
	, m_image_sur(nullptr)
{
}

gc_image::gc_image(gc_screen* screen)
	: m_screen(screen)
	, m_surface(SDL_GetWindowSurface(m_screen->window()))
	, m_image_sur(nullptr)
{
}

gc_image::gc_image(gc_screen* screen, std::string const& path)
	: gc_image(screen)
{
	CHECK_NULL(m_surface, "Couldn't Create Surface");
	set_path(path);
	load();
}

gc_image::~gc_image()
{
	LOG_INFO << "Free Up Surface Loaded From: " << m_path;
	deallocate();
}

void gc_image::deallocate_previous_image()
{
	if(nullptr != m_image_sur)
	{
		deallocate();
		LOG_WARN << "Previously Loaded Image: " << m_path << " Released.";
	}
}

gc_image& gc_image::load()
{
	load(m_path);
	return *this;
}

gc_image& gc_image::load(std::string const& path)
{
	CHECK_NULL(m_screen, "Screen Doesn't Exist.");
	deallocate_previous_image();
	set_path(path);
	load_by_prefix();

	return *this;
}

void gc_image::load_by_prefix()
{
	auto const prefix = std::filesystem::path(m_path).extension();
	if(".bmp" == prefix)
	{
		convert_surface(load_bmp());
	}
	else if(".png" == prefix)
	{
		convert_surface(load_png());
	}
	else
	{
		ERROR("Unknown Prefx: " + prefix.string());
	}
}

image_ptr_t gc_image::load_bmp()
{
	image_ptr_t image(SDL_LoadBMP(m_path.c_str()));
	CHECK_NULL(image, "Couldn't Load BMP: " + error());
	return image;
}

image_ptr_t gc_image::load_png()
{
	image_ptr_t image(IMG_Load(m_path.c_str()));
	CHECK_NULL(image, "Couldn't Load PNG: " + p_error());
	return image;
}

void gc_image::convert_surface(image_ptr_t&& image)
{
	m_image_sur = SDL_ConvertSurface(image.get(), m_surface->format, 0);
	CHECK_NULL(m_image_sur, "The Surface Convert Failed: " + error());
	LOG_INFO << "Image Loaded: " << m_path;
}

std::string gc_image::error()
{
	return SDL_GetError();
}

std::string gc_image::p_error()
{
	return IMG_GetError();
}

void gc_image::render()
{
	CHECK_FAILED(SDL_BlitSurface(m_image_sur, nullptr, m_surface, nullptr),
		     "Couldn't Apply Image: " + error());
	LOG_INFO << "Image Applied.";
}

void gc_image::render(int const width, int const heigth)
{
	SDL_Rect stretch_rect = {0, 0, width, heigth};
	CHECK_FAILED(SDL_BlitScaled(m_image_sur, nullptr, m_surface, &stretch_rect),
		     "Couldn't Apply Scaled Image: " + error());

	LOG_INFO << "Scaled Image Applied.";
}

void gc_image::deallocate()
{
	if(nullptr != m_image_sur)
	{
		SDL_FreeSurface(m_image_sur);
	}
}

void gc_image::set_path(std::string const& path)
{
	CHECK_PATH_EXIST(path);
	m_path = path;
}
} // namespace core
