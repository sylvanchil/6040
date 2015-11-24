/************************************
*    name: cong qiu                 *
*    email: congq@g.clemson.edu     *
*    date: NOV, 4th, 2015           *
*************************************/

#include"myimage.h"
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<vector>
#include"fileio.h"
#include"imageprocess.h"
#include "filter.h"
#include <string>
#include"resource.h"
#include "Matrix.h"

class Manager{
public:
	bool parseArgs(int argc, char** argv);
	void takeMatrix(Matrix3x3 matrix);
	void helpInfo();
	void run();
	bool save();
	bool canWrite();
	void turnTwrilModeOn(double s, double x, double y);
	//output image data to displaying buffer
	void repairInverseMapping();
	void display(unsigned char* des);
	//initialize the display buffer and windowsize 
	void prepare(int& wid, int& hei, int& c);
	Manager():

		writeFlag(false),
		imageFilename(new char[0]),
		resultFilename(new char[0]),
			
		twrilModeOn(false),
		strength(3.75),
		centerX(0.5),
		centerY(0.5),

		matrix3(Matrix3x3(0,0,0,0,0,0,0,0,0)),
		originImage(MyImage()),
		resultImage(MyImage()),
		ip(ImageProcess())
	{}
	~Manager(){}

private:
	
	bool writeFlag;
	char* imageFilename;
	char* resultFilename;

	bool twrilModeOn;

	double strength;
	double centerX;
	double centerY;

	Matrix3x3 matrix3;

	MyImage originImage;
	MyImage resultImage;
	ImageProcess ip;
	
	Manager(const Manager& m);
	Manager& operator=(const Manager& m);

};
