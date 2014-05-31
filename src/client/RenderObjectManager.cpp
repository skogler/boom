/*
 * RenderObjectManager.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "RenderObjectManager.hpp"
#include "Game.hpp"
#include <algorithm>

RenderObjectManager::RenderObjectManager() :
    m_zSortedRenderObjects()
{
}

RenderObjectManager::~RenderObjectManager() {
    for (auto ro : m_zSortedRenderObjects)
    {
        delete ro;
    }
}

//std::vector<RenderObject*> RenderObjectManager::getRenderObjectsFor(const Entity& entity)
//{
//}

void RenderObjectManager::updateRenderObject(const ObjectDelta& deltaType, RenderObject* ro)
{
	if (deltaType == ObjectDelta::REMOVED) {
        auto iter = std::lower_bound(m_zSortedRenderObjects.begin(), m_zSortedRenderObjects.end(), ro);
        if (iter != m_zSortedRenderObjects.end() && **iter == *ro) {
            m_zSortedRenderObjects.erase(iter);
        }
	} else {
        auto iter = std::lower_bound(m_zSortedRenderObjects.begin(), m_zSortedRenderObjects.end(), ro);
        if (iter != m_zSortedRenderObjects.end()) {
            if(**iter == *ro) {
                *iter = (ro);
            } else {
                m_zSortedRenderObjects.insert(iter, ro);
            }
        }
        else {
            m_zSortedRenderObjects.push_back(ro);
        }
    }
}
