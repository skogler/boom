/*
 * RenderObject.hpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#ifndef RENDEROBJECT_HPP_
#define RENDEROBJECT_HPP_

#include <string>
#include "Entity.hpp"
#include "Position.hpp"

class RenderObject {
public:
	RenderObject(const Entity& entity);
	RenderObject(const Entity& entity, std::string filename);
    RenderObject(const Entity& entity, std::string fileName, int zLevel, double alpha);
    RenderObject(const Entity& entity, std::string fileName, int zLevel, double alpha, Coords offset, Coords size);
	virtual ~RenderObject();

    bool operator==(const RenderObject& other) {
        return m_entity.getId() == other.m_entity.getId() 
            && m_fileName == other.m_fileName
            && m_zLevel == other.m_zLevel;
    }

    bool operator<(const RenderObject& other) {
        return m_zLevel < other.m_zLevel;
    }

    Entity m_entity;
	std::string m_fileName;
	int m_zLevel;
	double m_alpha;
    Coords m_offset;
    Coords m_size;
};

#endif /* RENDEROBJECT_HPP_ */
