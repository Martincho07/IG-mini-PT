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

#ifndef __LIGHTSOURCE_H
#define __LIGHTSOURCE_H

#include <vector>
#include "globals.h"
#include "Vector3.h"

class Object3D;
class World;
 
/** The LightSample class contains very basic information about a light source
		that has been hit by a shadow ray - i.e. is not occluded. 
		Basically just the direction to the light source, the distance and 
		the amount of light. */
struct LightSample 
{
	Vector3 dir;
	Real dist;
	Vector3 irradiance;
};


/** The abstract LightSource is the ancestor of all other light source classes. */
class LightSource 
{
protected:
	World* world;
	Vector3 intensities;
public:

	LightSource(World* _world, const Vector3& _intensities)
		:world(_world), intensities(_intensities) {}
		 
	/// Return the position of the light source
	virtual Vector3 get_position() const = 0;
	// Return the incoming direction from light to point
	virtual Vector3 get_incoming_direction(const Vector3 &point_lighted) const = 0;
	// Return if the light is visible from the point
	virtual bool is_visible(const Vector3 &point_lighted) const = 0;
	// Return the total light incoming the point from the light source
	virtual Vector3 get_incoming_light(const Vector3 &point_lighted) const = 0;

	/** Get the intensity of the light source. This is really the total emitted
			power - so one should be careful to divide by the number of samples in
			case of area lights */
	Vector3 get_intensities() const {return intensities;}
	
	/** Number of samples to cast from a given point towards the light source. */
	virtual int get_no_samples() const {return 1;}
};


/** PointLightSource class represents a single point sending light equally
		in all directions. */
class PointLightSource : public LightSource
{
	Vector3 position;

public:

	PointLightSource(World* _world,
									 const Vector3& pos,
									 const Vector3& ints): 
		LightSource(_world,ints),	position(pos) {}
  
	Vector3 get_position() const;
	//-----------------------------------------------------------------
	Vector3 get_incoming_direction(const Vector3 &point_lighted) const;
	Vector3 get_incoming_light(const Vector3 &point_lighted) const;
	//-------------------------------------------------------------------
	bool is_visible(const Vector3 &point_lighted) const;

	bool is_point_source() const {return true;}
};

#endif 


