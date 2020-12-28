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

#ifndef _AABB_H_
#define _AABB_H_

#include "Vector3.h"
#include "Ray.h"
#include <limits>

class AABB
{
	Vector3 _min, _max;
public:
	AABB():_min(std::numeric_limits<Real>::infinity()), _max(-std::numeric_limits<Real>::infinity())
	{}

	AABB(const Vector3 &_minpoint, const Vector3 &_maxpoint):
		_min(_minpoint), _max(_maxpoint)
	{}
	
	void add(const Vector3 &p)
	{
		if( p[0] < _min[0])
			_min[0] = p[0];
		if( p[1] < _min[1])
			_min[1] = p[1];
		if( p[2] < _min[2])
			_min[2] = p[2];
		if( p[0] > _max[0])
			_max[0] = p[0];
		if( p[1] > _max[1])
			_max[1] = p[1];
		if( p[2] > _max[2])
			_max[2] = p[2];
	}
	void add(const AABB &bb)
	{
		if( bb._min[0] < _min[0])
			_min[0] = bb._min[0];
		if( bb._min[1] < _min[1])
			_min[1] = bb._min[1];
		if( bb._min[2] < _min[2])
			_min[2] = bb._min[2];
		if( bb._max[0] > _max[0])
			_max[0] = bb._max[0];
		if( bb._max[1] > _max[1])
			_max[1] = bb._max[1];
		if( bb._max[2] > _max[2])
			_max[2] = bb._max[2];
	}

	/*
	 * Ray-box intersection from PBRT
	 */
	bool intersect(const Ray& r, Real &t)const
	{
		Vector3 origin = r.get_origin();
		Real t0 = -std::numeric_limits<Real>::infinity(),
			t1 = std::numeric_limits<Real>::infinity();
		for (int i = 0; i < 3; ++i) {
			// Update interval for _i_th bounding box slab
			Real invRayDir = 1.f / r.get_direction()[i];
			Real tNear = (_min[i] - origin[i]) * invRayDir;
			Real tFar  = (_max[i] - origin[i]) * invRayDir;

			// Update parametric interval from slab intersection $t$s
			if (tNear > tFar) std::swap(tNear, tFar);
			t0 = tNear > t0 ? tNear : t0;
			t1 = tFar  < t1 ? tFar  : t1;
			if (t0 > t1) return false;
		}
		t = t0;
		return true;
	}

	const AABB &operator=(const AABB& bb)
	{
		_min = bb._min;
		_max = bb._max;
		return *this;
	}

	int get_max_axis()const
	{
		Vector3 size = _max-_min;
		Real max_dim = size[0];
		int dim = 0;

		if( max_dim < size[1] )
		{
			dim = 1;
			max_dim = size[1];
		}
		if( max_dim < size[2] )
		{
			dim = 2;
			max_dim = size[2];
		}
		return dim;
	}
	Vector3 get_center() const
	{
		Vector3 size = _max+_min;

		return size*.5f;
	}
};
#endif