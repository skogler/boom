/*
 * RenderObject.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "RenderObject.hpp"
#include "Entity.hpp"

RenderObject::RenderObject(const Entity& entity) :
    m_entity(entity),
	m_fileName(""),
	m_zLevel(0),
	m_alpha(1),
    m_offset({0,0}),
    m_size({1,1}),
    m_rotation_center({0,0})
{
}

RenderObject::RenderObject(const Entity& entity, std::string filename) :
    m_entity(entity),
	m_fileName(filename),
	m_zLevel(0),
	m_alpha(1),
    m_offset({0,0}),
    m_size({1,1}),
    m_rotation_center({0,0})
{

}

RenderObject::RenderObject(const Entity& entity, std::string fileName, int zLevel, double alpha) :
        m_entity(entity),
		m_fileName(fileName),
		m_zLevel(zLevel),
		m_alpha(alpha),
        m_offset({0,0}),
        m_size({1,1}),
        m_rotation_center({0,0})
{

}
RenderObject::RenderObject(const Entity& entity, std::string fileName, int zLevel, double alpha, Coords offset, Coords size, Coords rotation_center) :
        m_entity(entity),
		m_fileName(fileName),
		m_zLevel(zLevel),
		m_alpha(alpha),
        m_offset(offset),
        m_size(size),
        m_rotation_center(rotation_center)
{

}

RenderObject::~RenderObject() {
	// TODO Auto-generated destructor stub
}

