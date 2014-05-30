/*
 * RenderObjectManager.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "RenderObjectManager.hpp"
#include "Game.hpp"

RenderObjectManager::RenderObjectManager() :
    m_renderObjects()
{
}

RenderObjectManager::~RenderObjectManager() {
}

void RenderObjectManager::updateRenderObject(const Entity& entity, const ObjectDelta& deltaType,
		RenderObject& ro)
{
	if (deltaType == ObjectDelta::REMOVED) {
		m_renderObjects.erase(entity);
	} else {
		m_renderObjects[entity] = ro;
	}
}
