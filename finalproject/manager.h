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
	void applyFilterToResult();
	void resetImage();
	void undo();
	void changeFilter(std::string);
	//run fast mode on 
	bool thunderModeOn();
	//run with out displaying
	void quickRun();
	bool canWrite();
	//output image data to displaying buffer
	void display(unsigned char* des);
	//initialize the display buffer and windowsize 
	void prepare(int& wid, int& hei, int& c);
	Manager():
		tFlag(false),
		gFlag(false),
		theta(0.0),
		sigma(0.0),
		period(0.0),
		writeFlag(false),
		filterFilename( new char[0]),
		imageFilename(new char[0]),
		resultFilename(new char[0]),
		filter(Filter()),
		originImage(MyImage()),
		resultImage(MyImage()),
		historyImages(std::vector<MyImage>()),
		ip(ImageProcess())
	{}
	~Manager(){}

private:
	bool tFlag;
	bool gFlag;
	float theta;
	float sigma;
	float period;
	bool writeFlag;

	char* filterFilename;
	char* imageFilename;
	char* resultFilename;

	Filter filter;
	MyImage originImage;
	MyImage resultImage;
	//store the history, not implemented yet
	std::vector<MyImage> historyImages; 
	ImageProcess ip;
	
	Manager(const Manager& m);
	Manager& operator=(const Manager& m);

};
