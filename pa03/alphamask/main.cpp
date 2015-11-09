/*
*  name: cong qiu
*  email: congq@g.clemson.edu
*  date: Sep, 30th, 2015
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
#include<vector>
#include"manager.h"

Manager manager;
int windowWidth=640;
int windowheight=480;
GLubyte* display_data = new GLubyte[0];

//initialization
void init(void)
{
	manager.prepare(windowWidth,windowheight, display_data);
	//manager.run();
	display_data = new unsigned char[windowWidth*windowheight*4];
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

}

//callback in glut loop
void display(void)
{

	manager.display(display_data);

	glClear(GL_COLOR_BUFFER_BIT);

glEnable( GL_ALPHA_TEST );
glAlphaFunc( GL_GREATER, 0.1 );

	glDrawPixels(windowWidth,windowheight,GL_RGBA, GL_UNSIGNED_BYTE, display_data);
	glFlush();
}


void handleMouseClick(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON&&state == GLUT_UP){
		manager.directHSVMask(x,y);
		manager.run();
		manager.display(display_data);

	}
	glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:
		//	doSomething();
			break;
		case GLUT_KEY_RIGHT:
		//	doSomething();
			break;
		case GLUT_KEY_UP:
		//	doSomething();
			manager.incrK();	
			manager.run();	
			manager.display(display_data);
			break;
		case GLUT_KEY_DOWN:
		//	doSomething();
			manager.decK();
			manager.run();
			manager.display(display_data);
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv){

	if(!manager.parseArgs(argc, argv)){
		manager.helpInfo();	
		exit(-1);
	}

	manager.run();

	//live Flag is not on, bye!
	if(!manager.isLive()){
		return 0;}

	init();	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(windowWidth,windowheight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	glutMouseFunc(handleMouseClick);
	glutSpecialFunc(SpecialKeys);	
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;

}



