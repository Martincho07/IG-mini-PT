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

#ifndef __FILM_H
#define __FILM_H

#include "globals.h"
#include "Vector2.h"
#include "Vector3.h"

namespace Imaging
{
	class Image;
}

// A rasterized simple Film in HDR
class Film
{
  /// Actual Bitmap containing image
  Real *image;

  /// Width and height of Film
  int width, height;

  /// Half width and height of Film.
  Real xw2,yw2;

  Real _min, _max;

  //Extremely simple tonemapper... almost embarrasing
  void tonemap(); 
  void fix(Imaging::Image &out_image);

public:
	// Constructs a Film with specified dimensions
	Film(int w, int h);
	~Film();

	// Returns width of Film
	int get_width() const;

	// Returns height of Film
	int get_height() const;
  
	// 2D transform from window coordinates to image coordinates.
	// Image coordinates are in the [-1,1]x[-1,1] range 
	const Vector2 window_coords2image_coords(const Vector2& p);
       
	// Draw a pixel to the Film.
	void draw_pixel(int x, int y, const Vector3& cv);

	// Store the image into an HDR
	void write(const char* name);
};
#endif


