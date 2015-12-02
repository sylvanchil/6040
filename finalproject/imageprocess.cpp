/************************************
*    name: cong qiu                 *
*    email: congq@g.clemson.edu     *
*    date: OCT, 4th, 2015           *
*************************************/

#include"imageprocess.h"
#include<cstdlib>
#include<cmath>
#include<iostream>
#include"colorwindow.h"

void ImageProcess::adjustBrightness(MyImage& img, MyImage& area, double value ){
	area= area; //delete later.
	float h=0;
	float s=0;
	float v=0;

	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	
	for(int y = 0;y != img.height; y ++){
		for(int x =0; x != img.width;x ++){
			RGBtoHSV(
					img.data[y*img.width*img.channels+x*img.channels],
					img.data[y*img.width*img.channels+x*img.channels+1],
					img.data[y*img.width*img.channels+x*img.channels+2],
					h,s,v
					);
		
			v = v*(1+ value);
			if (v> 1.00){
				v = 1.00;
			}
			
			HSVtoRGB(h,s,v,r,g,b);

			img.data[y*img.width*img.channels+x*img.channels] = r;
			img.data[y*img.width*img.channels+x*img.channels+1] =g;
			img.data[y*img.width*img.channels+x*img.channels+2] =b;
		}
	}
}

void ImageProcess::adjustSaturation(MyImage& img, MyImage& area, double value){
	area= area; //delete later.
	float h=0;
	float s=0;
	float v=0;

	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	
	for(int y = 0;y != img.height; y ++){
		for(int x =0; x != img.width;x ++){
			RGBtoHSV(
					img.data[y*img.width*img.channels+x*img.channels],
					img.data[y*img.width*img.channels+x*img.channels+1],
					img.data[y*img.width*img.channels+x*img.channels+2],
					h,s,v
					);
		
			s = s*(1+ value);
			if (s> 1.00){
				s = 1.00;
			}
			
			HSVtoRGB(h,s,v,r,g,b);

			img.data[y*img.width*img.channels+x*img.channels] = r;
			img.data[y*img.width*img.channels+x*img.channels+1] =g;
			img.data[y*img.width*img.channels+x*img.channels+2] =b;
		}
	}

}

void ImageProcess::adjustHighlight(MyImage& img, MyImage& area, double value){}

void ImageProcess::adjustShadow(MyImage& img, MyImage& area, double value){}

void ImageProcess::adjustWhitebalance(MyImage& img, MyImage& area, double value){}

void ImageProcess::adjustContrast(MyImage& img, MyImage& area, double value){
	adjustHighlight(img, area, value);
	adjustShadow(img, area, -value);
}













