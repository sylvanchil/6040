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
#include<stdlib.h>
#include<string>
#include<algorithm>
#include<iostream>
#include<vector>
#include"manager.h"

Manager manager;
int windowWidth=640;
int windowheight=480;
int chanls = 3;
//buffer to display
GLubyte* display_data = new GLubyte[0];

//initialization
void init(void)
{
	manager.run();
	manager.prepare(windowWidth,windowheight,chanls);
	display_data = new unsigned char[windowWidth*windowheight*4];
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	manager.display(display_data);
}
//callback in glut loop
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if(chanls ==3)
		glDrawPixels(windowWidth,windowheight,GL_RGB, GL_UNSIGNED_BYTE, display_data);
	else if(chanls ==4)
		glDrawPixels(windowWidth,windowheight,GL_RGBA, GL_UNSIGNED_BYTE, display_data);
	else if(chanls ==1){
		glDrawPixels(windowWidth,windowheight,GL_LUMINANCE, GL_UNSIGNED_BYTE, display_data);
	}
	glFlush();
}

void handleKey(unsigned char key,int x, int y){
	x=x;//useless, just get rid of the warning
	y=y;//useless, just get rid of the warning
	switch(key){	
		case 'c':
			manager.applyFilterToResult();
			manager.display(display_data);
			break;
		case 'r':
			manager.resetImage();
			manager.display(display_data);
			break;
		case 'w':
			if(manager.canWrite()){
				if(manager.save()){
					std::cout << "saved"<< std::endl;
				}
				else{
					std::cout << "save file false" << std::endl;
				}
			}
			else{
				std::cout << "no filename" << std::endl;
			}
			break;
		case 'q':
		case 27:
			exit(0);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv){
	if(!manager.parseArgs(argc, argv)){
		manager.helpInfo();	
		exit(-1);
	}
	if(manager.thunderModeOn()){
		manager.quickRun();
		exit(0);
	}

	init();	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(windowWidth,windowheight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutKeyboardFunc(handleKey);
	glutMainLoop();
	return 0;

}
