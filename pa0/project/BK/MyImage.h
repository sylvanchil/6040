#include<vector>
#include<iostream>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<cstdlib>
#include<cstring>


using std::vector;



class MyImage{
	public:
		MyImage() {}
		MyImage(const MyImage &m){}

		MyImage(GLubyte* srcdata, int resx, int resy, int chnls):resX(resx),resY(resy), numberOfChannels(chnls){
			data =(char ***) new char[resx*resy*chnls];
			memcpy(data, srcdata, resx*resy*chnls);
		}

		~MyImage(){}



		//return MyImage with the only specifid channel, c in { r,g,b}
		MyImage singleChannel(char c);

		//return the flipped image
		void flipImage();

		//return the vertical flipped image	
		void vflipImage();

		void displayOutput(GLubyte* des);

		int dataLength(){return resX*resY*numberOfChannels;}

		int getResX(){return resX;}
		int getResY(){return resY;}
		int channelsNum(){return numberOfChannels;}
	private:
		int resX;
		int resY;
		int numberOfChannels;

		char*** data;	

};



