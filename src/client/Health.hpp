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
	virtual ~Health();

private:
	int m_health;
};

#endif /* HEALTH_HPP_ */
