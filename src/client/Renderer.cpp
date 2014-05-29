#include "Renderer.hpp"
#include "Window.hpp" 
#include <SDL2/SDL.h>

Renderer::Renderer(Window* window)
    : m_window(window),
    m_renderer(nullptr)
{
    m_renderer = SDL_CreateRenderer(window->m_window, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::~Renderer()
{
}
