#include "gc_image.h"

#include <filesystem>

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

gc_image::gc_image(gc_screen* screen, std::string const& path, loads_mod const mode)
        : gc_image(screen)
{
        if (nullptr == m_surface) {
                LOG_FATAL << "Couldn't Create Surface";
                throw std::runtime_error("Couldn't Create Surface.");
        }
        LOG_INFO << "Surface Created.";

        m_path = path;
        if (loads_mod::immediate == mode) {
                load_image(path);
        }
}

gc_image::~gc_image()
{
        SDL_FreeSurface(m_image_sur);
        LOG_INFO << "Free Up Surface Loaded From: " << m_path;
}

void gc_image::load_image(std::string const& path)
{
        if (nullptr != m_image_sur) {
                SDL_FreeSurface(m_image_sur);
                LOG_WARN << "Previously Loaded Image: " << m_path
                         << " Removed.";
        }
        if (nullptr == m_screen) {
                LOG_ERROR << "Screen Doesn't Exist.";
                throw std::runtime_error("Screen Doesn't Exist.");
        }

        m_path = path;
        if (!std::filesystem::exists(m_path)) {
                LOG_ERROR << "Path Not Found: " + m_path;
                throw std::runtime_error("Path Not Found: " + m_path);
        }

        m_image_sur = SDL_LoadBMP(m_path.c_str());
        if (nullptr == m_image_sur) {
                LOG_ERROR << "Couldn't Load BMP: " << SDL_GetError();
                throw std::runtime_error("Couldn't Load BMP: " + std::string(SDL_GetError()));
        }
        LOG_INFO << "BMP: " + m_path + " Loaded";

        SDL_BlitSurface(m_image_sur, nullptr, m_surface, nullptr);
        LOG_INFO << "Image Applied.";
}

void gc_image::load_image()
{
        load_image(m_path);
}
} // namespace core
