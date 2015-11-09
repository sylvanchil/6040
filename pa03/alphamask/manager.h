/*
*  name: cong qiu
*  email: congq@g.clemson.edu
*  date: Sep, 30th, 2015
*/

#include"myimage.h"
#include<cstring>
#include<cstdlib>
#include<iostream>
#include"fileio.h"
#include"imageprocess.h"

class Manager{
public:
	bool parseArgs(int argc, char** argv);
	void helpInfo();
	void run();
	//display or not
	bool noDisplay();
	//output image data to displaying buffer
	void display(unsigned char* des);
	//initialize the display buffer and windowsize 
	void prepare(int& wid, int& hei, unsigned char* disData);
	//increase K value;
	void incrK();
	//decrease K
	void decK();
	//get pixel value rgb then do hsv mask 
	void directHSVMask(int x, int y);


	Manager():pvFlag(false),
			ssFlag(false),
			hFlag(false),
			hRangeB(90.0),
			hRangeU(150.0),
			sFlag(false),
			sRangeB(0.0),
			sRangeU(1.0),
			vFlag(false),
			vRangeB(0.0),
			vRangeU(1.0),
			gFlag(false),
			kFlag(false),
			pvK(1.0),
			lFlag(false),
			cFlag(false),
			oFlag(false),
			originFilename(new char[0]),
			maskedFilename(new char[0]),
			backgroundFilename(new char[0]),
			outputFilename(new char[0]),
			ip(ImageProcess()),
			originImage(MyImage()),
			maskedImage(MyImage()),
			bgImage(MyImage()),
			outputImage(MyImage()){
			
	}
	~Manager(){
		//delete originFilename;
		//delete maskedFilename;
		//delete backgroundFilename;
		//delete outputFilename;
	}
private:
	bool pvFlag;
	bool ssFlag;
	//hsv flag 
	bool hFlag;
	float hRangeB;
	float hRangeU;
	bool sFlag;
	float sRangeB;
	float sRangeU;
	bool vFlag;
	float vRangeB;
	float vRangeU;
	bool gFlag;
	bool kFlag;
	float pvK;
	//live view flag 
	bool lFlag;
	//compositing flag
	bool cFlag;
	//output flag
	bool oFlag;
	char* originFilename;
	char* maskedFilename;
	char* backgroundFilename;
	char* outputFilename;
	//to process image 
	ImageProcess ip;
	MyImage originImage;
	MyImage maskedImage;
	MyImage bgImage;
	MyImage outputImage;
//obsolete
	void setParam(bool pf, bool sf, float k, char* inamea, char* inameb);
	Manager(const Manager& m);
	Manager& operator=(const Manager& m);

};
