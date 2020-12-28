/*********************************************************************************
Copyright (C) 2014 Adrian Jarabo (ajarabo@unizar.es)
Copyright (C) 2014 Diego Gutierrez (diegog@unizar.es)
All rights reserved.

This is an educational Ray Tracer developed for the course 'Informatica Grafica'
(Computer Graphics) tought at Universidad de Zaragoza (Spain). As such, it does not 
intend to be fast or general, but just to provide an educational tool for undergraduate
students. 

This software is provided as is, and any express or implied warranties are disclaimed.
In no event shall copyright holders be liable for any damage.
**********************************************************************************/

#ifndef HOST_MATRIX4X4_H
#define HOST_MATRIX4X4_H

#include "Vector3.h"
#include "globals.h"

class Matrix4x4
{
public:
	Matrix4x4();
	
	void setColumn(const int index, const Vector3& v);
	bool invert(void);
	void print(void);

public:
	Real m_data[4][4];
};

#endif
