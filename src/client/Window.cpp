#include "Window.hpp"
#include <SDL2/SDL.h>
#include "common.hpp"

Window::Window()
    : m_window(nullptr)
{
    SDL_Init(SDL_INIT_VIDEO);
    m_window = SDL_CreateWindow(GAME_NAME.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            640, 480,
            SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);

}

Window::~Window()
{
}
