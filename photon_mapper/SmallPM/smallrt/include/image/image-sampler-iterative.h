#ifndef _IMAGE_IMAGE_SAMPLER_ITERATIVE_H_
#define _IMAGE_IMAGE_SAMPLER_ITERATIVE_H_

#include "image-sampler.h"

namespace Imaging
{

class ImageSamplerIterative : public ImageSampler
{
	Real min, max;
public:
	ImageSamplerIterative(Real _min = -1.0, Real _max = 1.0): min(_min), max(_max) { }	

	template<typename F>
	void sample(Image& image, const F& f) const
	{
		int i,j; Real x,y;
		for (j=0, y=0.0+min*((Real)image.height()/(Real)image.width());j<image.height();j++,y+=(max-min)/(Real)image.width())
			for (i=0, x=min;i<image.width();i++,x+=(max-min)/(Real)image.width())
				image.set(i,j,f(x,y));
	}

	void _sample(Image& image, const ImageFunction& image_function) const { sample(image,image_function); }
};

};

#endif
