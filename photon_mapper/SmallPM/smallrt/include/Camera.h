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

#ifndef __CAMERA_H
#define __CAMERA_H

#include "globals.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Ray.h"
/** This class represents a pinhole camera.*/
class Camera
{
protected:
  /// Position of camera
  Vector3 camera_position;
  /// Point we look at
  Vector3 focus_point;  
  /// Direction of up
  Vector3 up;  
  /// Direction in which we look
  Vector3 line_of_sight;

  /// Basis of camera coordinate system
  Vector3 nv,uv,vv;

  /// Distance from camera to focal plane
  Real focal_dist;    

public:

	/** Build the camera from viewing information.
			c is that camera position, f is the point we look at,
			u is the up vector and fd is the distance to the image
			plane. */
	Camera(const Vector3& c, const Vector3& f, 
				 const Vector3& u, const Real fd);

	/// Get direction of viewing ray from image coords.
	virtual const Vector3 get_ray_direction(const Vector2& p) const;

	/// Returns position of camera.
	virtual const Vector3& get_position() const;
	
	/// Calculates the ray
	virtual Ray get_ray(const Vector2& p) const;
};

#endif
