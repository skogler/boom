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
	m_alpha(1)
{
}

RenderObject::RenderObject(const Entity& entity, std::string filename) :
    m_entity(entity),
	m_fileName(filename),
	m_zLevel(0),
	m_alpha(1)
{

}

RenderObject::RenderObject(const Entity& entity, std::string fileName, int zLevel, double alpha) :
        m_entity(entity),
		m_fileName(fileName),
		m_zLevel(zLevel),
		m_alpha(alpha)
{

}

RenderObject::~RenderObject() {
	// TODO Auto-generated destructor stub
}

