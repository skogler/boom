#include "Renderer.hpp"

#include "Window.hpp" 
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <iostream>

using std::unordered_map;
namespace fs=boost::filesystem;

Renderer::Renderer(Window* window)
    : m_renderer(nullptr),
      m_window(window),
      m_textures(),
      m_texture_dir(fs::path("resources")/"textures")
{
    m_renderer = SDL_CreateRenderer(window->m_window, -1, SDL_RENDERER_ACCELERATED);
    loadAllTextures();
}

Renderer::~Renderer()
{
    for (auto& entry : m_textures) {
        if (entry.second) {
            SDL_DestroyTexture(entry.second);
            entry.second = nullptr;
        }
    }
    if(m_renderer)
        SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
}

void Renderer::loadAllTextures()
{
    if (!fs::exists(m_texture_dir) || ! fs::is_directory(m_texture_dir)) {
        throw std::runtime_error("Invalid texture directory");
    }
    for (auto iter = fs::directory_iterator(m_texture_dir); 
            iter != fs::directory_iterator(); iter++) {
        loadTexture(iter->path().filename().c_str());
    }
}

void Renderer::loadTexture(const string& name)
{
    SDL_Surface* surf = IMG_Load((m_texture_dir / name).c_str());
    if (!surf) {
        std::cerr << "Error loading texture " << m_texture_dir / name << std::endl;
        return;
    }
    SDL_Texture* tex  = SDL_CreateTextureFromSurface(m_renderer, surf);
    SDL_FreeSurface(surf);
    surf = nullptr;
    if (!tex) {
        std::cerr << "Error loading texture " << m_texture_dir / name << std::endl;
        return;
    }
    m_textures[name] = tex;
}

void Renderer::renderScene()
{
    //SDL_Rect viewport;
    //viewport.x=200;
    //viewport.y=200;
    //viewport.w=900;
    //viewport.h=400;
    //SDL_RenderSetViewport(m_renderer, &viewport);
    //SDL_RenderCopy(m_renderer, m_textures["foo.png"], nullptr, nullptr);
}
