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

//read filter file
bool FileIO::readFromFileToFilter(Filter& f,const char* filename){
	std::ifstream in(filename);
	if(!in)
		return false;
	int size ;
	in >> size;
	float* filterdata = new float[size*size];
	float tmp;
	float psum =0;
	float nsum =0;
	for(int i =0; i!= size* size ; i++){
		in >> tmp;
		if(tmp >0) 
			psum += tmp;
		else 
			nsum+= abs(tmp);
		filterdata[i] =tmp; 
	}
	
	if(psum> nsum){
		for(int i =0;i != size *size; i ++){
			filterdata[i] = filterdata[i]/psum;	
		}
	}
	else{
		for(int i =0;i != size*size ;i ++){
			
			filterdata[i] = filterdata[i]/nsum;	
		}
	}
	if(nsum > 0)
		f= Filter(size, 0, filterdata);
	else 
		f= Filter(size, 1, filterdata);
	return true;
}



