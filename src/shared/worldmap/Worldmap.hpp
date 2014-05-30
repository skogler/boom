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
    Worldmap(const int &seed, const int& size_x, const int& size_y, const int& center_area);

    Block* getBlock(const int& x, const int& y) const;
    void saveImage();

    bool isCenter(const int& x, const int& y);

    bool generated() {
        return _generated;
    }
    virtual ~Worldmap();

    int _size_x;
    int _size_y;
private:

    void _generate(const int &seed, const int& size_x, const int& size_y);
    void _createWall(const int& start_x, const int& start_y, const int& size_x, const int& size_y);
    void _init(const int& size_x, const int& size_y);
    int  _smoothPerlin(int x, int y, float max);

    int _center_area;
    std::vector<Block* > _world;
    bool _generated;
};

#endif /* WORLDMAP_H_ */
