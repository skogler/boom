/*
 * Worldmap.cpp
 *
 *  Created on: May 29, 2014
 *      Author: toe
 */

#include "Worldmap.h"
#include "simplexnoise1234.h"
#include "CImg.h"

Worldmap::Worldmap(const int &seed, const int& size_x, const int& size_y)
{
    _generate(seed, _size_x, size_y)
}

Worldmap::~Worldmap()
{
    // TODO Auto-generated destructor stub
}

// return a 'random' color value interpolated with its neighbours
int smoothPerlin(int x, int y, int max)
{
    float corners = ( SimplexNoise1234::noise(x-1, y-1)+SimplexNoise1234::noise(x+1, y-1)+SimplexNoise1234::noise(x-1, y+1)+SimplexNoise1234::noise(x+1, y+1) ) / 16.0f;
    float sides   = ( SimplexNoise1234::noise(x-1, y)  +SimplexNoise1234::noise(x+1, y)  +SimplexNoise1234::noise(x, y-1)  +SimplexNoise1234::noise(x, y+1) ) /  8.0f;
    float center  =  SimplexNoise1234::noise(x, y) / 4.0f;

    float noise = corners + sides + center;
    return (noise * (float) max);
}

void Worldmap::_generate(const int &seed, const int& size_x, const int& size_y)
{

    // the 3 layers of noise
    CImg<unsigned char> simplexnoise1(size_x, size_y, 1, 1);

    int noise_x = 0;
    int noise_y = 0;

    // create starting points for the first layer of panels
    for(int x = 0; x < size_x; x++) {
        for (int y = 0; y < size_y; y++) {
            int smooth = smoothPerlin(x, y, 255);
            if (smooth < 60) {
                smooth = 0;
            }
            else {
                smooth = 255;
            }
            simplexnoise1.draw_point(x, y, &smooth);
        }
    }

    // save image
    simplexnoise1.save_jpeg("noise.jpg");


}

