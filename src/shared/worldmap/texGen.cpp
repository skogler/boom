//============================================================================
// Name        : texGen.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "simplexnoise1234.h"
#include "CImg.h"
using namespace cimg_library;




// return a 'random' color value > threshhold, or 0
int threshhold_perlin(int x, int y, int max, int thresh)
{
	float noise = SimplexNoise1234::noise(x, y);
	int result = noise * (float)max;
	if (result > thresh) {
		return 0;
	}
	else {
		return max;
	}
}

// draw a small rectangle contour with a small 'handle'
void draw_rectangle_contour(CImg<unsigned char>& image, int x0, int y0, int x1, int y1, unsigned char* color)
{
	int width = x1 - x0;
	int height = y1 - y0;

	image.draw_line(x0, y0, x0+width, y0, color);

	image.draw_line(x0, y0, x0, y0+height, color);

	image.draw_line(x0+width, y0, x0+width, y0+height, color);

	image.draw_line(x0, y0+height, x0+width, y0+height, color);

	int lever_x0 = x0 + width/2;
	int lever_y0 = y1 - height/3;

	image.draw_line(lever_x0, lever_y0, lever_x0, lever_y0 + (height/4)-1, color);

}


