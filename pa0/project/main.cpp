#include<OpenImageIO/imageio.h>
OIIO_NAMESPACE_USING
#include<iostream>
#include<cstdlib>
#include<vector>
#include"MyImage.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif



std::vector<MyImage> images(10);
int current_image_index = 0;
GLubyte* display_image_data;

char one_channeled = 0;

//init function 
void init(void){

	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	display_image_data = new GLubyte[images[current_image_index].dataLength()];
	
	images[current_image_index].displayOutput(display_image_data);
	

}

void clean(){}


//display function 
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawPixels(images[current_image_index].getResX(), images[current_image_index].getResY(), GL_RGB, GL_UNSIGNED_BYTE, display_image_data);


	glFlush();

}




void handleKey(unsigned char key, int x, int y){
	switch(key){
		case 'f':
			images[current_image_index].flipImage();		
			images[current_image_index].displayOutput(display_image_data);	
			//do the flip
			break;

		case 'w':


			//do the write
			break;

		case 'i':

			images[current_image_index].vflipImage();		


			images[current_image_index].displayOutput(display_image_data);	
			//do the vertical flip
			break;
		case 'r':
		case 'g':
		case 'b':
			if(key != one_channeled){
				MyImage tmpImage = images[current_image_index].singleChannel(key);
				tmpImage.displayOutput(display_image_data);


			}
			//do the one channel thing
			break;

		case 'o':
			if(one_channeled!=0){
				images[current_image_index].displayOutput(display_image_data);
				one_channeled = 0;
			}

			break;		
		case 27:
		case 'c':
			exit(0);
			break;
	}
	glutPostRedisplay();


}


//reshape funciton ,to be implemented
void reshape(int w, int h){
}

void SpecialInput(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			//do something here
			exit(0);
			break;
		case GLUT_KEY_DOWN:
			exit(0);
			//do something here
			break;
		case GLUT_KEY_LEFT:
			//do something here


			current_image_index = (current_image_index+ images.size()-1)%images.size();

			images[current_image_index].displayOutput(display_image_data);

			break;
		case GLUT_KEY_RIGHT:
			//do something here

			current_image_index= (current_image_index+1)% images.size();

			images[current_image_index].displayOutput(display_image_data);
			break;
	}

	glutPostRedisplay();
} 


//


MyImage read_file(const char* filename){

	ImageInput *in = ImageInput::open(filename);

	const ImageSpec &spec = in->spec();

	int resX = spec.width;
	int resY = spec.height;
	int channels = spec.nchannels;

	unsigned char* pixels = new unsigned char[resX * resY * channels];

	in->read_image(TypeDesc::UINT8, pixels);

	in->close();

	return MyImage(pixels, resX, resY, channels);
	//todo : convert the data to image


}


int write_file(const MyImage image, const char* filename ){


	ImageOutput *out = ImageOutput::create(filename);

	//
	int resX;
	int resY;
	int channels;
	//todo: assign the value
	unsigned char* pixels= new unsigned char[resX*resY*channels];

	ImageSpec specOut(resX, resY, channels, TypeDesc::UINT8);

	out->write_image(TypeDesc::UINT8, pixels);

	out->close();
	delete out;


}


int main(int argc, char** argv){


	if(argc < 2){
		std::cout << "usage: oiioview [filename] [filename2] ..." << std::endl;
		exit(0);
	}


	//read all file into image vector;
	for(int i = 1; i < argc-1; i++){
		//MyImage img;
		images.push_back(read_file(argv[i]));
	}




	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);


	//todo: get the real width and height
	int theFakeWidth=640;
	int theFakeHeight=640;
	glutInitWindowSize(theFakeWidth,theFakeHeight);

	//todo: get the real position
	int theFakeX=200;
	int theFakeY=200;
	glutInitWindowPosition(theFakeX, theFakeY);


	glutCreateWindow(argv[0]);
	init();


	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(handleKey);
	glutSpecialFunc(SpecialInput);



	glutMainLoop();

	return 0;
}













