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

#ifndef _BVH_H_
#define _BVH_H_

#include "globals.h"
#include "Object3D.h"
#include "AABB.h"
#include <vector>

using namespace std;

class BVH: public Object3D
{
	AABB bb;
	vector<Object3D*> leaves;
	BVH *child1, *child2;
	
	void get_primitives(vector<Object3D*> &objects);
	void build_bounding_box(vector<Object3D*> &objects);
	void order_objects(vector<Object3D*> &objects)const;
	void split_objects(vector<Object3D*> &objects, 
		vector<Object3D*> &obj1, vector<Object3D*> &obj2)const;
	bool intersect(Intersection &it, Ray& r) const;
public:
	BVH():Object3D(0),child1(0),child2(0){}
	BVH(vector<Object3D*> &objects);
	virtual void transform(const Matrix4x4& m){throw("No transformation here");}

	bool intersect(Ray& r, Intersection &it, float time = 0.) const;

 	Vector3 shade(const Intersection &it) const;
  
	Vector3 get_normal(const Vector3& v) const{throw("No normals here");}

	AABB get_bounding_box()const;
	Vector3 get_center() const;
};
#endif
