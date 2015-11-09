/*
*  name: cong qiu
*  email: congq@g.clemson.edu
*  date: Sep, 30th, 2015
*/
#include"myimage.h"

class ImageProcess{
public:
	void hsvMask(MyImage& img, float hB, float hU, float sB, float sU, float vB, float vU);
	void hsvGSMask(MyImage& img, float hB, float hU, float sB, float sU, float vB, float vU);
	void pvMask(MyImage& img, float k);
	void ssMask(MyImage& img, float k);
	void myMask(MyImage& img);
};
