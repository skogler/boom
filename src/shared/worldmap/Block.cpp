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

