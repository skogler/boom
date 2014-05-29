/*
 * Position.h
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#ifndef POSITION_H_
#define POSITION_H_

#include <vector>
#include <cmath>

typedef struct {
	double x;
	double y;
} Coords;

class BoundingBox {
private:
	std::vector<Coords> m_polygon;

public:
	BoundingBox() : m_polygon() {}
	BoundingBox(Coords topLeft, Coords bottomRight) :
		m_polygon()
	{
		m_polygon.push_back(Coords{topLeft.x, topLeft.y});
		m_polygon.push_back(Coords{bottomRight.x, topLeft.y});
		m_polygon.push_back(Coords{bottomRight.x, bottomRight.y});
		m_polygon.push_back(Coords{topLeft.x, bottomRight.y});
	}

	BoundingBox rotate(Coords origin, double angle);
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

	Position operator+=(const Coords &other) const
	{
		return Position(m_realm,
				getCoords().x + other.x,
				getCoords().y + other.y);
	}

	Position operator=(const Coords &other) const
	{
		return Position(m_realm,
				other.x, other.y);
	}

private:
	const int m_realm;
	const Coords m_coords;
};

class Orientation {
public:
	Orientation();
	Orientation(double angle) : m_angle(angle) {}
	virtual ~Orientation();

	Orientation operator=(const Orientation &other) const
	{
		return Orientation(other.getAngle());
	}

	double getAngle() const { return m_angle; }

	Orientation operator+=(const Orientation &other) const
    {
		return Orientation(getAngle() + other.getAngle());
    }


private:
	const double m_angle;
};

#endif /* POSITION_H_ */
