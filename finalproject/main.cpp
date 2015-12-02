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
//callback in glut loop
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
		case 'u':
			manager.undo();
			manager.display(res.displayData);	
			break;
		case 'b':
			manager.adjustBrightness();
			manager.display(res.displayData);
			break;
		case 's':
			manager.adjustSaturation();
			manager.display(res.displayData);
			break;

		case 'h':
			manager.adjustHighlight();
			manager.display(res.displayData);
			break;

		case 'j':
			manager.adjustShadow();
			manager.display(res.displayData);
			break;

		case 'l':
			manager.adjustContrast();
			manager.display(res.displayData);
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
	
	init();	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(res.windowWidth,res.windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);

	glutKeyboardFunc(handleKey);
	glutMainLoop();
	return 0;
}
