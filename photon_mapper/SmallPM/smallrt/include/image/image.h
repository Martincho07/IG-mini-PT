#ifndef _IMAGE_IMAGE_H_
#define _IMAGE_IMAGE_H_

#ifndef cimg_display
#define cimg_display 0
#endif

#include <algorithm>
#include <ctype.h>
#include <cmath>
#include <math.h>

#include "mlaa-wrapper.h"
#define cimg_plugin "cimg-additions.h"
#define cimg_plugin1 "cimg-mlaa.h"
#define cimg_plugin2 "cimg-tmo.h"

#include "CImg.h"
using namespace cimg_library;

#ifndef Real
	#define Real double
#endif

#include <vector>

using namespace std;

#ifndef IGNORE_RGBCOLOR
	#include "rgbcolor.h"
#endif

namespace Imaging
{

class Image : public CImg<Real>
{
public:
	Image() : CImg<Real>(1,1,1,3) {}
	Image(int _w, int _h) : CImg<Real>(_w, _h, 1, 3) {}
	Image(const CImg<Real>& img) : CImg<Real>(img) {}
	~Image() { }
	Real operator()(int x, int y, int c) const { return this->atXYZC(x,y,0,c,0.0); }
	Real& operator()(int x, int y, int c) { return this->atXYZC(x,y,0,c); }
#ifndef IGNORE_RGBCOLOR
	RGBColor operator()(int x, int y) const { return RGBColor((*this)(x,y,0),(*this)(x,y,1),(*this)(x,y,2)); }
	RGBColor cubic(Real x, Real y) const { return RGBColor(this->cubic_atXY(x,y,0,0),this->cubic_atXY(x,y,0,1),this->cubic_atXY(x,y,0,2)); }
	RGBColor linear(Real x, Real y) const { return RGBColor(this->linear_atXY(x,y,0,0),this->linear_atXY(x,y,0,1),this->linear_atXY(x,y,0,2)); }
	void set(int x, int y,const RGBColor& color) { for (int i=0;i<3;i++) (*this)(x,y,i)=color[i]; }
#endif

	Image(const char* filename) : CImg<Real>() { this->load(filename);}
};

typedef CImgList<Real> ImageList;

class ImageVector
{
	vector<Image*> data;
public:
	ImageVector(unsigned int n) : data(n)
	{
		vector<Image*>::iterator i;
		for (i=data.begin();i!=data.end();i++)
		{	(*i)=new Image(); }
	}

	~ImageVector()
	{
		vector<Image*>::iterator i;
		for (i=data.begin();i!=data.end();i++)
		{	delete (*i); }
	}

	Image& operator[](unsigned int i) { return *(data[i]); }
	const Image& operator[](unsigned int i) const { return *(data[i]); }
};

};

//This stuff down is needed when compiling with python
#ifdef HAVE_PROTOTYPES
	#undef HAVE_PROTOTYPES
#endif
#ifdef _POSIX_C_SOURCE
	#undef _POSIX_C_SOURCE
#endif
#ifdef _XOPEN_SOURCE
	#undef _XOPEN_SOURCE
#endif


#endif

