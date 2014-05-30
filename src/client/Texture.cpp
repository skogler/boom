
#include "Texture.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Texture::Texture(SDL_Renderer* renderer, const string& absPath) : 
    m_texture(nullptr),
    m_width(0),
    m_height(0)
{
    m_surface = IMG_Load(absPath.c_str());
    if (!m_surface) {
        std::cerr << "Error loading texture " << absPath << std::endl;
        return;
    }
    m_width = m_surface->w;
    m_height = m_surface->h;

    SDL_Texture* tex  = SDL_CreateTextureFromSurface(renderer, m_surface);
   // SDL_FreeSurface(surf);
   // m_surface = nullptr;
    if (!tex) {
        std::cerr << "Error loading texture " << absPath << std::endl;
        return;
    }
    m_texture = tex;
}

Texture::Texture(SDL_Renderer* renderer, SDL_Surface* surf) :
    m_texture(nullptr),
    m_width(0),
    m_height(0),
    m_surface(surf)
{
    m_width = m_surface->w;
    m_height = m_surface->h;

    SDL_Texture* tex  = SDL_CreateTextureFromSurface(renderer, m_surface);
   // SDL_FreeSurface(surf);
    surf = nullptr;
    if (!tex) {
        std::cerr << "Error creating texture ";
        return;
    }
    m_texture = tex;
}

Texture::~Texture()
{
    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
}
