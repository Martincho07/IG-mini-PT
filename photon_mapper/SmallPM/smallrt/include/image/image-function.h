#ifndef _IMAGE_IMAGE_FUNCTION_H_
#define _IMAGE_IMAGE_FUNCTION_H_

namespace Imaging
{

class ImageFunction
{
public:
	virtual RGBColor operator()(Real x, Real y) const = 0;
};

};

#endif

