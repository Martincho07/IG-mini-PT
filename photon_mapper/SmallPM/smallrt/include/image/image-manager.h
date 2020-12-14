#ifndef _IMAGING_IMAGE_MANAGER_H_
#define _IMAGING_IMAGE_MANAGER_H_

#include "image.h"
#include <map>
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/tr1/memory.hpp>

namespace Imaging
{

class ImageManager
{
	std::map<std::string,std::tr1::shared_ptr<Image> > images;

public:
	ImageManager() {}
	~ImageManager()
	{

	}

	const std::tr1::shared_ptr<Image>& image(const std::string& file)
	{
		if (images.find(file) != images.end())
		{
			return images[file];
		}		
		else
		{
			images[file] = std::tr1::shared_ptr<Image>(new Image(file.c_str()));
			std::string ext=boost::filesystem::path(file).extension().string();
		        if (!((ext.compare(".hdr")==0) || (ext.compare(".Hdr")==0) || (ext.compare(".HDR")==0))) (*images[file])/=255.0;
			return images[file];
		}
	}

	template<typename Ostream>
	void debug(Ostream& os)
	{
		os<<"Loaded images:"<<endl;
		std::map<std::string,std::tr1::shared_ptr<Image> >::iterator i;
		for (i=images.begin();i!=images.end();i++)
		{
			os<<"\t"<<(*i).first;
			if ((*i).second) os<<" [ OK ] ";
			else os<<" [NULL] ";
			os<<endl;
		}
	}
};

};

#endif
