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

#ifndef _INTERSECTION_H
#define _INTERSECTION_H

#include "globals.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Ray.h"
#include "Object3D.h"
	

/** The Intersection class is used store the data of the intersection. */
class Intersection
{		
	/// has the ray hit something ?!
	bool hit; 

	//The ray traced when found the intersection
	Ray ray;

	/// the object that has been hit
	const Object3D* obj;           

	//The position at the surface hit
	Vector3 position;

	//The normal at the surface hit
	Vector3 normal;

	//The uv-coordinates at the surface hit
	Vector2 uv;
public:
	Intersection();

	Intersection(const Ray &r, const Object3D* _obj, const Vector3 &_n, const Vector2 &_uv);

	/// Get intersection position.
	const Vector3 get_position() const;
	
	/// Get intersection normal.
	const Vector3 get_normal() const;
	
	/// Get intersection uv coordinates.
	const Vector2 get_uv() const;

	/// Get ray
	const Ray get_ray() const;

	/// Returns true if ray has hit an object.
	bool did_hit() const;

	/// If ray has hit, return intersected object.
	const Object3D* intersected() const;

	const Intersection &operator=(const Intersection &it);
};

#endif










