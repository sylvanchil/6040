/************************************
*    name: cong qiu                 *
*    email: congq@g.clemson.edu     *
*    date: OCT, 4th, 2015           *
*************************************/

#include"myimage.h"
#include"filter.h"


class ImageProcess{
public:

	//apply Filter to img
	void applyFilterTo( MyImage& img, Filter f );
	//Gabor filter 
	void applyGaborFilterTo(MyImage& img, float t, float s,float p);

    float clamp(float d);

	void applyFilterWithClampTo(MyImage& img, Filter f); 

	void simpleToneMapping(MyImage& img, float gm);

	void toneMappingWithConvolution(MyImage& img, float cvalue);

	void bilateralToneMapping(MyImage& img,float cvalue);
};
