/*
 * Worldmap.cpp
 *
 *  Created on: May 29, 2014
 *      Author: toe
 */

#include "Worldmap.hpp"
#include "simplexnoise1234.hpp"
#include "Block.hpp"
#include <algorithm>
#include <SDL2/SDL_image.h>

Worldmap::Worldmap(const int &seed, const int& size_x, const int& size_y, const int& center_area = 5):
    _size_x(size_x), _size_y(size_y), _center_area(center_area), _world()
{
    _generated = false;
    _init(size_x, size_y);
    _generate(seed, size_x, size_y);
}

Worldmap::~Worldmap()
{
    std::vector<Block*>::iterator blocks = _world.begin();
    //for (; blocks != _world.end(); blocks++) {
    //    delete *blocks;
    //}
    _world.clear();
}

bool Worldmap::isCenter(const int& x, const int& y)
{
    int center_x = _size_x / 2;
    int center_y = _size_y / 2;

    if ((x >= center_x - _center_area && x <= center_x + _center_area) &&
        (y >= center_y - _center_area && y <= center_y + _center_area)) {
        return true;
    }

    return false;
}

// return a 'random' value interpolated with its neighbours
int Worldmap::_smoothPerlin(int x, int y, float max)
{
    float corners = ( SimplexNoise1234::noise(x-1, y-1)+SimplexNoise1234::noise(x+1, y-1)+SimplexNoise1234::noise(x-1, y+1)+SimplexNoise1234::noise(x+1, y+1) ) / 16.0f;
    float sides   = ( SimplexNoise1234::noise(x-1, y)  +SimplexNoise1234::noise(x+1, y)  +SimplexNoise1234::noise(x, y-1)  +SimplexNoise1234::noise(x, y+1) ) /  8.0f;
    float center  =  SimplexNoise1234::noise(x, y) / 4.0f;

    float noise = corners + sides + center;
    return fabs((noise * (float) max));
}

void Worldmap::saveImage()
{
    SDL_Surface* surface = SDL_CreateRGBSurface(0,_size_x,_size_y,32,0,0,0,0);

    Uint32 black = SDL_MapRGB(surface->format,0, 0, 0);
    Uint32 green = SDL_MapRGB(surface->format,0, 255, 0);

    SDL_FillRect(surface, NULL, black);

    SDL_Rect pixel;
    pixel.x = 0;
    pixel.y = 0;
    pixel.w = 1;
    pixel.h = 1;

    for(int x = 0; x < _size_x; x++) {
        for (int y = 0; y < _size_y; y++) {
            if (getBlock(x, y)->getType() == Block::WALL) {
                pixel.x = x;
                pixel.y = y;
                SDL_FillRect(surface, &pixel, green);
            }
        }
    }
    SDL_SaveBMP(surface, "map.bmp");

}

void Worldmap::_createWall(const int& start_x, const int& start_y, const int& width, const int& height)
{

    int end_x = std::min(_size_x, start_x + width);
    int end_y = std::min(_size_y, start_y + height);

    for (int x_coord = start_x; x_coord < end_x; x_coord ++) {
        for (int y_coord = start_y; y_coord < end_y; y_coord ++) {
            if (isCenter(x_coord, y_coord)) {
                continue;
            }
            getBlock(x_coord, y_coord)->setType(Block::WALL);
        }
    }
}

void Worldmap::_init(const int& size_x, const int& size_y)
{
    _size_x = size_x;
    _size_y = size_y;
    _world.clear();
    _world.reserve(size_x * size_y);

    for (int x = 0; x < size_x; ++x) {
        for (int y = 0; y < size_y; ++y) {
            Block *block = new Block(Block::FLOOR, this, x, y);
            _world.push_back(block);
        }
    }
}

Block* Worldmap::getBlock(const int& x, const int& y) const
{
    int x_coord = x % _size_x;
    int y_coord = y % _size_y;
    int index = x_coord * _size_x + y_coord;
    return _world[index];
}

void Worldmap::_generate(const int &seed, const int& size_x, const int& size_y)
{
    srand(seed);

    int perlin_offset = rand() % 200;

    // the 3 layers of noise
   // CImg<unsigned char> simplexnoise1(size_x, size_y, 1, 1);

    // create starting points for the first layer of panels
    for(int x = 0; x < size_x / 2; x++) {
        for (int y = 0; y < size_y / 2; y++) {
            float smooth = _smoothPerlin(x + perlin_offset, y + perlin_offset, 255.0f);
            if (smooth < 90.0f || smooth > 120.0f) {
                continue;
            }
             int size = rand() % 10 + 1;
             int size_type = rand() % 3;
             if (size_type == 0)
                 continue;

             SDL_Rect r;
             r.x = x;
             r.y = y;

             if (size_type == 1) {
                 r.h = size;
                 r.w = 1;
             }
             else if (size_type == 2) {
                 r.h = 1;
                 r.w = size;
             }
             _createWall(r.x, r.y, r.w, r.h);
        }
    }

    for(int x = 0; x < size_x / 2; x++) {
        for (int y = 0; y < size_y / 2; y++) {
            Block::BlockType type = getBlock(x, y)->getType();
            int mirror_x = _size_x - x - 1;
            int mirror_y = _size_y - y - 1;
            getBlock(x, mirror_y)->setType(type);
            getBlock(mirror_x, y)->setType(type);
            getBlock(mirror_x, mirror_y)->setType(type);
        }
    }
    _generated = true;

}

