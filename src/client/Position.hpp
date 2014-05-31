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
#include <assert.h>
#ifndef M_PI
#define M_PI 3.1415926
#endif

typedef struct {
	double x;
	double y;
} Coords;

Coords normalizeCoords(const Coords &coords);

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
		m_coords(Coords{x, y}),
		m_absolute(false)
		{
		}
	virtual ~Position();

	Position(int realm, double x, double y, bool absolute) :
		m_realm(realm),
		m_coords(Coords{x, y}),
		m_absolute(absolute)
		{
		}
	Coords getCoords() const { return m_coords; }
	int getRealm() const { return m_realm; }

	double distance(const Position &other) const
	{
		return (sqrt(pow(getCoords().x - other.getCoords().x, 2)) + pow(getCoords().y - other.getCoords().y, 2));
	}

	Position operator+(const Position &other) const
	{
//		if (m_realm != other.m_realm)
		return Position(m_realm,
				getCoords().x + other.getCoords().x,
				getCoords().y + other.getCoords().y);
	}

	const Position &operator+=(const Position &other)
    {
		m_coords.x += other.getCoords().x;
		m_coords.y += other.getCoords().y;
		return *this;
    }

	const Position &operator+=(const Coords &other)
	{
		m_coords.x += other.x;
		m_coords.y += other.y;
        

		return *this;
	}

	Position& operator=(const Coords &other)
	{
        m_coords = other;
        return *this;
	}

	bool isAbsolute() const {
	    return m_absolute;
	}

private:
	int m_realm;
	Coords m_coords;
	bool    m_absolute;
};

class Orientation {
public:
	Orientation();
	Orientation(double angle) : m_angle(angle) {}
	virtual ~Orientation();

	double getAngle() const { return m_angle; }
	double getAngleDegrees() const { return m_angle * 180 / M_PI; }

	const Orientation &operator+=(const Orientation &other)
    {
		m_angle += other.getAngle();
        if (m_angle > 2*M_PI) {
            m_angle -= 2*M_PI;
        }
        else if (m_angle < -2*M_PI) {
            m_angle += 2*M_PI;
        }
		return *this;
    }


private:
	double m_angle;
};

#endif /* POSITION_H_ */
