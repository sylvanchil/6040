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
		}
	}
}

void ImageProcess::applyFilterTo(MyImage& m,Filter f){
	MyImage mbk(m);

	int rindex = 0; 
	int findex = 0;
	int yoffset= 0;
	int xoffset=0;
//store the compute then normalize with them	
	float * tmpData = new float[m.height*m.width*m.channels];
	
	for(int h = 0; h != m.height; h ++){
		for(int w = 0; w!= m.width ; w ++){

			float rgba[4] = {0.0,0.0,0.0,0.0}; 
			for(int j = 0;j != f.size; j ++){
				for (int i = 0; i != f.size ; i++ ){
					yoffset= j - f.size/2;
					xoffset = i - f.size/2;
					findex = j*f.size + i;
					int H, W;
					//reflection to handle boundary
					if(h + yoffset<0) H= -(h+yoffset);
					else if((h+ yoffset)> m.height) H = m.height - (h+yoffset-m.height);
					else H = h + yoffset;

					if(w + xoffset<0) W= -(w+xoffset);
					else if((w+ xoffset)> m.width) W = m.width - (w+xoffset-m.width);
					else W = w + xoffset;

					rindex = H* m.width* m.channels + W* m.channels;
					for(int c = 0; c != m.channels; c ++){
						rgba[c]+= f.value[findex] * mbk.data[rindex+c];

					}
				}
			}

			rindex = w*m.channels + h*m.width*m.channels;
			for(int c = 0; c != m.channels; c ++){
				m.data[rindex+c] = rgba[c];	
				tmpData[rindex+c] = rgba[c];
			}
		}
	}
	if(f.type()==0){
		int max = 0;
		int min = 0;
		for(int i= 0;i!= m.height* m.width*m.channels; i ++){
			if(tmpData[i]> max)
				max = tmpData[i];
			else if(tmpData[i]< min){
				min = tmpData[i];
			}
		}
		//find the max offset
		//then scale the result 
		if(abs(min)> max) max = min;
		for(int i= 0; i!= m.height*m.width*m.channels; i ++){
			m.data[i] = tmpData[i]*127/max + 127;
		}

	}

}
void ImageProcess::applyGaborFilterTo(MyImage& m, float t, float s, float p){
//	const float e= 2.71828;
	const float pi = 3.14159;
	float kx, ky, a;
	int size = s*2+1;
	float *value = new float[size*size];
	int i = 0;
	for(int y= 0-size/2;y < size/2+1; y ++ ){
		for (int x = 0-size/2; x < size/2+1; x ++){
			kx = x*cos(t/180*pi)+ y*sin(t/180*pi);
			ky = -x*sin(t/180*pi)+ y* cos(t/180*pi);
			a = exp(-(kx*kx+ ky*ky)/(2*s*s))*(cos(2*pi*kx/p));
			value[i++] = a;		
		}
	}
	applyFilterTo(m, Filter(size, 0, value));
	delete value;
}

void ImageProcess::inverseMapping(const MyImage& srcImg, MyImage& desImg){
	


}








