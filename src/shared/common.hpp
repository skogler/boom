#ifndef COMMON_HPP_UVOCTULR
#define COMMON_HPP_UVOCTULR

#include <string>
using std::string;

typedef unsigned int uint;


const string GAME_NAME = "Boom!";

#define DISABLECOPY(classname)  private: \
                                 classname(const classname &rhs); \
                                 classname& operator=(const classname &rhs)

#endif /* end of include guard: COMMON_HPP_UVOCTULR */
