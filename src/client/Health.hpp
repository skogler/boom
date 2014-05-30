/*
 * Health.hpp
 *
 *  Created on: 30 May 2014
 *      Author: Marco
 */

#ifndef HEALTH_HPP_
#define HEALTH_HPP_

class Health {
public:
	Health(int health);
	Health() : m_health(0) {}
	virtual ~Health();

	int getHealth() const { return m_health; }

	const Health &operator+=(const Health &rhs) {
		m_health += rhs.getHealth();
		return *this;
	}

	Health operator+(const Health &rhs) {
		return Health(m_health + rhs.getHealth());
	}

private:
	int m_health;
};

#endif /* HEALTH_HPP_ */
