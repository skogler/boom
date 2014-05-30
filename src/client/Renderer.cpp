#include "Renderer.hpp"

#include "Window.hpp" 
#include "Game.hpp"
#include "RenderObjectManager.hpp"
#include "PositionManager.hpp"
#include "Texture.hpp"
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <unordered_map>

using std::unordered_map;
using std::vector;
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
    if(m_renderer)
        SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
}

void Renderer::loadAllTextures()
{
    if (!fs::exists(m_texture_dir) || ! fs::is_directory(m_texture_dir)) {
        throw std::runtime_error("Invalid texture directory");
    }
    for (auto iter = fs::recursive_directory_iterator(m_texture_dir); 
            iter != fs::recursive_directory_iterator(); iter++) {
        if (!fs::is_directory(iter->path())) {
            loadTexture(iter->path());
        }
    }
}

void Renderer::loadTexture(const fs::path& path)
{
    string basepath = m_texture_dir.string().c_str();
    string name = path.parent_path().string().c_str();
    name.erase(0, basepath.length());
    if (name.size() != 0) 
    {
        if (name[0] == '/')
            name.erase(0, 1);
        if (name[name.size()-1] != '/')
            name.append("/");
    }
    name.append(path.stem().string().c_str());

    Texture* tex = new Texture(m_renderer, path.string().c_str());;
    
    std::cout << "Loaded texture " << name << std::endl;
    m_textures[name] = std::unique_ptr<Texture>(tex);
}

void Renderer::updateViewports() 
{
    int players = m_game->getNumberOfPlayers();
    std::pair<uint, uint> w_size = m_window->getSize();

    m_viewports.clear();
    m_viewports.reserve(players);
    int w = static_cast<int>(w_size.second / 2);
    int h = static_cast<int>(players <= 2 ? w_size.first : w_size.first / 2);
    
    m_viewports.push_back(SDL_Rect{0,0,w,h});
    m_viewports.push_back(SDL_Rect{w,0,w,h});
    if (players > 2) {
        m_viewports.push_back(SDL_Rect{0,h,w,h});
        m_viewports.push_back(SDL_Rect{w,h,w,h});
    }
}

void Renderer::renderScene()
{
    SDL_RenderSetViewport(m_renderer, nullptr);
    SDL_RenderCopy(m_renderer, m_textures.at("foo")->m_texture, nullptr, nullptr);

    const GameState& state = m_game->getCurrentGameState();
    for(auto& renderObject : state.getRenderObjectManager().m_zSortedRenderObjects)
    {
        try 
        {
            auto& tex = m_textures.at(renderObject.m_fileName);
            auto pos = state.getPositionManager().getPosition(renderObject.m_entity);
            int realm = pos.getRealm();
            std::cout << realm << std::endl;
            if (realm >= 0)
                SDL_RenderSetViewport(m_renderer, &m_viewports[realm]);
            else
                SDL_RenderSetViewport(m_renderer, nullptr);
            SDL_Rect target;
            target.x = pos.getCoords().x + renderObject.m_offset.x;
            target.y = pos.getCoords().y + renderObject.m_offset.y;
            target.w = tex->m_width;
            target.h = tex->m_height;
            SDL_RenderCopy(m_renderer, tex->m_texture, nullptr, &target);
        }
        catch (const std::runtime_error& ex)
        {
            std::cout << "Invalid texture name: " << renderObject.m_fileName << std::endl;
        }
    }
}

void Renderer::setGame(Game* game)
{
    m_game = game;
}

