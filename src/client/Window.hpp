#ifndef WINDOW_HPP_UGPBTZKY
#define WINDOW_HPP_UGPBTZKY

#include "common.hpp"

struct SDL_Window;

class Window
{
    DISABLECOPY(Window);
public:
    Window (int width, int height, bool fullscreen);
    virtual ~Window ();

    std::pair<int, int> getSize();

    SDL_Window* m_window;
private:
    int m_width;
    int m_height;
};

#endif /* end of include guard: WINDOW_HPP_UGPBTZKY */

