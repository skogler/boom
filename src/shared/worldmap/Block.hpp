/*
 * Block.h
 *
 *  Created on: May 29, 2014
 *      Author: toe
 */

#ifndef BLOCK_H_
#define BLOCK_H_

typedef enum BlockType_ {
    WALL,
    FLOOR,
}BlockType;

class Block {
public:
    Block();
    virtual ~Block();
private:

    BlockType       _type;
    int             _hitPoints;
    BlockTexture    *_texture;
    int             _x;
    int             _y;
};

#endif /* BLOCK_H_ */
