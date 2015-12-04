/************************************
*    name: cong qiu                 *
*    email: congq@g.clemson.edu     *
*    date: DEC, 3rd, 2015           *
*************************************/

#ifndef MYIMAGE_H_
#define MYIMAGE_H_

#include<cstring>

class MyImage{
private:
	int width;
	int height;
	int channels;
	float* data;
public:
	MyImage():width(0), height(0), channels(3), data(new float[0]){
	
	}
	MyImage(const MyImage& m):width(m.width), height(m.height), channels(m.channels), data(new float[width*height*channels]){
		memcpy(data,m.data, width*height*channels*sizeof(float)
		);
	}
	MyImage& operator=(const MyImage& my);

	MyImage to4ChannelsImage();

	MyImage(int wid, int hei, int chan, float* dat);
	~MyImage(){delete data;}

	int getWidth()const {return width;}
	int getHeight()const {return height;}
	int getChannels()const {return channels;}

	MyImage over(MyImage& image,int posx, int posy);

	void flip();
	void vflip();
	void displayOutput(float* desBuff);

	friend class FileIO;
	friend class Manager;
	friend class ImageProcess;	

};


#endif
