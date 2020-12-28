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

#ifndef __OBJECT3D_H
#define __OBJECT3D_H

#include <vector>
#include "globals.h"
#include "Matrix4x4.h"
#include "AABB.h"


class Intersection;
class BSDF;
class Ray;

//---------------------------------------------------------------------------
// class Object3D 
//
// This is the abstract ancestor of all traceable objects.
//---------------------------------------------------------------------------
class Object3D 
{
protected:
	// An object contains a surface
	BSDF* mat;
	bool is_solid;
	Vector3 speed;
public:

	Object3D(BSDF* _mat): mat(_mat), speed(0.) {}

  /** Transform an object. Objects are represented directly in world
			coordinates. This function is used to transform the objects 
			according to an arbitrary transfer matrix. */
	virtual void transform(const Matrix4x4& m) = 0;
  
	/// Intersect the object with a ray.
	virtual bool intersect(Ray& r, Intersection &it, float time = 0.) const = 0;
  
	// Return a pointer to the material of the object 
	virtual const BSDF *material()const; 

	/// Return the normal at a given point
	virtual Vector3 get_normal(const Vector3& v) const = 0;

	/// Gives the Bounding Box of the object
	virtual AABB get_bounding_box()const = 0;

	// Gives the center of the object
	virtual Vector3 get_center()const = 0;

	// Gives primitives, if exists
	virtual void push_primitives(std::vector<Object3D*> &objects);
	
	void set_speed(const Vector3 &_speed){speed = _speed;}
};


#endif





