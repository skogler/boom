#ifndef INPUT_HPP_EYIAZASI
#define INPUT_HPP_EYIAZASI

#include <SDL2/SDL.h>
#include <map>
class Input 
{
    private:
        std::map<int, bool> current_keystate;
        std::map<int, bool> last_keystate;
   

    public:    
        void initialize();
        void processEvent( SDL_Event event );
        

};

#endif /* end of include guard: INPUT_HPP_EYIAZASI */

