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
#include<vector>

using std::vector;

//data to be displayed
GLubyte* display_data;
//data to be output to file
GLubyte* outputfile;


char* outputfilename;
char * inputFilename;
int do_output = 0;
char outputcolor='o';

//information of images
int imageWidth= 0;
int imageHeight= 0;
int chanls = 0;
vector<vector<vector<GLubyte> > > data;

//flip the displaying data
void flip(){
	GLbyte tmp;
	for(int y = 0;y != imageHeight/2; y++){
		for(int x =0; x != imageWidth; x++){
			for(int c = 0; c!= chanls ;c++){
				tmp = display_data[c+ x*chanls + y*imageWidth*chanls];
				display_data[c + x*chanls+ y*imageWidth*chanls] =display_data[c + x * chanls + (imageHeight-1-y)* imageWidth * chanls];
				display_data[c + x * chanls + (imageHeight-1-y)* imageWidth * chanls] = tmp;
			}
		}
	}
}

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

	//while drawing data, use GL_RGB for 3 channels image, GL_RGBA for 4 channels image
	if(chanls ==3)
		glDrawPixels(imageWidth, imageHeight, GL_RGB, GL_UNSIGNED_BYTE, display_data);
	else 
		glDrawPixels(imageWidth, imageHeight, GL_RGBA, GL_UNSIGNED_BYTE, display_data);
	glFlush();
}

//output data to display, flip in the meantime
void dis(){
	for(int y=0; y != imageHeight; y ++){
		for(int x = 0;x != imageWidth; x ++){
			for(int c = 0;c != chanls ; c++)
			{
				//output the [imageHeight-1-y]th line to the yth line, there fore flip the image. 
				display_data[c + x* chanls+ y * imageWidth* chanls]=data[imageHeight-1-y][x][c];
			}
		}
	}
}

//call to write to file 
void write_to_file(){
	outputfile = new GLubyte[imageHeight* imageWidth*chanls];

	//extract data from 'data', put data into the buffer which will be writen to file
	//when single channel is specified, flag "outputcolor" will be changed in advance, then output accordingly
	if(outputcolor == 'o')
		for(int y=0; y != imageHeight; y ++){
			for(int x = 0;x != imageWidth; x ++){
				for(int c = 0;c != chanls ; c++)
				{
					outputfile[c + x* chanls+ y * imageWidth* chanls]=data[y][x][c];
				}
			}
		}
	else{
		//i for index of colors red green blue in a pixel
		int i=0;
		if(outputcolor=='g') i =1;
		if(outputcolor=='b') i =2;

		for(int y=0; y != imageHeight; y ++){
			for(int x = 0;x != imageWidth; x ++){
				for(int c = 0;c != chanls ; c++)
				{
					if((c+chanls)%chanls==i)					
						outputfile[c + x* chanls+ y * imageWidth* chanls]=data[y][x][c];
					else

						outputfile[c + x* chanls+ y * imageWidth* chanls]=0;
				}
			}
		}
	}

	ImageOutput *out = ImageOutput::create(outputfilename);

	ImageSpec spec (imageWidth, imageHeight, chanls, TypeDesc::UINT8);
	out->open(outputfilename, spec);
	out->write_image(TypeDesc::UINT8, outputfile);
	out->close();
	delete outputfile;

};

//handle mouse click
void handleMouseClick(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON&&state == GLUT_UP){
		//output looks like "the color of point(x,y) is:(r,g,b[,a])."
		std::cout<< "the color of point(" << x <<","<< y<< ") is: ("; 
		for(int i = 0; i!= chanls-1; i ++){
			std::cout << (short)display_data[i + x*chanls + (imageHeight-1-y) * imageWidth*chanls] <<",";
		}
		std::cout << (short)display_data[chanls-1 + x*chanls +(imageHeight-1-y) * imageWidth*chanls] << ").";
	}
	std::cout << std::endl;

}

//the real handlekey function
void handleKey(unsigned char key,int x, int y){
	switch (key){
		case 'f':
			std::reverse(data.begin(), data.end());
			dis();
			break;	
		case 'i':
			for(int y=0; y != imageHeight; y ++){
				std::reverse(data[y].begin(), data[y].end());
			}
			dis();	
			break;
	
		//output single color image
		case 'r':
		case 'g':
		case 'b':{
					 outputcolor=key;
					 int pos=0;
					 if(key=='g') pos = 1;
					 if(key == 'b') pos =2;
					 for(int i = 0; i != imageHeight * imageWidth*chanls;i++){
						 if(i%chanls!=pos)
							 display_data[i] = 0;
					 }
					 break;
				 }
		case 'o':
				 outputcolor=key; 
				 dis();
				 break;

		case 'w':
				 if (do_output==1){
					 write_to_file();
				 }
				 dis();
				break;
		case 'q':
				delete display_data;
				exit(0);
		default:

				 break;
	}
	glutPostRedisplay();
}

//read from file, fill out the information of an image
void readfile(){

	ImageInput *in = ImageInput::open(inputFilename);

	if(!in){
		std::cout << "file not exist" << std::endl;
		exit(-1);
	}


	const ImageSpec & spec = in->spec();
	imageWidth = spec.width;
	imageHeight = spec.height;
	chanls = spec.nchannels;

	display_data = new GLubyte[imageHeight*imageWidth*chanls];

	if(!in->read_image(TypeDesc::UINT8 , display_data)){
		std::cout << "cant read data" << std::endl;
		delete in;

		exit(-1);
	}
	//store data in data vector;
	for(int y = 0; y != imageHeight; y ++){
		vector<vector<GLubyte> > line;
		for(int x = 0; x != imageWidth; x ++){
			vector<GLubyte> pixel;
			for(int c = 0; c != chanls; c ++){
				pixel.push_back(display_data[c + x*chanls + y * imageWidth*chanls]);
			}
			line.push_back(pixel);
		}
		data.push_back(line);
	}

	flip();

}


int main(int argc, char** argv){
	if(argc< 2){
		std::cerr<< "Usage: " << argv[0] << "[filename]" << std::endl;
		exit(-1);
	}
	inputFilename= argv[1];
	readfile();
	if(argc>2){
		do_output = 1;
		outputfilename = argv[2];
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(imageWidth, imageHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutMouseFunc(handleMouseClick);
	glutKeyboardFunc(handleKey);
	glutMainLoop();
	return 0;
}

