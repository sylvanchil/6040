#include"imageprocess.h"
#include<cstdlib>
#include"colorwindow.h"
void ImageProcess::setAlpha(MyImage& img, bool pv, bool ss){
	if(img.getChannels()!=4){
		exit(-1);
	}
	unsigned char r,g,b;
	float h,s,v;
	if(!pv&&!ss){
		for(int y = 0 ;y != img.height; y++){
			for (int x =0; x != img.width; x ++){
				r = img.data[0+x*4+y*img.width*4];
				g = img.data[1+x*4+y*img.width*4];
				b = img.data[2+x*4+y*img.width*4];
				RGBtoHSV(r,g,b,h,s,v);
				if(h>90.0 && h < 150.0){
					
					img.data[3+x*4+y*img.width*4]=0;
				}

			}
		}
	}

}

