#ifndef TEXTURE_HPP_Q8F5AM9K
#define TEXTURE_HPP_Q8F5AM9K

#include "common.hpp"

struct SDL_Texture;
struct SDL_Renderer;

class Texture
{
    DISABLECOPY(Texture);
public:
    Texture (SDL_Renderer* renderer, const string& absPath);
    virtual ~Texture ();

    SDL_Texture* m_texture;
    int m_width;
    int m_height;
};

#endif /* end of include guard: TEXTURE_HPP_Q8F5AM9K */

