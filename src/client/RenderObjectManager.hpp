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

//    std::vector<RenderObject*> getRenderObjectsFor(const Entity& entity)

	void updateRenderObject(const ObjectDelta& deltaType, RenderObject* ro);

    std::vector<RenderObject*> m_zSortedRenderObjects;
};

#endif /* RENDEROBJECTMANAGER_HPP_ */
