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
	void display(unsigned char* des);
	//initialize the display buffer and windowsize 
	void prepare(int& wid, int& hei, int& c);
	
	void adjustBrightness();
	void adjustSaturation();
	void adjustContrast();
	void adjustWhitebalance();
	void adjustHighlight();
	void adjustShadow();

	Manager():
		writeFlag(false),
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

	char* imageFilename;
	char* resultFilename;

	MyImage originImage;
	MyImage resultImage;
	std::vector<MyImage> historyImages; 
	ImageProcess ip;
	
	Manager(const Manager& m);
	Manager& operator=(const Manager& m);
};
