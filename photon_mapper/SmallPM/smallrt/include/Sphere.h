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

#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Object3D.h"
#include "Ray.h"
#include "Intersection.h"
/** The notion of a sphere should be familiar. A sphere is a solid, hence
		may transmit light. */
class Sphere : public Object3D
{
	Vector3 position;
	Real radius;
  
public:
	
	Vector3 get_normal(const Vector3& surf_point) const;
	
	void transform(const Matrix4x4&);
		
	Sphere(const Vector3& pos, const Real rad, BSDF* _mat)
		: Object3D(_mat), position(pos), radius(rad) 
	{
		is_solid = true;
	}
  
	virtual bool intersect(Ray& r, Intersection &it, float time = 0.) const;

	AABB get_bounding_box()const;

	Vector3 get_center()const
	{
		return position;
	}
};      
#endif
