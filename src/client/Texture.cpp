
#include "Texture.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Texture::Texture(SDL_Renderer* renderer, const string& absPath) : 
    m_texture(nullptr),
    m_width(0),
    m_height(0)
{
    SDL_Surface* surf = IMG_Load(absPath.c_str());
    if (!surf) {
        std::cerr << "Error loading texture " << absPath << std::endl;
        return;
    }
    m_width = surf->w;
    m_height = surf->h;

    SDL_Texture* tex  = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    surf = nullptr;
    if (!tex) {
        std::cerr << "Error loading texture " << absPath << std::endl;
        return;
    }
    m_texture = tex;
}

Texture::~Texture()
{
    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
}
