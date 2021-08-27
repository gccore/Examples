#include "gc_image.h"

#include <filesystem>

#include <SDL2/SDL.h>

#include "gc_screen.h"
#include "Logger.h"

namespace core
{
gc_image::gc_image()
        : m_screen(nullptr),
          m_surface(nullptr),
          m_image_sur(nullptr)
{
}

gc_image::gc_image(gc_screen* screen)
        : m_screen(screen),
          m_surface(SDL_GetWindowSurface(m_screen->window())),
          m_image_sur(nullptr)
{
}

gc_image::gc_image(gc_screen* screen, std::string const& path)
        : gc_image(screen)
{
        if (nullptr == m_surface) {
                LOG_FATAL << "Couldn't Create Surface";
                throw std::runtime_error("Couldn't Create Surface.");
        }
        LOG_INFO << "Surface Created.";

        set_path(path);
        load_image();
}

gc_image::~gc_image()
{
        LOG_INFO << "Free Up Surface Loaded From: " << m_path;
        deallocate();
}

gc_image& gc_image::load_image(std::string const& path)
{
        if (nullptr == m_screen) {
                LOG_ERROR << "Screen Doesn't Exist.";
                throw std::runtime_error("Screen Doesn't Exist.");
        }
        if (nullptr != m_image_sur) {
                deallocate();
                LOG_WARN << "Previously Loaded Image: " << m_path
                         << " Released.";
        }

        set_path(path);
        load();
        return *this;
}

gc_image& gc_image::load_image()
{
        load_image(m_path);
        return *this;
}

void gc_image::load()
{
        auto const image = SDL_LoadBMP(m_path.c_str());
        if (nullptr == image) {
                LOG_ERROR << "Couldn't Load BMP: " << SDL_GetError();
                throw std::runtime_error("Couldn't Load BMP: " + std::string(SDL_GetError()));
        }

        m_image_sur = SDL_ConvertSurface(image, m_surface->format, 0);
        if (nullptr == m_image_sur) {
                LOG_ERROR << "Couldn't Convert The Surface: " << SDL_GetError();
                throw std::runtime_error("Couldn't Convert The Surface: " +
                                         std::string(SDL_GetError()));
        }
        SDL_FreeSurface(image);

        LOG_INFO << "BMP: " + m_path + " Loaded";
}

void gc_image::render()
{
        if (0 != SDL_BlitSurface(m_image_sur, nullptr, m_surface, nullptr)) {
                LOG_ERROR << "Couldn't Apply Image: " << SDL_GetError();
                throw std::runtime_error("Couldn't Apply Image : "
                                         + std::string(SDL_GetError()));
        }

        LOG_INFO << "Image Applied.";
}

void gc_image::deallocate()
{
        if (nullptr != m_image_sur) {
                SDL_FreeSurface(m_image_sur);
        }
}

void gc_image::set_path(std::string const& path)
{
        if (!std::filesystem::exists(path)) {
                LOG_ERROR << "Path Not Found: " + path;
                throw std::runtime_error("Path Not Found: " + path);
        }
        m_path = path;
}
} // namespace core
