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

private:

    BlockType       _type;
    int             _hitPoints;
    Worldmap        *_worldmap;
//    BlockTexture    *_texture;
    int             _x;
    int             _y;
};

#endif /* BLOCK_H_ */
