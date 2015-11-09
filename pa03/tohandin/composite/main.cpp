/*	name: cong qiu
 *	email: congq@g.clemson.edu
 *  date: 7th Sep 2015
 */
#include<OpenImageIO/imageio.h>
OIIO_NAMESPACE_USING
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

#include<stdlib.h>
#include<string>
#include<algorithm>
#include<iostream>
#include"myimage.h"
#include"fileio.h"


GLubyte* display_data = new GLubyte[0];
MyImage foreImage;
MyImage backImage;
MyImage imageToBeOutput;

//initialization
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

//callback in glut loop
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawPixels(imageToBeOutput.getWidth(), imageToBeOutput.getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, display_data);
	glFlush();
}


int main(int argc, char** argv){
	if(argc < 3){
		std::cout << "usage:"<<std::endl;
		std::cout << "composite [foregroundImagename] [backgroundImagename]" << std::endl;
		std::cout << "or" <<std::endl;
		std::cout << "composite [foregroundImagename] [backgroundImagename] [outputIMagename]" << std::endl;
		exit(-1);
	}

	FileIO::getInstance().readFromFileToImage(foreImage, argv[1]);
	FileIO::getInstance().readFromFileToImage(backImage, argv[2]);
	imageToBeOutput = foreImage.over(backImage,0,0);
	display_data = new GLubyte[imageToBeOutput.getWidth()*imageToBeOutput.getHeight()*4];
	imageToBeOutput.displayOutput(display_data);

	if(argc>3){
		FileIO::getInstance().writeImageToFile(imageToBeOutput,argv[3]);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(imageToBeOutput.getWidth(), imageToBeOutput.getHeight());
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

