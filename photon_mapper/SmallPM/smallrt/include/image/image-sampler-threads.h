#ifndef _IMAGE_IMAGE_SAMPLER_THREADS_H_
#define _IMAGE_IMAGE_SAMPLER_THREADS_H_

#include "image-sampler.h"
#include <thread/concurrent-queue.h>

namespace Imaging
{

class ImageSamplerThreads : public ImageSampler
{
protected:
	class ImageArea
	{
	public:
		int imin;  int jmin;  int imax; int jmax;
		Real xmin; Real ymin; Real dx;  Real dy;

		ImageArea() {}

		ImageArea(int _imin, int _jmin, int _imax, int _jmax, Real _xmin, Real _ymin, Real _dx, Real _dy):
			imin(_imin),jmin(_jmin),imax(_imax),jmax(_jmax),xmin(_xmin),ymin(_ymin),dx(_dx),dy(_dy) {}		
	};

	template<typename F>
	class ThreadTask
	{
		Image& image;
		const F& f;
		concurrent_queue<ImageArea>& queue;
	
	public:
		ThreadTask(Image& _image, const F& _f, concurrent_queue<ImageArea>& _queue):
			image(_image),f(_f),queue(_queue) { }

		void operator()()
		{
			ImageArea area;
			int i,j; Real x,y;
			while(true)
			{
				queue.wait_and_pop(area);
				for (j=area.jmin, y=area.ymin;j<area.jmax;j++,y+=area.dy)
					for (i=area.imin, x=area.xmin;i<area.imax;i++,x+=area.dx)
						image.set(i,j,f(x,y));
			}
		}
	};
private:
	int chunks;	
	Real min; Real max; 	

public:
	ImageSamplerThreads(int _chunks = 4, Real _min = -1.0, Real _max=1.0) :
		chunks(_chunks),min(_min),max(_max) { }

	template<typename F>
	void sample(Image& image, const F& f) const
	{
		
		concurrent_queue<ImageArea> queue;
		int n=boost::thread::hardware_concurrency();
		boost::thread_group tg;

		for (int i=0;i<n;i++)
		{	tg.create_thread(ThreadTask<F>(image,f,queue)); }

		Real d = (max-min)/(Real)image.width();

		for (int j=0;j<chunks;j++)
			for (int i=0;i<chunks;i++)
				queue.push(ImageArea((i*image.width())/chunks,(j*image.height())/chunks,
					   ((i+1)*image.width())/chunks,((j+1)*image.height())/chunks,
					   min + d*((i*image.width())/chunks),
					   min*((Real)image.height()/(Real)image.width()) + d*((j*image.width())/chunks),
					   d,d)); 	   

		queue.wait_for_empty();
		tg.interrupt_all();
		tg.join_all();		
	}

	void _sample(Image& image, const ImageFunction& image_function) const { sample(image,image_function); }
};

};

#endif
