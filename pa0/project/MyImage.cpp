#include"MyImage.h"
#include<algorithm>
#include<cstring>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>


MyImage MyImage::singleChannel(char c){
				
}

void MyImage::flipImage(){
}

void MyImage::vflipImage(){
}

void MyImage::displayOutput(GLubyte* des){
	memcpy(des,data, resX*resY*numberOfChannels);
	
}



