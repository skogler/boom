/*
 * Position.h
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#ifndef POSITION_H_
#define POSITION_H_

#include <vector>

typedef struct {
	double x;
	double y;
} Coords;

class BoundingBox {
private:
	std::vector<Coords> polygon;

public:
	BoundingBox(Coords topLeft, Coords bottomLeft);
};

class Position {
public:
	Position();
	virtual ~Position();

private:
	const int realm;
	const Coords coords;
};

class Orientation {
public:
	Orientation();
	virtual ~Orientation();

private:
	const double angle;
};

#endif /* POSITION_H_ */
