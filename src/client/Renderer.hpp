#ifndef RENDERER_HPP_Y3A02IJX
#define RENDERER_HPP_Y3A02IJX

#include "common.hpp"
#include "Position.hpp"
#include <boost/filesystem.hpp>
#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>
#include <memory>
using std::unique_ptr;

class Window;
class Game;
class Texture;
struct SDL_Renderer;

class Renderer
{
    DISABLECOPY(Renderer);

public:
    Renderer (Window* window);
    virtual ~Renderer ();

    inline void startFrame();
    void renderScene();
    void updateCameras();
    inline void endFrame();
    void setGame(Game* game);
    void updateViewports();
    Coords screenToRealm(int x, int y, int realm) const;
    Coords realmToScreen(double x, double y, int realm) const;
    int screenCoordsIsRealm(int x, int y) const;
    void createBackground(int x_size, int y_size);

    static const int SCALE = 32;

private:
    void loadAllTextures();
    void loadTexture(const boost::filesystem::path& path);
    void createWallTextures();

    SDL_Renderer* m_renderer;
    Window* m_window;
    std::unordered_map<string, unique_ptr<Texture>> m_textures;
    boost::filesystem::path m_texture_dir;
    Game* m_game;
    std::vector<SDL_Rect> m_viewports;
    std::vector<std::pair<Coords, Coords>> m_cameras;
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

