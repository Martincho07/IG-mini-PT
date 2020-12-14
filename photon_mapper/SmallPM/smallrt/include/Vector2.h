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

#ifndef HOST_VECTOR2_H
#define HOST_VECTOR2_H

#include "globals.h"

class Vector2
{
public:
	Vector2(const Real f= 0.f);
	Vector2(const Real x, const Real y);
	
	Vector2 operator+(const Vector2& v) const;
	Vector2 operator-(const Vector2& v) const;
	Vector2 operator*(const Real f) const;
	Vector2 operator+=(const Vector2& v);
	Vector2 operator-=(const Vector2& v);
	Vector2 operator*=(const Real f);

	Real getComponent(const int dimension) const;
	Real operator[](const int dimension) const;
	Real &operator[](const int dimension);
private:
	Real data[2];
};

#endif
