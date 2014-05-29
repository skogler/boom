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
	Position(int realm, double x, double y) :
		m_realm(realm),
		m_coords(Coords{x, y})
		{
		}
	virtual ~Position();

	Position operator=(const Position &other) const
	{
		return Position(m_realm,
				other.getCoords().x,
				other.getCoords().y);
	}

	Coords getCoords() const { return m_coords; }

	Position operator+(const Position &other) const
	{
//		if (m_realm != other.m_realm)
		return Position(m_realm,
				getCoords().x + other.getCoords().x,
				getCoords().y + other.getCoords().y);
	}

	Position operator+=(const Position &other) const
    {
		return Position(m_realm,
				getCoords().x + other.getCoords().x,
				getCoords().y + other.getCoords().y);
    }

private:
	const int m_realm;
	const Coords m_coords;
};

class Orientation {
public:
	Orientation();
	virtual ~Orientation();

private:
	const double angle;
};

#endif /* POSITION_H_ */
