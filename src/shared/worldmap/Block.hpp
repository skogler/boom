/*
 * Block.h
 *
 *  Created on: May 29, 2014
 *      Author: toe
 */

#ifndef BLOCK_H_
#define BLOCK_H_

class BlockTexture;
class Worldmap;

class Block {
public:

    static const int NEIGHBOR_UP =      0x01;
    static const int NEIGHBOR_DOWN =    0x02;
    static const int NEIGHBOR_LEFT =    0x04;
    static const int NEIGHBOR_RIGHT =   0x08;

    static const int NEIGHBOR_UP_LEFT =     0x10;
    static const int NEIGHBOR_UP_RIGHT =    0x20;
    static const int NEIGHBOR_DOWN_RIGHT =  0x40;
    static const int NEIGHBOR_DOWN_LEFT =   0x80;

    typedef enum BlockType_ {
        WALL,
        FLOOR,
        NONE,
    }BlockType;

    Block(const BlockType& type, Worldmap* map, const int& x, const int& y);
    virtual ~Block();

    void setType(const BlockType& type)
    {
        _type = type;
    }
    BlockType getType() const {
        return _type;
    }

    int getNeighbors();


private:

    void _checkNeighbors();

    BlockType       _type;
    Worldmap        *_worldmap;
//    BlockTexture    *_texture;
    int             _x;
    int             _y;
    int             _neighbors;
};

#endif /* BLOCK_H_ */
