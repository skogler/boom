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
    DISABLECOPY(RenderObjectManager);
public:
	RenderObjectManager();
	virtual ~RenderObjectManager();

	void updateRenderObject(const ObjectDelta& deltaType, RenderObject* ro);
    void removeEntity(Entity entity);

    std::vector<RenderObject*> m_zSortedRenderObjects;
    std::unordered_map<Entity, RenderObject*, hash_Entity> m_render_objects;
};

#endif /* RENDEROBJECTMANAGER_HPP_ */
