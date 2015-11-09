/*
*  name: cong qiu
*  email: congq@g.clemson.edu
*  date: Sep, 30th, 2015
*/
#include"myimage.h"

class ImageProcess{
public:
	//normal hsv masking base on HSV range
	void hsvMask(MyImage& img, float hB, float hU, float sB, float sU, float vB, float vU);
	//greyscale hsvmaksing 
	void hsvGSMask(MyImage& img, float hB, float hU, float sB, float sU, float vB, float vU);
	//pv masking
	void pvMask(MyImage& img, float k);
	//spill suppression 
	void ssMask(MyImage& img, float k);
	void myMask(MyImage& img);
};
