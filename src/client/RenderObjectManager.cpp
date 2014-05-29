/*
 * RenderObjectManager.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "RenderObjectManager.hpp"
#include "Game.hpp"

RenderObjectManager::RenderObjectManager() {
	// TODO Auto-generated constructor stub

}

RenderObjectManager::~RenderObjectManager() {
	// TODO Auto-generated destructor stub
}

void RenderObjectManager::updateRenderObject(Entity entity, ObjectDelta deltaType,
		RenderObject ro)
{
	if (deltaType == OBJECT_REMOVED) {
		m_renderObjects.erase(entity);
	} else
	{
		m_renderObjects[entity] = ro;
	}
}
