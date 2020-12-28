#ifndef _IMAGE_RGBCOLOR_H_
#define _IMAGE_RGBCOLOR_H_

//#include <boost/array.hpp>
#include <vector>
//#include <numbers/real.h>

namespace Imaging
{

class RGBColor
{
	Real data[3];
public:
   RGBColor() { (*this)[0]=(*this)[2]=(*this)[2]=0.0; };
   RGBColor(Real c) { (*this)[0]=(*this)[2]=(*this)[2]=c; }
   RGBColor(Real r, Real g, Real b) { (*this)[0]=r; (*this)[1]=g; (*this)[2]=b; }
   RGBColor(const std::vector<Real>& that) { for (int i=0;i<3;i++) (*this)[i]=that[i]; }
   //RGBColor(const boost::array<Real,3>& that) { for (int i=0;i<3;i++) (*this)[i]=that[i]; }
   RGBColor(const Real* that) { for (int i=0;i<3;i++) (*this)[i]=that[i]; }
   const RGBColor& operator=(const std::vector<Real>& that) { for (int i=0;i<3;i++) (*this)[i]=that[i]; return (*this);}
   //const RGBColor& operator=(const boost::array<Real,3>& that) { for (int i=0;i<3;i++) (*this)[i]=that[i]; return (*this);}
   Real &operator[](const int i){return data[i];}
   const Real &operator[](const int i)const{return data[i];}
   Real r() const { return (*this)[0]; }
   Real g() const { return (*this)[1]; }
   Real b() const { return (*this)[2]; }
   const Real* pointer() const { return &((*this)[0]); }

	RGBColor& operator+=(const RGBColor& s)
	{
		for (unsigned int i=0;i<3;i++) (*this)[i]+=s[i];
		return (*this);
	}

	RGBColor operator+(const RGBColor& s) const
	{
		RGBColor sol=(*this);
		return sol+=s;
	}

	RGBColor& operator-=(const RGBColor& s)
	{
		for (unsigned int i=0;i<3;i++) (*this)[i]-=s[i];
		return (*this);
	}

	RGBColor operator-(const RGBColor& s) const
	{
		RGBColor sol=(*this);
		return sol-=s;
	}

	RGBColor& operator*=(const RGBColor& s)
	{
		for (unsigned int i=0;i<3;i++) (*this)[i]*=s[i];
		return (*this);
	}

	RGBColor operator*(const RGBColor& s) const
	{
		RGBColor sol=(*this);
		return sol*=s;
	}

	RGBColor& operator*=(float f)
	{
		for (unsigned int i=0;i<3;i++) (*this)[i]*=f;
		return (*this);
	}

	RGBColor operator*(float f) const
	{
		RGBColor sol=(*this);
		return sol*=f;
	}

	RGBColor& operator*=(double f)
	{
		for (unsigned int i=0;i<3;i++) (*this)[i]*=f;
		return (*this);
	}

	RGBColor operator*(double f) const
	{
		RGBColor sol=(*this);
		return sol*=f;
	}

	RGBColor& operator/=(float f)
	{
		for (unsigned int i=0;i<3;i++) (*this)[i]/=f;
		return (*this);
	}

	RGBColor operator/(float f) const
	{
		RGBColor sol=(*this);
		return sol/=f;
	}

	RGBColor& operator/=(double f)
	{
		for (unsigned int i=0;i<3;i++) (*this)[i]/=f;
		return (*this);
	}

	RGBColor operator/(double f) const
	{
		RGBColor sol=(*this);
		return sol/=f;
	}


};

template <typename T>
RGBColor operator*(const T& t, const RGBColor& s) { return s*t; }

template<typename Stream>
Stream& operator<<(Stream& os,const RGBColor& s) { os.output(s); return os; }

};

#endif


