/*
 * RenderObject.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "RenderObject.hpp"

RenderObject::RenderObject(std::string filename) :
	m_fileName(filename),
	m_zLevel(0),
	m_alpha(1)
{

}

RenderObject::RenderObject(std::string fileName, int zLevel, double alpha) :
		m_fileName(fileName),
		m_zLevel(0),
		m_alpha(1)
{

}

RenderObject::~RenderObject() {
	// TODO Auto-generated destructor stub
}

