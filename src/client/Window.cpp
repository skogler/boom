#include "Window.hpp"
#include <SDL2/SDL.h>
#include <assert.h>

Window::Window (int width, int height, bool fullscreen) : 
    m_window(nullptr),
    m_width(width),
    m_height(height)
{
    SDL_Init(SDL_INIT_VIDEO);
    int flags = SDL_WINDOW_OPENGL;

    if (fullscreen) {
        width = 0;
        height = 0;
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    m_window = SDL_CreateWindow(GAME_NAME.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            flags);

    assert(m_window);

    SDL_GetWindowSize(m_window, &m_width, &m_height);
}

Window::~Window()
{
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
}

std::pair<int, int> Window::getSize()
{
    return std::pair<int, int>(m_width, m_height);
}
