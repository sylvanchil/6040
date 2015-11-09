/************************************
*    name: cong qiu                 *
*    email: congq@g.clemson.edu     *
*    date: OCT, 4th, 2015           *
*************************************/

#include"myimage.h"
#include"filter.h"
#include"Matrix.h"

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

	//apply Filter to img
	void applyFilterTo( MyImage& img, Filter f );
	//Gabor filter 
	void applyGaborFilterTo(MyImage& img, float t, float s,float p);
	
	void inverseMapping(MyImage& img, Matrix3x3 m);
	

};
