/*
 * Worldmap.h
 *
 *  Created on: May 29, 2014
 *      Author: toe
 */

#ifndef WORLDMAP_H_
#define WORLDMAP_H_

#include <vector>

class Block;

class Worldmap {
public:
    Worldmap(const int &seed, const int& size_x, const int& size_y);

    Block* getBlock(double x, double y);

    virtual ~Worldmap();
private:

    void _generate(const int &seed, const int& size_x, const int& size_y);

    std::vector< std::vector<Block*> > _world;
};

#endif /* WORLDMAP_H_ */
