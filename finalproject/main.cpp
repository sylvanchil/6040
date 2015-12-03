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
#include"resource.h"

Manager manager;
Resource res(640,480,4,new unsigned char[640*480*4]);
bool recordMouse = false;

void init(void)
{
	manager.run();
	manager.prepare(res.windowWidth,res.windowHeight,res.channels);
	res.displayData = new unsigned char[res.windowWidth*res.windowHeight*4];
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	manager.display(res.displayData);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if(res.channels ==3)
		glDrawPixels(res.windowWidth,res.windowHeight,GL_RGB, GL_UNSIGNED_BYTE, res.displayData);
	else if(res.channels ==4)
		glDrawPixels(res.windowWidth,res.windowHeight,GL_RGBA, GL_UNSIGNED_BYTE, res.displayData);
	else if(res.channels ==1){
		glDrawPixels(res.windowWidth,res.windowHeight,GL_LUMINANCE, GL_UNSIGNED_BYTE, res.displayData);
	}
	glFlush();
}

	
void handleKey(unsigned char key,int x, int y){
	x=x;//useless, just get rid of the warning
	y=y;//useless, just get rid of the warning
	switch(key){	
		case 'r':
			manager.resetImage();
			manager.display(res.displayData);
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
		case 's':
			manager.savemask();
			break;
		case 'u':
			manager.undo();
			manager.display(res.displayData);	
			break;
		case 'o':
			manager.displayOriginal(res.displayData);
			break;
		case 'O':
			manager.display(res.displayData);	
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
			manager.setUseBrush(0);
			manager.setMode(key);
			std::cout << "int mode " << key<< std::endl;
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


void SpecialKey(int Key, int x, int y){
	x = x;
	y = y;
	switch(Key){
		case GLUT_KEY_UP:
			manager.adjust(0.05);
			manager.display(res.displayData);	
			break;
		case GLUT_KEY_DOWN:
			manager.adjust(-0.05);
			manager.display(res.displayData);	
			break;
		case GLUT_KEY_LEFT:

			break;
		case GLUT_KEY_RIGHT:

			break;

	}


	glutPostRedisplay();
}

void MouseClick(int button, int state, int x, int y){
	x = x;
	y = y;
	if ( button == GLUT_LEFT_BUTTON ) {
		if ( state == GLUT_DOWN ) {
			manager.setUseBrush(1);
			recordMouse = true;
		} else {
			recordMouse = false;
		}
	}
}

void MouseMove(int x, int y){
	if(recordMouse){
		manager.addBrushPaint(x, y);
	}
}

int main(int argc, char** argv){
	if(!manager.parseArgs(argc, argv)){
		manager.helpInfo();	
		exit(-1);
	}

	init();	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(res.windowWidth,res.windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);

	glutKeyboardFunc(handleKey);
	glutSpecialFunc(SpecialKey);
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMove);

	glutMainLoop();
	return 0;
}
