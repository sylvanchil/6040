/************************************
*    name: cong qiu                 *
*    email: congq@g.clemson.edu     *
*    date: OCT, 4th, 2015           *
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

class Manager{
public:
	bool parseArgs(int argc, char** argv);
	void helpInfo();
	void run();
	bool save();
	void resetImage();
	void undo();
	bool canWrite();
	//output image data to displaying buffer
	void display(float* des);
	//initialize the display buffer and windowsize 
	void prepare(int& wid, int& hei, int& c);

	void setMode(int i);

	void addBrushPaint(int x, int y);
	
	void adjust(double value);

	void setUseBrush(int i);
	
	void magBrush();
	void minBrush();
	void magFading();
	void minFading();
	
	void displayOriginal(float* des);
	void savemask();

	Manager():
		writeFlag(false),
		mode(1),
	
		useBrush(0),
		rSolid(20),
		rFading(50),

		maskImage(MyImage()),
		imageFilename(new char[0]),
		resultFilename(new char[0]),
		
		originImage(MyImage()),
		resultImage(MyImage()),
		historyImages(std::vector<MyImage>()),
		ip(ImageProcess())
	{}
	~Manager(){}

private:
	bool writeFlag;

	int mode;
	/*
	1 Brightness
	2 Saturation
	3 Hightlight
	4 Shadow 
	5 Whitebalance
	6 Contrast
	*/
	int useBrush;
	double rSolid;
	double rFading;
	
	MyImage maskImage;

	char* imageFilename;
	char* resultFilename;

	MyImage originImage;
	MyImage resultImage;
	std::vector<MyImage> historyImages; 
	ImageProcess ip;
	
	Manager(const Manager& m);
	Manager& operator=(const Manager& m);
};
