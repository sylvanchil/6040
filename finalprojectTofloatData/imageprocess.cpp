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

void ImageProcess::adjustBrightness(MyImage& img,  MyImage& area, double value ){
//	area= area; //delete later.
	float h=0;
	float s=0;
	float v=0;

	float r = 0.0;
	float g = 0.0;
	float b = 0.0;
	
	for(int y = 0;y != img.height; y ++){
		for(int x =0; x != img.width;x ++){
			RGBtoHSV(
					img.data[y*img.width*img.channels+x*img.channels],
					img.data[y*img.width*img.channels+x*img.channels+1],
					img.data[y*img.width*img.channels+x*img.channels+2],
					h,s,v
					);
			
			v = v*(1+ value*((area.data[y * area.width +x])));
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
	//area= area; //delete later.
	float h=0;
	float s=0;
	float v=0;

	float r = 0;
	float g = 0;
	float b = 0;
	
	for(int y = 0;y != img.height; y ++){
		for(int x =0; x != img.width;x ++){
			RGBtoHSV(
					img.data[y*img.width*img.channels+x*img.channels],
					img.data[y*img.width*img.channels+x*img.channels+1],
					img.data[y*img.width*img.channels+x*img.channels+2],
					h,s,v
					);
		
			s = s*(1+ value*(area.data[y * area.width +x])  );
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

void ImageProcess::adjustHighlight(MyImage& img, MyImage& area, double value){
//	area= area; //delete later.
	float h=0;
	float s=0;
	float v=0;

	float r = 0;
	float g = 0;
	float b = 0;
	
	float adj=0 ;

	for(int y = 0;y != img.height; y ++){
		for(int x =0; x != img.width;x ++){
			RGBtoHSV(
					img.data[y*img.width*img.channels+x*img.channels],
					img.data[y*img.width*img.channels+x*img.channels+1],
					img.data[y*img.width*img.channels+x*img.channels+2],
					h,s,v
					);
	
			if(v> 0.5){	
				adj= (v -0.5)*(v -0.5);
			}else{
				adj = 0;
			}
			
			r= img.data[y*img.width*img.channels+x*img.channels]*(1.0+value*((area.data[y * area.width +x]))*adj);
			g=img.data[y*img.width*img.channels+x*img.channels+1]*(1.0+value*((area.data[y * area.width +x]))*adj);
			b=img.data[y*img.width*img.channels+x*img.channels+2]*(1.0+value*((area.data[y * area.width +x]))*adj);

		//	if(r > 255) r = 255;
		//	if(g> 255) g = 255;
		//	if(b> 255) b = 255;

			//HSVtoRGB(h,s,v,r,g,b);
			img.data[y*img.width*img.channels+x*img.channels] =r;
			img.data[y*img.width*img.channels+x*img.channels+1] =g;
			img.data[y*img.width*img.channels+x*img.channels+2] =b;
		}
	}




}

void ImageProcess::adjustShadow(MyImage& img, MyImage& area, double value){
//	area= area; //delete later.
	float h=0;
	float s=0;
	float v=0;

	float r = 0;
	float g = 0;
	float b = 0;
	
	float adj=0 ;

	for(int y = 0;y != img.height; y ++){
		for(int x =0; x != img.width;x ++){
			RGBtoHSV(
					img.data[y*img.width*img.channels+x*img.channels],
					img.data[y*img.width*img.channels+x*img.channels+1],
					img.data[y*img.width*img.channels+x*img.channels+2],
					h,s,v
					);
	
			if(v< 0.5){	
				adj= (0.5 -v)*(0.5-v);
			}else{
				adj = 0;
			}
			
			r= img.data[y*img.width*img.channels+x*img.channels]*(1.0-value*((area.data[y * area.width +x]))*adj);
			g=img.data[y*img.width*img.channels+x*img.channels+1]*(1.0-value*((area.data[y * area.width +x]))*adj);
			b=img.data[y*img.width*img.channels+x*img.channels+2]*(1.00-value*((area.data[y * area.width +x]))*adj);

			if(r > 255) r = 255;
			if(g> 255) g = 255;
			if(b> 255) b = 255;

			//HSVtoRGB(h,s,v,r,g,b);
			img.data[y*img.width*img.channels+x*img.channels] =r;
			img.data[y*img.width*img.channels+x*img.channels+1] =g;
			img.data[y*img.width*img.channels+x*img.channels+2] =b;
		}
	}

}

void ImageProcess::adjustWhitebalance(MyImage& img, MyImage& area, double value){
//	area= area; //delete later.
	
	float r= 0;
	float b = 0;

	for(int y = 0;y != img.height; y ++){
		for(int x =0; x != img.width;x ++){
				
			r = img.data[y*img.width*img.channels+x*img.channels] *(1+value*((area.data[y * area.width +x])));
			b= img.data[y*img.width*img.channels+x*img.channels+2] *(1-value*((area.data[y * area.width +x])));
		
			if(r > 255) r = 255;
			if(b> 255) b = 255;

			img.data[y*img.width*img.channels+x*img.channels] = r;
			img.data[y*img.width*img.channels+x*img.channels+2]=b; 
		}
	}
}

void ImageProcess::adjustContrast(MyImage& img, MyImage& area, double value){
	adjustHighlight(img, area, value);
	adjustShadow(img, area, value);
}

void ImageProcess::brushMaskImage(MyImage& mimg, int bx, int by, double rs, double rf){
	
	double d= 0;
	double v = 0;
	for(int y = 0; y < mimg.height; y ++ ){
		for(int x = 0; x < mimg .width; x ++){

			d= sqrt((y-by)*(y-by)+(x-bx)*(x-bx));
			if(d < rs){
				v = 1;
				if(mimg.data[y*mimg.width+x] < v)
					{mimg.data[y*mimg.width+x] = v;}
			}
			if(d > rs && d < rf){
				v = (d-rf)/(rs-rf);
				if(mimg.data[y*mimg.width+x] < v)
					{mimg.data[y*mimg.width+x] = v;}
					
			}
		}
	}
	


}

















