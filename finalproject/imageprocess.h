/************************************
*    name: cong qiu                 *
*    email: congq@g.clemson.edu     *
*    date: OCT, 4th, 2015           *
*************************************/

#include"myimage.h"
#include"filter.h"


class ImageProcess{
public:
	void adjustBrightness(MyImage& img, MyImage& area, double value);
	void adjustSaturation(MyImage& img, MyImage& area, double value);
	void adjustContrast(MyImage& img, MyImage& area, double value);
	void adjustWhitebalance(MyImage& img, MyImage& area, double value);
	void adjustHighlight(MyImage& img, MyImage& area, double value);
	void adjustShadow(MyImage& img, MyImage& area, double value);

	void brushMaskImage(MyImage& mimg, int x, int y, double rs, double rf);
};
