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

#ifndef _RENDERENGINE__H
#define _RENDERENGINE__H

#include <time.h>

#include "globals.h"

#include "Vector3.h"
#include "Film.h"
#include "World.h"
#include "Camera.h"
#include "PhotonMapping.h"

/** The RenderEngine Contains the main loop of the program.
		RenderEngine ties together the World (containing all objects and lights),
		the camera and the film (unto which pixels are drawn). */
class RenderEngine
{
	/// World (containing all objects and lights),
	World *world;
	
	/// Film (unto which pixels are drawn).
	Film* film;

	/// Viewing information.
	Camera* camera;

	// Photon Mapping Integrator
	PhotonMapping *photon_mapping;

	/// Trace a single ray
	const Vector3 trace_ray(const Vector2& pi);
		
public:

	/** Build engine from world information, a Film and a camera. */
 	RenderEngine(World*  _world, Film* _film, Camera* _camera, PhotonMapping *_pm): 
 		world(_world), film(_film), camera(_camera), photon_mapping(_pm)
	{
		srand((unsigned)time(0));	
	}
	
	void render(const std::string& name);

};

#endif

