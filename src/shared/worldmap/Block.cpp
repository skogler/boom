/*
 * Block.cpp
 *
 *  Created on: May 29, 2014
 *      Author: toe
 */

#include "Block.hpp"
#include "Worldmap.hpp"

Block::Block(const BlockType& type, Worldmap* map, const int& x, const int& y) : _type(type), _worldmap(map), _x(x), _y(y)
{
    // TODO Auto-generated constructor stub

}

Block::~Block()
{
    // TODO Auto-generated destructor stub
}

#define NEIGHBOR_UP     0x01
#define NEIGHBOR_DOWN   0x02
#define NEIGHBOR_LEFT   0x04
#define NEIGHBOR_RIGHT  0x08

#define NEIGHBOR_UP_LEFT     0x01
#define NEIGHBOR_UP_RIGHT     0x01
#define NEIGHBOR_DOWN_LEFT   0x02
#define NEIGHBOR_DOWN_LEFT   0x02
#define NEIGHBOR_LEFT   0x04
#define NEIGHBOR_RIGHT  0x08

void Block::checkSubType()
{
    if (_type != WALL) {
        return;
    }
    unsigned int neighbors = 0;

    if (_worldmap->getBlock(_x + 1, _y)->getType() == WALL) {
        neighbors |= NEIGHBOR_UP;
    }
    if (_worldmap->getBlock(_x - 1, _y)->getType() == WALL) {
        neighbors |= NEIGHBOR_DOWN;
    }
    if (_worldmap->getBlock(_x, _y + 1)->getType() == WALL) {
        neighbors |= NEIGHBOR_RIGHT;
    }
    if (_worldmap->getBlock(_x, _y - 1)->getType() == WALL) {
        neighbors |= NEIGHBOR_LEFT;
    }

}

