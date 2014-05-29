/*
 * RenderObjectManager.hpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#ifndef RENDEROBJECTMANAGER_HPP_
#define RENDEROBJECTMANAGER_HPP_

#include <map>
#include "RenderObject.hpp"
#include "Entity.hpp"
#include "Game.hpp"

class RenderObjectManager {
public:
	RenderObjectManager();
	virtual ~RenderObjectManager();

	void updateRenderObject(Entity entity, ObjectDelta deltaType,
			RenderObject ro);

	std::map<Entity, RenderObject> m_renderObjects;
};

#endif /* RENDEROBJECTMANAGER_HPP_ */
