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
#ifndef _BSDF_H_
#define _BSDF_H_

#include "globals.h"
#include "Vector3.h"

class World;
class Intersection;
class Ray;

class BSDF
{
protected:
	World *w;
public:
	BSDF(World *_w):w(_w) {}
	
	// Stochastically samples a new ray 'r' given a previous intersection 'it'. The 'pdf' 
	// value is needed to get statistically correct results, but it is not needed for 
	// specular and transparent objects (a parameter is needed, but it can just be ignored.
	virtual void get_outgoing_sample_ray(const Intersection &it, Ray &r, Real &pdf)const = 0;
	
	// Returns the albedo of the surface at intersection 'it'
	virtual Vector3 get_albedo(const Intersection &it) const = 0;
	// Returns the specular coefficient at intersection 'it'
	virtual Real get_specular(const Intersection &it) const = 0;

	virtual bool is_delta()const = 0;
};

#endif