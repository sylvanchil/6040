#include"MyImage.h"
#include<algorithm>

#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>


MyImage MyImage::singleChannel(char c){
				
}

void MyImage::flipImage(){
	for(int y=0; y != resY; y ++){
		std::reverse(data[y], data[y]+resX*numberOfChannels);
	}	
}

void MyImage::vflipImage(){
	std::reverse(data, data+resX*resY*numberOfChannels);	
}

void MyImage::displayOutput(GLubyte* des){

	for(int y=0; y !=resY;y ++){
		for(int x = 0;x !=resX; x ++){
			for(int c = 0;c !=numberOfChannels;c++)
			{
				des[c + x*numberOfChannels+ y* resX*numberOfChannels]= data[y][x][c];
			
			}
		}
	
	
	
	}

	
}



