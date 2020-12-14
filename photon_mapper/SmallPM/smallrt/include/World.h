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

#ifndef __WORLD_H
#define __WORLD_H

#include <list>
#include <vector>
#include <assert.h>
#include "globals.h"
#include "Object3D.h"
#include "Mesh.h"
#include "LightSource.h"
#include "globals.h"
typedef std::vector<Object3D*>::iterator    Object3DPtrIterator;
typedef std::vector<LightSource*>::iterator LightSourcePtrIterator;

/** class World. World contains global information about the scene.
		In particular World contains a list of lights and objects. However, World 
		also contains other information and function that can be used to trace
		a ray into the World (and get a colour back). World also contains functions
		useful for photon mapped caustics. */
class World
{
	/// List of all objects in our world
	std::vector<Object3D*>    object_list;

	/// Ambient colour
	Vector3 ambient;

	/** Background colour used to shade rays that miss all objects and 
			continue into the void. */
	Vector3 background;
	bool fixed;
public:
	World();

	/// List of all lightsources in world
	std::vector<LightSource*> light_source_list;

	/// Set & get ambient level
	void set_ambient(const Vector3& amb);
	Vector3 get_ambient();

	/// Set & get background color.
	void set_background(const Vector3 bkg);
	Vector3 get_background();

	/// Add a light source to our World
	void add_light(LightSource* ls);
	const LightSource &light(const int idx)const;
	int nb_lights()const;

	/// Add an object to our world
	void add_object(Object3D* o3d);
	void add_objects(std::vector<Object3D*> &o3ds);

	/// Fix all the primitives in the scene, and makes all needed actions before
	//	rendering
	void fix();

	/// Return the object that first intersects `ray'
	Real first_intersection(Ray& ray, Intersection &it);

};
#endif




