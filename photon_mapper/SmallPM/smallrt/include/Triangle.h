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

#ifndef __TINT_TRIANGLE_H
#define __TINT_TRIANGLE_H

#include "globals.h"
#include "Vector3.h"
#include "Object3D.h"
#include "Ray.h"
#include "Intersection.h"

/** The triangle class represents triangles. */
class Triangle : public Object3D
{
	Vector3 v0,v1,v2;
	Vector3 n0,n1,n2;
	bool smooth;
	Vector3 normal;
public:

	Triangle(const Vector3& _v0, const Vector3& _v1, 
		 const Vector3& _v2, BSDF* _mat)
		: Object3D(_mat), v0(_v0), v1(_v1), v2(_v2), 
		normal(normalize(cross(v1-v0,v2-v0))),smooth(false)
	{
		is_solid = false;
	}
	Triangle(const Vector3& _v0, const Vector3& _n0, 
			 const Vector3& _v1, const Vector3& _n1, 
			 const Vector3& _v2, const Vector3& _n2, 
			 BSDF* _mat)
		: Object3D(_mat), v0(_v0), v1(_v1), v2(_v2)
		, n0(_n0), n1(_n1), n2(_n2), smooth(true)
	{
		is_solid = false;
	}
	void transform(const Matrix4x4& m);
		
	bool intersect(Ray& r, Intersection &it, float time = 0.) const;

	Vector3 get_normal(const Vector3& v) const
	{
		return normal;
	}

	AABB get_bounding_box()const;

	Vector3 get_center() const;
};
#endif
