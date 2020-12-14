#ifndef _IMAGE_IMAGE_SAMPLER_H_
#define _IMAGE_IMAGE_SAMPLER_H_

#include "image.h"
#include "image-function.h"

namespace Imaging
{

class ImageSampler
{
public:
	
	virtual void _sample(Image& image, const ImageFunction& image_function) const = 0;

	template<typename F>
	void sample(Image& image,const F& f) const { return this->_sample(image,f); }

	virtual void update() {}; 
};

};

#endif
