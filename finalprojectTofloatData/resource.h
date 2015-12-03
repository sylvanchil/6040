#ifndef RES_H
#define RES_H

#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>


class Resource{
public:
	int windowWidth;
	int windowHeight;
	int channels;
	float* displayData;

	Resource():
	windowWidth(0),windowHeight(0),channels(0),displayData(new float[0]){
		
	}

	Resource(int w, int h, int c, float* d):
	windowWidth(w),windowHeight(h),channels(c)
	,displayData(new float[windowWidth*windowHeight*channels]){
		memcpy(displayData , d, windowWidth* windowHeight* channels* sizeof(float));
	}	

	Resource(const Resource& r):
	windowWidth(r.windowWidth),windowHeight(r.windowHeight),channels(r.channels),
	displayData(new float[windowWidth* windowHeight* channels]){

		memcpy(displayData , r.displayData, windowWidth* windowHeight* channels*sizeof(float ));
		
	}	


};

#endif 
