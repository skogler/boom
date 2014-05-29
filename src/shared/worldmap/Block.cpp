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
_worldmap(map),
_x(x),
_y(y),
_neighbors(-1)
{
    // TODO Auto-generated constructor stub

}

Block::~Block()
{
    // TODO Auto-generated destructor stub
}

int Block::getTextures(std::vector<std::string>& textures)
{
    int count = textures.size();;
    if (getType() == FLOOR || getType() == BROKEN_WALL) {
        textures.push_back("resources/textures/floor/floor_steel.png");
    }
    else if (getType() == WALL) {
        textures.push_back("resources/textures/wall/32_wall_basic.png");

        if (getNeighbors() && NEIGHBOR_DOWN) {
            textures.push_back("resources/textures/wall/wall_easy/wall_S.png");
        }
        if (getNeighbors() && NEIGHBOR_UP) {
            textures.push_back("resources/textures/wall/wall_easy/wall_N.png");
        }
        if (getNeighbors() && NEIGHBOR_LEFT) {
            textures.push_back("resources/textures/wall/wall_easy/wall_W.png");
        }
        if (getNeighbors() && NEIGHBOR_RIGHT) {
            textures.push_back("resources/textures/wall/wall_easy/wall_E.png");
        }
        if (getNeighbors() && NEIGHBOR_DOWN_LEFT) {
            textures.push_back("resources/textures/wall/wall_easy/wall_SW.png");
        }
        if (getNeighbors() && NEIGHBOR_DOWN_RIGHT) {
            textures.push_back("resources/textures/wall/wall_easy/wall_SE.png");
        }
        if (getNeighbors() && NEIGHBOR_UP_RIGHT) {
            textures.push_back("resources/textures/wall/wall_easy/wall_NE.png");
        }
        if (getNeighbors() && NEIGHBOR_UP_LEFT) {
            textures.push_back("resources/textures/wall/wall_easy/wall_NW.png");
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

