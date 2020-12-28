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

#ifndef _MESH_H_
#define _MESH_H_

#include "Object3D.h"
#include "Triangle.h"
#include "Matrix4x4.h"
#include <vector>
#include <string>

class BSDF;

class Mesh: public Object3D
{
	std::vector<Triangle> triangles;
	AABB bb;
public:
 
	Mesh(const std::vector<Triangle> &_triangles, BSDF *_m);
	Mesh(const std::string &name_file, BSDF *_m);

	virtual void transform(const Matrix4x4& m);

	/// Intersect the object with a ray.
	bool intersect(Ray& r, Intersection &it, float time = 0.) const;

  
	Vector3 get_normal(const Vector3& v) const;

	AABB get_bounding_box()const;

	Vector3 get_center()const;

	void push_primitives(std::vector<Object3D*> &objects);
	
	//Loads the mesh from an obj file
	void load(const std::string &name_file );
};
#endif