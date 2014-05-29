#ifndef WINDOW_HPP_UGPBTZKY
#define WINDOW_HPP_UGPBTZKY

#include "common.hpp"

struct SDL_Window;

class Window
{
    DISABLECOPY(Window);
public:
    Window (uint width, uint height, bool fullscreen);
    virtual ~Window ();

    SDL_Window* m_window;
    
};

#endif /* end of include guard: WINDOW_HPP_UGPBTZKY */

