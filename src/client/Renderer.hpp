#ifndef RENDERER_HPP_Y3A02IJX
#define RENDERER_HPP_Y3A02IJX

#include "common.hpp"
#include <SDL2/SDL.h>

class Window;
struct SDL_Renderer;

class Renderer
{
    DISABLECOPY(Renderer);

public:
    Renderer (Window* window);
    virtual ~Renderer ();

    inline void startFrame();
    inline void endFrame();

private:
    Window* m_window;
    SDL_Renderer* m_renderer;
    
};

void Renderer::startFrame()
{
    SDL_RenderClear(m_renderer);
}
void Renderer::endFrame()
{
    SDL_RenderPresent(m_renderer);
}

#endif /* end of include guard: RENDERER_HPP_Y3A02IJX */

