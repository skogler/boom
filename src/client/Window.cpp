#include "Window.hpp"
#include <SDL2/SDL.h>

Window::Window (uint width, uint height, bool fullscreen)
    : m_window(nullptr)
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
            SDL_WINDOW_OPENGL);
}

Window::~Window()
{
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
}
