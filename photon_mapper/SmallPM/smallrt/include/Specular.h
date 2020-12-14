/*********************************************************************************
Copyright (C) 2014 Adrian Jarabo (ajarabo@unizar.es)
Copyright (C) 2014 Diego Gutierrez (diegog@unizar.es)
All rights reserved.

This is an educational Ray Tracer developed for the course 'Informatica Grafica'
(Computer Graphics) tought at Universidad de Zaragoza (Spain). As such, it does not 
intend to be fast or general, but just to provide an educational tool for undergraduate
students. 
**********************************************************************************/

#ifndef _SPECULAR_H_
#define _SPECULAR_H_

#include "BSDF.h"
#include "Vector3.h"
#include "Intersection.h"

class Specular: public BSDF
{
	//Absorption coefficient
	Vector3 absorption;
public:
	Specular(World *_w):absorption(0.f),BSDF(_w){}
	Specular(World *_w, const Vector3 &_absorption):absorption(_absorption),BSDF(_w){}
	void get_outgoing_sample_ray(const Intersection &it, Ray &r, Real &weight)const;
	Vector3 get_albedo(const Intersection &it) const;
	Real get_specular(const Intersection &it) const;

	bool is_delta()const;
};

#endif