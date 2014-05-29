/*
 * CollisionSystem.hpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

class QuadTree;

class CollisionSystem {
public:
	CollisionSystem();
	virtual ~CollisionSystem();

	void checkCollisions(std::vector<Entity> entities);

private:
	QuadTree *qt;
};

#endif /* COLLISIONSYSTEM_HPP_ */
