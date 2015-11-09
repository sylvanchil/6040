#include"myimage.h"
#include<cstring>
#include<cstdlib>
#include<iostream>
#include"fileio.h"


class Manager{
public:
	bool parseArgs(int argc, char** argv);
	void helpInfo();
	void run();
private:
	bool pvFlag;
	bool ssFlag;
	float pvK;
	char* inputFilenameA;
	char* inputFilenameB;

	void setParam(bool pf, bool sf, float k, char* inamea, char* inameb);
};
