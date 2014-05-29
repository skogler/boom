#ifndef RENDERER_HPP_Y3A02IJX
#define RENDERER_HPP_Y3A02IJX

#include "common.hpp"
#include <SDL2/SDL.h>
#include <unordered_map>
#include <boost/filesystem.hpp>

class Window;
struct SDL_Renderer;

class Renderer
{
    DISABLECOPY(Renderer);

public:
    Renderer (Window* window);
    virtual ~Renderer ();

    inline void startFrame();
    void renderScene();
    inline void endFrame();

    SDL_Renderer* m_renderer;

private:
    void loadAllTextures();
    void loadTexture(const string& name);

    Window* m_window;
    std::unordered_map<string, SDL_Texture*> m_textures;
    boost::filesystem::path m_texture_dir;
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

