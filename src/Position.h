/*
 * Position.h
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#ifndef POSITION_H_
#define POSITION_H_

class Position {
public:
	Position();
	virtual ~Position();

private:
	const int realm;
	const double x, y, z;
};

class Orientation {
public:
	Orientation();
	virtual ~Orientation();

private:
	const double angle;
};

#endif /* POSITION_H_ */
