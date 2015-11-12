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

#include "Matrix.h"

Manager manager;

Resource res(640,480,4,new unsigned char[640*480*4]);

/*
   Convert the string s to lower case
 */
void lowercase(char *s){
	int i;

	if(s != NULL) {
		for(i = 0; s[i] != '\0'; i++) {
			if(s[i] >= 'A' && s[i] <= 'Z')
				s[i] += ('a' - 'A');
		}
	}
}

//scale sx sy
void Scale(Matrix3x3 &M, float sx, float sy){
	int row, col;
	Matrix3x3 R(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);

	R[0][0] = sx;
	R[1][1] = sy;

	Matrix3x3 Prod = R * M;

	for(row = 0; row < 3; row++) {
		for(col = 0; col < 3; col++) {
			M[row][col] = Prod[row][col];
		}
	}
}


//translate dx dy
void Translate(Matrix3x3 &M, float dx, float dy){
	int row, col;
	Matrix3x3 R(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);

	R[0][2] = dx;
	R[1][2] = dy;

	Matrix3x3 Prod = R * M;

	for(row = 0; row < 3; row++) {
		for(col = 0; col < 3; col++) {
			M[row][col] = Prod[row][col];
		}
	}
}

//shear hx hy

void Shear(Matrix3x3 &M, float hx, float hy){
	int row, col;
	Matrix3x3 R(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);

	R[0][1] = hx;
	R[1][0] = hy;

	Matrix3x3 Prod = R * M;

	for(row = 0; row < 3; row++) {
		for(col = 0; col < 3; col++) {
			M[row][col] = Prod[row][col];
		}
	}
}


/* 
   Multiply M by a rotation matrix of angle theta
 */

void Rotate(Matrix3x3 &M, float theta){
	int row, col;
	Matrix3x3 R(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
	double rad, c, s;

	rad = PI * theta / 180.0;
	c = cos(rad);
	s = sin(rad);

	R[0][0] = c;
	R[0][1] = -s;
	R[1][0] = s;
	R[1][1] = c;

	Matrix3x3 Prod = R * M;

	for(row = 0; row < 3; row++) {
		for(col = 0; col < 3; col++) {
			M[row][col] = Prod[row][col];
		}
	}
}


/*
   Routine to build a projective transform from input text, display, or
   write transformed image to a file
 */
void process_input(Matrix3x3 &M){
	char command[1024];
	bool done;
	float theta;

	float inputX;
	float inputY;
	float inputZ;
	/* build identity matrix */
	M.identity();

	for(done = false; !done;) {

		/* prompt and accept input, converting text to lower case */
		printf("> ");
		scanf("%s", command);
		lowercase(command);

		/* parse the input command, and read parameters as needed */
		if(strcmp(command, "d") == 0) {
			done = true;
		} else if(strlen(command) != 1) {
			printf("invalid command, enter r, s, t, h, d\n");
		} else {
			switch(command[0]) {

				case 'r':		/* Rotation, accept angle in degrees */
					if(scanf("%f", &theta) == 1)
						Rotate(M, theta);
					else
						fprintf(stderr, "invalid rotation angle\n");
					break;
				case 's':		/* Scale, accept scale factors */
					if(scanf("%f %f", &inputX, &inputY))
						Scale(M, inputX, inputY);
					else
						fprintf(stderr,"invalid scaling input\n");

					break;
				case 't':		/* Translation, accept translations */
					if(scanf("%f %f", &inputX, &inputY))
						Translate(M, inputX, inputY);
					else
						fprintf(stderr,"invalid scaling input\n");

					break;
				case 'h':		/* Shear, accept shear factors */
					if(scanf("%f %f", &inputX, &inputY))
						Shear(M, inputX, inputY);
					else
						fprintf(stderr,"invalid scaling input\n");
				
				//twirl mode on
				case 'n':
					if(scanf("%f %f %f", &inputX, &inputY, &inputZ)){
						manager.turnTwrilModeOn(inputX, inputY, inputZ);
					}else{
						fprintf(stderr, "invalid scaling input\n");
					}

					break;
				case 'd':		/* Done, that's all for now */
					done = true;
					break;
				default:
					printf("invalid command, enter r, s, t, h, d\n");
			}
		}
	}
}


//initialization
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
		case 'w':
		case 'W':
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
		case 'Q':
		case 27:
			exit(0);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}




int main(int argc, char** argv){

	Matrix3x3 M(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);

	process_input(M);

	cout << "Accumulated Matrix: " << endl;
	cout << M << endl;

	if(!manager.parseArgs(argc, argv)){
		manager.helpInfo();	
		exit(-1);
	}

	manager.takeMatrix(M);

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


