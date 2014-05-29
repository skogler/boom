/*
 * RenderObject.hpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#ifndef RENDEROBJECT_HPP_
#define RENDEROBJECT_HPP_

#include <string>

class RenderObject {
public:
	RenderObject();
	RenderObject(std::string filename);
    RenderObject(std::string fileName, int zLevel, double alpha);
	virtual ~RenderObject();

private:
	std::string m_fileName;
	int m_zLevel;
	double m_alpha;
};

#endif /* RENDEROBJECT_HPP_ */
