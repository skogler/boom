/*
 * RenderObjectManager.hpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#ifndef RENDEROBJECTMANAGER_HPP_
#define RENDEROBJECTMANAGER_HPP_

class RenderObjectManager {
public:
	RenderObjectManager();
	virtual ~RenderObjectManager();

	void updateRenderObject(Entity entity, ObjectDelta deltaType,
			RenderObject ro)
	{
		if (deltaType == OBJECT_REMOVED) {
			delete m_renderObjects[entity];
		} else
		{
			m_renderObjects[entity] = ro;
		}
	}

	std::map<Entity, RenderObject> m_renderObjects;
};

#endif /* RENDEROBJECTMANAGER_HPP_ */
