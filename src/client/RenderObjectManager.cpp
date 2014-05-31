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
    m_zSortedRenderObjects(),
    m_render_objects()
{
}

RenderObjectManager::~RenderObjectManager() {
    for (auto ro : m_zSortedRenderObjects)
    {
        delete ro;
    }
}


void RenderObjectManager::removeEntity(Entity entity)
{
    for (std::vector<RenderObject*>::iterator iter = m_zSortedRenderObjects.begin();
            iter != m_zSortedRenderObjects.end(); ++iter) {
         if ((*iter)->m_entity == entity)
         {
             m_zSortedRenderObjects.erase(iter);
             m_render_objects.erase(entity);
             return;
         }
    }
}

void RenderObjectManager::updateRenderObject(const ObjectDelta& deltaType, RenderObject* ro)
{
	if (deltaType == ObjectDelta::REMOVED) {
        auto iter = std::find(m_zSortedRenderObjects.begin(), m_zSortedRenderObjects.end(), ro);
        if (iter != m_zSortedRenderObjects.end()) {
            m_zSortedRenderObjects.erase(iter);
        }
	} else {
        RenderObject* existing = m_render_objects[ro->m_entity];
        if (existing) {
            *existing = *ro;
            delete ro;
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
}
