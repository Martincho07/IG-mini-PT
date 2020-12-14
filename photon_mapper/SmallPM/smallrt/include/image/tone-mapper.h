#ifndef _IMAGING_TONE_MAPPER_H_
#define _IMAGING_TONE_MAPPER_H_

#undef max
#undef min

#include "image.h"
#include "rgbcolor.h"

namespace Imaging
{

class ToneMapper
{
public:
	virtual RGBColor tonemap_pixel(int x, int y, const RGBColor& in) const = 0;
	virtual void tonemap(const Image& in, Image& out) const
	{
		out.resize(in.width(),in.height());
		//This can be parallelized
		for (int y=0;y<in.height();y++) for (int x=0;x<in.width();x++)
			out.set(x,y,tonemap_pixel(x,y,in(x,y)));
	}
};

class ToneMapperSigmoidal : public ToneMapper
{
	Real log_average;
	Real Lwhite;
	Real invLwhite2;
	Real a;
	Real factor;

public:
	Real get_log_average() const { return log_average; }
	Real get_Lwhite() const { return Lwhite; }
	Real get_a() const { return a; }
	Real get_factor() const { return factor; }

	ToneMapperSigmoidal(Real _log_average = 0.15, Real _Lwhite = 1.0, Real _a = 0.18, Real _factor=1.0) : 
			log_average(_log_average), Lwhite(_Lwhite), invLwhite2(1.0 / (_Lwhite*_Lwhite)), a(_a), factor(_factor)
	{	}
	
	ToneMapperSigmoidal(const Image& ref, Real _Lwhite = -1.0, Real _a = 0.18, Real _factor=1.0, bool count_zeroes=true) : a(_a), factor(_factor)
	{
		log_average=0.0;
		Real max_L=0.0;
		int n = 0; //We will get just the non-black pixels
		//This can be parallelized
		for (int y=0;y<ref.height();y++)
			for (int x=0;x<ref.width();x++)
			{
				Real lum=_factor*(0.27*ref(x,y,0) + 0.67*ref(x,y,1) + 0.06*ref(x,y,2));
				if (lum>0.0) { log_average+=log(1.0 + lum); n++; }
				else if (count_zeroes) { n++; }
				max_L=std::max(max_L,lum);
			}
		log_average /= (Real)(n);
		Lwhite = (_Lwhite <= 0.0)?max_L:_Lwhite;
		invLwhite2 = 1.0 / (Lwhite*Lwhite);
	}

	RGBColor tonemap_pixel(int x, int y, const RGBColor& in) const
	{
		Real lum=factor*(0.27*in.r() + 0.67*in.g() + 0.06*in.b());
		Real L=(a/log_average)*lum;
		Real Ld = (L*(1+L*invLwhite2))/(1+L);
		return (255.0*
			RGBColor(std::max((Real)0.0,std::min(factor*(Ld/lum)*in.r(),(Real)1.0)),
				std::max((Real)0.0,std::min(factor*(Ld/lum)*in.g(),(Real)1.0)),
				std::max((Real)0.0,std::min(factor*(Ld/lum)*in.b(),(Real)1.0))));
	}
};

};

#endif
