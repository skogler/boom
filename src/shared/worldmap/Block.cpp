/*
 * Block.cpp
 *
 *  Created on: May 29, 2014
 *      Author: toe
 */

#include "Block.hpp"
#include "Worldmap.hpp"
#include <string.h>
#include <stdio.h>

Block::Block(const BlockType& type, Worldmap* map, const int& x, const int& y) :
_type(type),
_x(x),
_y(y),
_neighbors(-1)
{
    _worldmap = map;
    _neighbors = -1; // TODO
    // TODO Auto-generated constructor stub

}

Block::~Block()
{
    // TODO Auto-generated destructor stub
}

 void Block::getTextureNames(std::vector<std::string>& textures, int neighbors)
{
    textures.push_back("wall/wall_simple/wall_basic");

    if ((neighbors & BORDER_DOWN)) {
        textures.push_back("wall/wall_simple/wall_S");
    }
    if (neighbors & BORDER_UP) {
        textures.push_back("wall/wall_simple/wall_N");
    }
    if (neighbors & BORDER_LEFT) {
        textures.push_back("wall/wall_simple/wall_W");
    }
    if (neighbors & BORDER_RIGHT) {
        textures.push_back("wall/wall_simple/wall_E");
    }
    if (neighbors & BORDER_DOWN_LEFT) {
        textures.push_back("wall/wall_simple/wall_SW");
    }
    if (neighbors & BORDER_DOWN_RIGHT) {
        textures.push_back("wall/wall_simple/wall_SE");
    }
    if (neighbors & BORDER_UP_RIGHT) {
        textures.push_back("wall/wall_simple/wall_NE");
    }
    if (neighbors & BORDER_UP_LEFT) {
        textures.push_back("wall/wall_simple/wall_NW");
    }
}

int Block::getTextures(std::vector<std::string>& textures)
{
    if (_worldmap == NULL || _worldmap->generated() == false) {
        return 0;
    }
    int count = textures.size();;
    if (getType() == FLOOR || getType() == BROKEN_WALL) {
        textures.push_back("floor/floor_steel");
    }
    else if (getType() == WALL) {
        char name[20];
        memset(name, 0, sizeof(name));
        int neighbors = getNeighbors();
        sprintf(name, "wall/%04d", neighbors);
        textures.push_back(name);
    }
    return textures.size() - count;
}


int Block::getNeighbors()
{
    if (_neighbors < 0) {
        _checkNeighbors();
    }
    return _neighbors;
}

void Block::_checkNeighbors()
{
    if (_type != WALL) {
        return;
    }
    _neighbors = 0;

    if (_worldmap->getBlock(_x, _y + 1 )->getType() == FLOOR) {
        _neighbors |= BORDER_DOWN;
        _neighbors |= BORDER_DOWN_LEFT;
        _neighbors |= BORDER_DOWN_RIGHT;
    }
    if (_worldmap->getBlock(_x, _y - 1)->getType() == FLOOR) {
        _neighbors |= BORDER_UP;
        _neighbors |= BORDER_UP_LEFT;
        _neighbors |= BORDER_UP_RIGHT;
    }
    if (_worldmap->getBlock(_x + 1, _y)->getType() == FLOOR) {
        _neighbors |= BORDER_RIGHT;
        _neighbors |= BORDER_DOWN_RIGHT;
        _neighbors |= BORDER_UP_RIGHT;
    }
    if (_worldmap->getBlock(_x - 1, _y )->getType() == FLOOR) {
        _neighbors |= BORDER_LEFT;
        _neighbors |= BORDER_DOWN_LEFT;
        _neighbors |= BORDER_UP_LEFT;
    }
    if (_worldmap->getBlock(_x + 1, _y - 1)->getType() == FLOOR) {
        _neighbors |= BORDER_UP_RIGHT;
    }
    if (_worldmap->getBlock(_x - 1, _y - 1)->getType() == FLOOR) {
        _neighbors |= BORDER_UP_LEFT;
    }
    if (_worldmap->getBlock(_x + 1, _y + 1)->getType() == FLOOR) {
        _neighbors |= BORDER_DOWN_RIGHT;
    }
    if (_worldmap->getBlock(_x - 1, _y + 1)->getType() == FLOOR) {
        _neighbors |= BORDER_DOWN_LEFT;
    }
}

