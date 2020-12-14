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

#ifndef _TRANSMISSIVE_H_
#define _TRANSMISSIVE_H_

#include "globals.h"
#include "BSDF.h"
#include "Vector3.h"
#include "Intersection.h"

class Transmissive: public BSDF
{
	//Absorption coefficient
	Vector3 absorption;
	//Index of refraction
	Real refraction_index;
public:
	Transmissive(World *_w):absorption(0.f), refraction_index(1.f), BSDF(_w){}
	Transmissive(World *_w, const Vector3 &_absorption, const Real _refraction)
		:absorption(_absorption),refraction_index(_refraction),BSDF(_w){}
	Transmissive(World *_w, const Real _refraction)
		:absorption(0.f),refraction_index(_refraction),BSDF(_w){}
	Vector3 shade(const Intersection &it)const;
	void get_outgoing_sample_ray(const Intersection &it, Ray &r, Real &weight)const;
	Vector3 get_albedo(const Intersection &it) const;
	Real get_specular(const Intersection &it) const;
	bool is_delta()const;
};

#endif