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
		bool canWrite();
		//output image data to displaying buffer
		void display(float* des);
		//initialize the display buffer and windowsize 
		void prepare(int& wid, int& hei, int& c);
		void switchImage();


		Manager():
			cFlag(false),
			gFlag(false),
			bFlag(false),
			gm(0.4),
			cvalue(20),
			writeFlag(false),
			sFlag(1),	
			imageFilename(new char[0]),
			resultFilename(new char[0]),
			filter(Filter()),
			originImage(MyImage()),
			resultImage(MyImage()),
			ip(ImageProcess())
	{}
		~Manager(){}

	private:
		bool cFlag;
		bool gFlag;
		bool bFlag;

		float gm;
		float cvalue;
		bool writeFlag;

		int sFlag;
		char* imageFilename;
		char* resultFilename;

		Filter filter;
		MyImage originImage;
		MyImage resultImage;

		ImageProcess ip;
		Manager(const Manager&);

};
