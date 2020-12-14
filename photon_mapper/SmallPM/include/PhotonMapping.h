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

#ifndef _PHOTONMAPPING_H_
#define _PHOTONMAPPING_H_

#include <time.h>

#include "globals.h"

#include "Vector3.h"
#include "KDTree.h"

class World;
class Intersection;
class Ray;

/** The PhotonMapping class is a light integrator that implements
	classic Jensen's photon mapping algorithm. Both the pre-process
	pass and the gathering pass are assumed to be iterative (as 
	oposed to the traditional recursive formulation of Whitted's 
	ray tracing. */
class PhotonMapping
{
	World *world;
	
	unsigned int m_max_nb_shots, m_nb_global_photons, m_nb_caustic_photons;
	unsigned int m_nb_current_shots;

	unsigned int m_nb_photons;
	bool m_raytraced_direct;

	// Structure defining a photon (a directionally-resolved packet of 
	// energy), that will be used later for radiance estimation.
	struct Photon
	{
		Vector3 position;
		Vector3 direction;
		Vector3 flux;

		Photon():
			position(0), direction(0), flux(0) {}
		Photon(const Vector3 &p, const Vector3 &d, const Vector3 &f):
			position(p), direction(d), flux(f) {}
	};

	KDTree<Photon, 3> m_global_map, m_caustics_map;

	// Compute the photons by tracing the Ray 'r' from the light source
	// through the scene, and by storing the intersections with matter
	// in the lists 'xx_photons', storing the diffuse (global) and caustic
	// photons respectively. For efficiency, both are computed at the same
	// time, since computing them separately would result into a lost of
	// several samples marked as caustic or diffuse.
	// Same goes with the boolean 'direct', that specifies if direct 
	// photons (from light to surface) are being stored or not. 
	// The initial traced photon has energy defined by the tristimulus
	// 'p', that accounts for the emitted power of the light source.
	// The function will return true when there are more photons (caustic
	// or diffuse) to be shot, and false otherwise.
	bool trace_ray(const Ray& r, const Vector3 &p, 
			   std::list<Photon> &global_photons, std::list<Photon> &caustic_photons, bool direct);
public:

 	PhotonMapping( World *_world, unsigned int nb_global_photons, unsigned int nb_caustic_photons,
				   unsigned int max_nb_shots, unsigned int nb_photons, bool raytraced_direct = true): 
 		world(_world), m_max_nb_shots(max_nb_shots), m_nb_current_shots(0),
		m_nb_global_photons(nb_global_photons), m_nb_caustic_photons(nb_caustic_photons),
		m_nb_photons(nb_photons), m_raytraced_direct(raytraced_direct)
	{ }
	
	// Preprocess the photon map. This needs to be run before rendering,
	// or no photons will be stored to compute radiance in the rendering
	// pass.
	void preprocess();

	// Computes shading at the intersection 'it0' and returns the estimated
	// radiance.
	Vector3 shade(Intersection &it0)const;
};

#endif