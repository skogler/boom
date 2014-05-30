/*
 * Block.cpp
 *
 *  Created on: May 29, 2014
 *      Author: toe
 */

#include "Block.hpp"
#include "Worldmap.hpp"

Block::Block(const BlockType& type, Worldmap* map, const int& x, const int& y) :
_type(type),
_x(x),
_y(y),
_neighbors(-1)
{
    _worldmap = map;
    _neighbors = 0; // TODO
    // TODO Auto-generated constructor stub

}

Block::~Block()
{
    // TODO Auto-generated destructor stub
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
        textures.push_back("wall/wall_simple/wall_basic");

        if (getNeighbors() && NEIGHBOR_DOWN) {
            textures.push_back("wall/wall_simple/wall_S");
        }
        if (getNeighbors() && NEIGHBOR_UP) {
            textures.push_back("wall/wall_simple/wall_N");
        }
        if (getNeighbors() && NEIGHBOR_LEFT) {
            textures.push_back("wall/wall_simple/wall_W");
        }
        if (getNeighbors() && NEIGHBOR_RIGHT) {
            textures.push_back("wall/wall_simple/wall_E");
        }
        if (getNeighbors() && NEIGHBOR_DOWN_LEFT) {
            textures.push_back("wall/wall_simple/wall_SW");
        }
        if (getNeighbors() && NEIGHBOR_DOWN_RIGHT) {
            textures.push_back("wall/wall_simple/wall_SE");
        }
        if (getNeighbors() && NEIGHBOR_UP_RIGHT) {
            textures.push_back("wall/wall_simple/wall_NE");
        }
        if (getNeighbors() && NEIGHBOR_UP_LEFT) {
            textures.push_back("wall/wall_simple/wall_NW");
        }
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

    if (_worldmap->getBlock(_x + 1, _y)->getType() == WALL) {
        _neighbors |= NEIGHBOR_UP;
    }
    if (_worldmap->getBlock(_x - 1, _y)->getType() == WALL) {
        _neighbors |= NEIGHBOR_DOWN;
    }
    if (_worldmap->getBlock(_x, _y + 1)->getType() == WALL) {
        _neighbors |= NEIGHBOR_RIGHT;
    }
    if (_worldmap->getBlock(_x, _y - 1)->getType() == WALL) {
        _neighbors |= NEIGHBOR_LEFT;
    }

    if (_worldmap->getBlock(_x + 1, _y + 1)->getType() == WALL) {
        _neighbors |= NEIGHBOR_UP_RIGHT;
    }
    if (_worldmap->getBlock(_x + 1, _y - 1)->getType() == WALL) {
        _neighbors |= NEIGHBOR_UP_LEFT;
    }
    if (_worldmap->getBlock(_x - 1, _y + 1)->getType() == WALL) {
        _neighbors |= NEIGHBOR_DOWN_RIGHT;
    }
    if (_worldmap->getBlock(_x - 1, _y - 1)->getType() == WALL) {
        _neighbors |= NEIGHBOR_DOWN_LEFT;
    }
}

