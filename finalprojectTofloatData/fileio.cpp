/************************************
*    name: cong qiu                 *
*    email: congq@g.clemson.edu     *
*    date: OCT, 4th, 2015           *
*************************************/

#include<OpenImageIO/imageio.h>
OIIO_NAMESPACE_USING
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include"fileio.h"
#include<fstream>

FileIO& FileIO::getInstance(){
	static FileIO instance;
	return instance;
}

bool FileIO::readFromFileToImage(MyImage& my, char* filename)
{
	ImageInput *in = ImageInput::open(filename);

	if(!in){
		std::cout << "file not exist" << std::endl;
		return false;
	}
	const ImageSpec & spec = in->spec();
	int imageWidth = spec.width;
	int imageHeight = spec.height;
	int chanls = spec.nchannels;

//	std::cout<< chanls << std::endl;

	float* data = new float[imageHeight*imageWidth*chanls];

	if(!in->read_image(TypeDesc::FLOAT , data)){
		std::cout << "cant read data" << std::endl;
		delete in;
		return false;
	}
	my = MyImage(imageWidth, imageHeight, chanls, data);
	return true;
}

bool FileIO::writeImageToFile(const MyImage& my, char* filename){
	ImageOutput *out = ImageOutput::create(filename);
	ImageSpec spec(my.getWidth(),my.getHeight(), my.getChannels(),  TypeDesc::UINT8);
	if((out->open(filename, spec))){
		out->write_image(TypeDesc::FLOAT, my.data);
		out->close();
		delete out;
		return true;
	}
	return false ;

}



