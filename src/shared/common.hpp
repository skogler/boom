#ifndef COMMON_HPP_UVOCTULR
#define COMMON_HPP_UVOCTULR

#include <string>
using std::string;

typedef unsigned int uint;


typedef enum
{
       IDLE,
       MOVE_RIGHT,
       MOVE_LEFT,
       MOVE_TOP,
       MOVE_DOWN,
       SHOOT,
       TURN
}UserActionType;

const string GAME_NAME = "Boom!";

#define DISABLECOPY(classname)  private: \
                                 classname(const classname &rhs); \
                                 classname& operator=(const classname &rhs)
#define UNUSED(var) (void) (var);

#endif /* end of include guard: COMMON_HPP_UVOCTULR */
