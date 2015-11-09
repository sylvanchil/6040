#ifndef MYIMAGE_H_
#define MYIMAGE_H_

#include<cstring>

class MyImage{
private:
	int width;
	int height;
	int channels;
	unsigned char* data;
public:
	MyImage():width(0), height(0), channels(3), data(new unsigned char[0]){
	
	}
	MyImage(const MyImage& m):width(m.width), height(m.height), channels(m.channels), data(new unsigned char[width*height*channels]){
		memcpy(data,m.data, width*height*channels);
	}
	MyImage& operator=(const MyImage& my);

	MyImage to4ChannelsImage();

	MyImage(int wid, int hei, int chan, unsigned char* dat);
	~MyImage(){delete data;}

	int getWidth()const {return width;}
	int getHeight()const {return height;}
	int getChannels()const {return channels;}


	MyImage over(MyImage& image,int posx, int posy);

	//average 2 image
//	MyImage operator+(const MyImage& image);
	//mask image with alpha image
//	MyImage operator*(const MyImage& image);

	void flip();
	void vflip();
	void displayOutput(unsigned char* desBuff);

	friend class FileIO;
	friend class Manager;
	friend class ImageProcess;	

};


#endif
