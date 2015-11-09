#include<cstdlib>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include<GL/glut.h>
#endif


using namespace std;

#define WIDTH 	600
#define HEIGHT	600
#define MAXINT 2147483647
#define COLORDIV 20

GLint colors[3] = {MAXINT,MAXINT,MAXINT};


void drawSquare(){
	//	float colors[3]={0,0,0};
//	GLint colors[3] = {MAXINT,MAXINT,MAXINT};

	glClear(GL_COLOR_BUFFER_BIT);

	//	glColor3f(colors[0],colors[1],colors[2]);
	glColor3i(colors[0], colors[1], colors[2]);


	glBegin(GL_POLYGON);
	glVertex2i(100,100);
	glVertex2i(100,500);
	glVertex2i(500,500);
	glVertex2i(500,100);
	glEnd();

	glFlush();

}

void handleKey(unsigned char key, int x, int y){
	switch(key){
		case 'r':
			if(colors[1]<(MAXINT/COLORDIV)){colors[1]=0;}
			else{colors[1]-=MAXINT/COLORDIV; }
			if(colors[2]<(MAXINT/COLORDIV)){colors[1]=0;}
			else{colors[2]-=MAXINT/COLORDIV; }
			glutPostRedisplay();
			
			break;
		case 'R':

			if(colors[1]>(MAXINT-MAXINT/COLORDIV)){colors[1]=MAXINT;}
			else{colors[1]+=MAXINT/COLORDIV; }
			if(colors[2]>(MAXINT-MAXINT/COLORDIV)){colors[1]=MAXINT;}
			else{colors[2]+=MAXINT/COLORDIV; }
			glutPostRedisplay();

			break;
		case 'g':
			if(colors[0]<(MAXINT/COLORDIV)){colors[1]=0;}
			else{colors[0]-=MAXINT/COLORDIV; }
			if(colors[2]<(MAXINT/COLORDIV)){colors[1]=0;}
			else{colors[2]-=MAXINT/COLORDIV; }
			glutPostRedisplay();
			
			break;
		case 'G':

			if(colors[0]>(MAXINT-MAXINT/COLORDIV)){colors[1]=MAXINT;}
			else{colors[0]+=MAXINT/COLORDIV; }
			if(colors[2]>(MAXINT-MAXINT/COLORDIV)){colors[1]=MAXINT;}
			else{colors[2]+=MAXINT/COLORDIV; }
			glutPostRedisplay();

			break;
		case 'b':
			if(colors[1]<(MAXINT/COLORDIV)){colors[1]=0;}
			else{colors[1]-=MAXINT/COLORDIV; }
			if(colors[0]<(MAXINT/COLORDIV)){colors[1]=0;}
			else{colors[0]-=MAXINT/COLORDIV; }
			glutPostRedisplay();
			
			break;
		case 'B':

			if(colors[1]>(MAXINT-MAXINT/COLORDIV)){colors[1]=MAXINT;}
			else{colors[1]+=MAXINT/COLORDIV; }
			if(colors[0]>(MAXINT-MAXINT/COLORDIV)){colors[1]=MAXINT;}
			else{colors[0]+=MAXINT/COLORDIV; }
			glutPostRedisplay();

			break;
		


		case 'c':
		case 'C':
		case 'q':
		case 'Q':
		case 27:
			exit(0);
		default:
			return;

	}
}


int main(int argc, char* argv[]){
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("this is the first windows");

	glutDisplayFunc(drawSquare);
	glutKeyboardFunc(handleKey);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,WIDTH,0, HEIGHT);

	glClearColor(1,1,1,1);

	glutMainLoop();
	return 0;
}

















