/*
*  name: cong qiu
*  email: congq@g.clemson.edu
*  date: Sep, 30th, 2015
*/

#include"imageprocess.h"
#include<cstdlib>
#include"colorwindow.h"
/*void setAlpha(MyImage& img, bool pv, bool ss){
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
 */

void ImageProcess::hsvMask(MyImage& img, float hB, float hU, float sB, float sU, float vB, float vU){
	if(img.getChannels()!=4){
		exit(-1);
	}
	unsigned char r,g,b;
	float h,s,v;
	for(int y = 0 ;y != img.height; y++){
		for (int x =0; x != img.width; x ++){
			r = img.data[0+x*4+y*img.width*4];
			g = img.data[1+x*4+y*img.width*4];
			b = img.data[2+x*4+y*img.width*4];
			RGBtoHSV(r,g,b,h,s,v);
			if(h>hB && h < hU&& s>sB && s<sU && v>vB&& v < vU){
				img.data[3+x*4+y*img.width*4]=0;
			}
		}
	}
}



void ImageProcess::hsvGSMask(MyImage& img, float hB, float hU, float sB, float sU, float vB, float vU){
	if(img.getChannels()!=4){
		exit(-1);
	}
	unsigned char r,g,b;
	float h,s,v;
	for(int y = 0 ;y != img.height; y++){
		for (int x =0; x != img.width; x ++){
			r = img.data[0+x*4+y*img.width*4];
			g = img.data[1+x*4+y*img.width*4];
			b = img.data[2+x*4+y*img.width*4];
			RGBtoHSV(r,g,b,h,s,v);
			if(s>sB && s<sU && v>vB&& v < vU){
				if(h>hB&& h <=hU){
					img.data[3+x*4+y*img.width*4]=0;}
				else if(h > (hB-16)&& h < hB){
					img.data[3+x*4+y*img.width*4]= 256/16*(hB-h);}
				else if(h>hU && h< (hU+16)){
					img.data[3+x*4+y*img.width*4]= 256/16*(h-hU);}
			}
		}
	}
}

void ImageProcess::pvMask(MyImage& img, float k){
	float g,b;
	for(int y =0; y != img.height; y++){
		for(int x = 0; x != img.width; x++){
		//	r = img.data[0+x*4+y*img.width*4];
			g = img.data[1+x*4+y*img.width*4];
			b = img.data[2+x*4+y*img.width*4];
			if(g> b*k ){
				img.data[3+x*4+y*img.width*4]=0;
			}
		}
	}
}

void ImageProcess::ssMask(MyImage& img, float k){
	float r, g,b,matte, max;
	for(int y =0; y != img.height; y++){
		for(int x = 0; x != img.width; x++){
			r = img.data[0+x*4+y*img.width*4];
			g = img.data[1+x*4+y*img.width*4];
			b = img.data[2+x*4+y*img.width*4];
			
			if(g > b*k){
				g = b;
			}
			if(b > r){max = b;}
			else{ max = r;}
			
			matte = g - max;

			img.data[3+x*4+y*img.width*4]= matte;

			
			//if(g> b*k ){
			//	img.data[3+x*4+y*img.width*4]=0;
			//}
		}
	}




}











