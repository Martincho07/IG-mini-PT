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

#ifndef __PLANE_H
#define __PLANE_H

#include "Vector3.h"
#include "Object3D.h"
#include "Ray.h"
#include "Intersection.h"

/** Infinite plane object. Not a solid. */
class Plane : public Object3D
{
	Vector3 pos;
	Vector3 normal;
	Real d;


public:

	Vector3 get_normal(const Vector3& surf_point) const { return normal; }

	Plane(const Vector3& _pos,
						const Vector3& _normal,
						BSDF* _mat);

	virtual void transform(const Matrix4x4& m);

	bool intersect(Ray& r, Intersection &it, float time = 0.) const;

	AABB get_bounding_box() const;
	
	Vector3 get_center() const
	{
		return pos;
	}
};
#endif
