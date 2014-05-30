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
    m_renderer = SDL_CreateRenderer(window->m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
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
    
    m_textures[name] = std::unique_ptr<Texture>(tex);
}

void Renderer::updateViewports() 
{
    int players = m_game->getNumberOfPlayers();
    auto w_size = m_window->getSize();

    m_viewports.clear();
    m_viewports.reserve(players+1);
    int w = w_size.first / 2;
    int h = players <= 2 ? w_size.second : w_size.second / 2;
    
    m_viewports.push_back(SDL_Rect{0,0,w_size.first,w_size.second});
    m_viewports.push_back(SDL_Rect{0,0,w,h});
    m_viewports.push_back(SDL_Rect{w,0,w,h});
    if (players > 2) {
        m_viewports.push_back(SDL_Rect{0,h,w,h});
        m_viewports.push_back(SDL_Rect{w,h,w,h});
    }
    m_cameras.clear();
    m_cameras.resize(players + 1);
    m_cameras[0] = std::make_pair<Coords,Coords>(Coords{0,0},Coords{0,0});
    for (int i = 1; i < players; ++i) {
        const auto& player = m_game->getPlayerByID(i);
        m_cameras[i] = std::make_pair<Coords, Coords>(m_game->getPlayerPosition(player), Coords{w/32., h/32.});
    }
}

void Renderer::updateCameras()
{
    for (uint i = 1; i < m_cameras.size(); ++i) {
        const auto& player = m_game->getPlayerByID(i-1);
        m_cameras[i].first = m_game->getPlayerPosition(player);
        m_cameras[i].first.x -= m_cameras[i].second.x/2;
        m_cameras[i].first.y -= m_cameras[i].second.y/2;
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
            auto& tex = m_textures.at(renderObject->m_fileName);
            auto pos = state.getPositionManager().getPosition(renderObject->m_entity);
            auto rot = state.getPositionManager().getOrientation(renderObject->m_entity);
            int realm = pos.getRealm();
            const SDL_Rect& viewport = m_viewports[realm + 1];

            SDL_RenderSetViewport(m_renderer, &viewport);
            auto& cam = m_cameras[realm + 1];

            SDL_Rect target;
            target.w = SCALE * ( renderObject->m_size.x);
            target.h = SCALE * ( renderObject->m_size.y);
            target.x = SCALE * (-cam.first.x + pos.getCoords().x + renderObject->m_offset.x); 
            target.y = SCALE * (-cam.first.y + pos.getCoords().y + renderObject->m_offset.y);

            SDL_RenderCopyEx(m_renderer, tex->m_texture, nullptr, &target, rot.getAngleDegrees(), nullptr, SDL_FLIP_NONE);
        }
        catch (const std::runtime_error& ex)
        {
            std::cout << "Invalid texture name: " << renderObject->m_fileName << std::endl;
        }
    }
}

void Renderer::setGame(Game* game)
{
    m_game = game;
}

