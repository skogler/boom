#ifndef TEXTURE_HPP_Q8F5AM9K
#define TEXTURE_HPP_Q8F5AM9K

#include "common.hpp"

struct SDL_Texture;
struct SDL_Surface;
struct SDL_Renderer;

class Texture
{
    DISABLECOPY(Texture);
public:
    Texture (SDL_Renderer* renderer, const string& absPath);
    Texture(SDL_Renderer* renderer, SDL_Surface* surf);
    virtual ~Texture ();

    SDL_Texture* m_texture;
    SDL_Surface* m_surface;
    int m_width;
    int m_height;
};

#endif /* end of include guard: TEXTURE_HPP_Q8F5AM9K */

