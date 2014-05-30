/*
 * Position.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "Position.hpp"

Coords normalizeCoords(const Coords &coords)
{
	double length = sqrt(coords.x*coords.x + coords.y*coords.y);
	if (length > 0.0005)
		return Coords{coords.x/length, coords.y/length};
	else
		return Coords{0, 0};
}

Position::Position() : m_realm(-1), m_coords(Coords{0,0}) {
	// TODO Auto-generated constructor stub

}

Position::~Position() {
	// TODO Auto-generated destructor stub
}

Orientation::Orientation() : m_angle(0) {
	// TODO Auto-generated constructor stub

}

Orientation::~Orientation() {
	// TODO Auto-generated destructor stub
}
