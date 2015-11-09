#include<vector>
#include<iostream>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<algorithm>
#include<iterator>
#include<cstring>

using std::vector;



class MyImage{
		public:
				MyImage() {}
				//				MyImage(const MyImage &m){}

				MyImage(const MyImage &m){
						resX = m.resX;
						resY = m.resY;
						numberOfChannels = m.numberOfChannels;
						memcpy(data, m.data, resX*resY*numberOfChannels);
				}

				MyImage(GLubyte* srcdata, int resx, int resy, int chnls):resX(resx),resY(resy), numberOfChannels(chnls){
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
				unsigned char* data;
//				vector<vector<vector<unsigned char> > > data;


};



