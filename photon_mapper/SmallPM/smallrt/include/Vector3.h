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

#ifndef Vector3_H
#define Vector3_H

#include "globals.h"

class Vector3
{
public:
	Vector3(const Real f= 0.f);
	Vector3(const Real x, const Real y, const Real z);
	
	Vector3 operator-()const;
	Vector3 operator+(const Vector3& v) const;
	Vector3 operator-(const Vector3& v) const;
	Vector3 operator*(const Real f) const;
	Vector3 operator/(const Real f) const;
	Vector3 operator*(const Vector3& v) const;
	Vector3 operator/(const Vector3& v) const;
	Vector3 operator+=(const Vector3& v);
	Vector3 operator-=(const Vector3& v);
	Vector3 operator*=(const Real f);
	Vector3 normalize(void);
	Vector3 cross(const Vector3 &v) const;
	Real dot(const Vector3 &v) const;
	Real dot_abs(const Vector3 &v) const;
	Real length() const;
	Real length2() const;
	Real avg() const;
	Real getComponent(const int dimension) const;
	Real operator[](const int dimension) const;
	Real &operator[](const int dimension);
	bool isZero(void) const;
	//Function that returns the reflected direction, depending on normal
	Vector3 reflect(const Vector3 &normal)const;
	//Function that returns the reflected direction, depending on normal and refractive_index
	Vector3 refract(const Vector3 &normal, Real refractive_index)const;
	Vector3 transform_matrix_to(const Vector3& from, const Vector3& to)const;
public:
	Real data[3];
};

Real dot(const Vector3 &v1, const Vector3 &v2);
Real dot_abs(const Vector3 &v1, const Vector3 &v2);
Vector3 cross(const Vector3 &v1, const Vector3 &v2);
Vector3 operator*(const Real f, const Vector3 &v);
Vector3 normalize(const Vector3 &v);

#endif
