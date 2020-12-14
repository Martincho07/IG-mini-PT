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

#ifndef _RAY_H
#define _RAY_H

#include <float.h>
#include "globals.h"
#include "Vector3.h"

class Object3D;
	
/** This is a constant used to dismiss intersections very close to previous
		intersections. */
const Real SMALLEST_DIST = 1e-6;

/// This is the refraction index of air. 
const Real DEFAULT_REFRACTION_INDEX = 1.0;


/** The Ray class is used to find intersections between a ray and the scene,
		but it also stores information. For instance the Ray remembers intersection
		points, and the refraction index of material it is passing through. */
class Ray
{		
	/// Origin of the ray
	Vector3 origin;

	/// The normalized direction of the ray
	Vector3 direction;

	/// The parameter -i.e. the distance we have traversed along the ray
	Real t;                             

	/// Level is the number of times the ray has been traced recursively.
	int level;

	/// has the ray hit something ?!
	bool hit;  
public:
  
	
	// Construct a ray. First argument is position. Second argument
	// is the direction of the ray. The magnitude of the second argument
	// is construed as the step length.
	Ray(const Vector3& p, const Vector3& d, int _level=0);
    Ray();

	// Get ray position.
	const Vector3 get_position() const;

	// Get ray origin.
	const Vector3& get_origin() const;
  
	// Get ray parameter.
	Real get_parameter() const;

	// Get direction of ray.
	const Vector3& get_direction() const;

	// Conditional set parameter. Set parameter only if it corresponds
	// to a closer hit point than stored parameter. Set the associated
	// object.
	bool cond_set_parameter(const Real par);
	bool did_hit() const;

	int get_level() const;

	const Ray &operator=(const Ray &r);
	void shift(const Real d=1.e-4);
};

#endif










