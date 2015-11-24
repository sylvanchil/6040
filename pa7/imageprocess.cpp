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
/*
   void ImageProcess::bilinearWarp(MyImage& img, Matrix3x3 m){
   Vector3d topLeft	(0			,0			, 1);
   Vector3d topRight	(img.width	,0			, 1);
   Vector3d buttomLeft	(0			,img.height	, 1);
   Vector3d buttomRight(img.width	,img.height	, 1);

   topLeft = m* topLeft;
   topRight = m*topRight;
   buttomLeft = m* buttomLeft;
   buttomRight = m* buttomRight;

   double xs[4]= { topLeft[0]/topLeft[2], topRight[0]/topRight[2], buttomRight[0]/buttomRight[2], buttomLeft[0]/buttomLeft[2]};
   double ys[4]= { topLeft[1]/topLeft[2], topRight[1]/topRight[2], buttomRight[1]/buttomRight[2], buttomLeft[1]/buttomLeft[2]};

   double maxx, minx, maxy, miny;

//find the range of x and y
if(xs[0]> xs[1]){
maxx = xs[0];
minx = xs[1];
}else{
maxx = xs[1];
minx = xs[0];
}

if(xs[2]> maxx){
maxx = xs[2];
}else if(xs[2]< minx){
minx = xs[2];
}

if(xs[3]> maxx){
maxx = xs[3];
}else if(xs[3]< minx){
minx = xs[3];
}
//y max min
if(ys[0]> ys[1]){
maxy = ys[0];
miny = ys[1];
}else{
maxy = ys[1];
miny = ys[0];
}

if(ys[2]> maxy){
maxy = ys[2];
}else if(ys[2]< miny){
miny = ys[2];
}

if(ys[3]> maxy){
maxy = ys[3];
}else if(ys[3]< miny){
miny = ys[3];
}

//translation, to move the image to center;
Matrix3x3 calMatrix(1,0,-minx,0,1,-miny,0,0,1);

Matrix3x3 translateToCenter = calMatrix*m;

Matrix3x3 inversedMatrix = translateToCenter.inv();

//	double factor= inversedMatrix[2][2];

//prepara data for new image
int newImageWidth = maxx - minx;
int newImageHeight = maxy - miny;
int newImageChannels = img.channels;
unsigned char* newImageData = new unsigned char[newImageWidth * newImageHeight* newImageChannels];

memset(newImageData , 0, newImageWidth* newImageHeight* newImageChannels);

for(int y= 0;y < newImageHeight ;y ++){
	for(int x = 0; x < newImageWidth; x ++ ){
		Vector3d pixelPos(x,y,1);
		pixelPos = inversedMatrix*pixelPos;

		for(int c = 0; c< newImageChannels ; c ++){
			int ox= round(pixelPos[0]/pixelPos[2]);
			int oy= round(pixelPos[1]/pixelPos[2]);

			if(ox>0 && ox < img.width && oy > 0 && oy < img.height){
				newImageData[y*newImageWidth*newImageChannels + x*newImageChannels +c]=	
					img.data[oy*img.width*img.channels + ox*img.channels + c];
			}
			else{

				newImageData[y*newImageWidth*newImageChannels + x*newImageChannels +c]=	0;
			}
		}

	}
}
img = MyImage(newImageWidth, newImageHeight, newImageChannels, newImageData);





}
*/

void ImageProcess::inverseMapping( MyImage& img, Matrix3x3 m, int flag){
	Vector3d topLeft	(0			,0			, 1);
	Vector3d topRight	(img.width	,0			, 1);
	Vector3d buttomLeft	(0			,img.height	, 1);
	Vector3d buttomRight(img.width	,img.height	, 1);

	topLeft = m* topLeft;
	topRight = m*topRight;
	buttomLeft = m* buttomLeft;
	buttomRight = m* buttomRight;

	double xs[4]= { topLeft[0]/topLeft[2], topRight[0]/topRight[2], buttomLeft[0]/buttomLeft[2], buttomRight[0]/buttomRight[2]};
	double ys[4]= { topLeft[1]/topLeft[2], topRight[1]/topRight[2], buttomLeft[1]/buttomLeft[2], buttomRight[1]/buttomRight[2]};

	double maxx, minx, maxy, miny;

	//find the range of x and y
	if(xs[0]> xs[1]){
		maxx = xs[0];
		minx = xs[1];
	}else{
		maxx = xs[1];
		minx = xs[0];
	}

	if(xs[2]> maxx){
		maxx = xs[2];
	}else if(xs[2]< minx){
		minx = xs[2];
	}

	if(xs[3]> maxx){
		maxx = xs[3];
	}else if(xs[3]< minx){
		minx = xs[3];
	}
	//y max min
	if(ys[0]> ys[1]){
		maxy = ys[0];
		miny = ys[1];
	}else{
		maxy = ys[1];
		miny = ys[0];
	}

	if(ys[2]> maxy){
		maxy = ys[2];
	}else if(ys[2]< miny){
		miny = ys[2];
	}

	if(ys[3]> maxy){
		maxy = ys[3];
	}else if(ys[3]< miny){
		miny = ys[3];
	}

	//translation, to move the image to center;
	Matrix3x3 calMatrix(1,0,-minx,0,1,-miny,0,0,1);

	Matrix3x3 translateToCenter = calMatrix*m;

	Matrix3x3 inversedMatrix = translateToCenter.inv();

	//	double factor= inversedMatrix[2][2];

	//prepara data for new image
	int newImageWidth = maxx - minx;
	int newImageHeight = maxy - miny;
	int newImageChannels = img.channels;
	unsigned char* newImageData = new unsigned char[newImageWidth * newImageHeight* newImageChannels];

	memset(newImageData , 0, newImageWidth* newImageHeight* newImageChannels);
	//inverse mapping
	for(int y= 0;y < newImageHeight ;y ++){
		for(int x = 0; x < newImageWidth; x ++ ){
			Vector3d pixelPos(x,y,1);
			pixelPos = inversedMatrix*pixelPos;

			for(int c = 0; c< newImageChannels ; c ++){
				int ox= round(pixelPos[0]/pixelPos[2]);
				int oy= round(pixelPos[1]/pixelPos[2]);

				if(ox>1 && ox < img.width-1 && oy > 1 && oy < img.height-1){
					if(flag== 0){
						newImageData[y*newImageWidth*newImageChannels + x*newImageChannels +c]=	
							img.data[oy*img.width*img.channels + ox*img.channels + c];
					}else if(flag==1){

						int orx = floor(pixelPos[0]/pixelPos[2]);
						int ory = floor(pixelPos[1]/pixelPos[2]);
						double da = pixelPos[0]/pixelPos[2]- orx;
						double db = pixelPos[1]/pixelPos[2]- ory;

						Vector2d va(1-da, da);
						Vector2d vb(1-db, db);

						Matrix2x2 m(
							img.data[ory*img.width*img.channels + orx*img.channels + c],
							img.data[ory*img.width*img.channels + (orx+1)*img.channels + c],
							img.data[(ory+1)*img.width*img.channels + orx*img.channels + c],
							img.data[(ory+1)*img.width*img.channels + (orx+1)*img.channels + c]
						);	
						
						newImageData[y*newImageWidth*newImageChannels + x*newImageChannels +c]=	
							vb*m*va;
					}
				}
				else{

					newImageData[y*newImageWidth*newImageChannels + x*newImageChannels +c]=	0;
				}

			}
		}

	}

img = MyImage(newImageWidth, newImageHeight, newImageChannels, newImageData);

}

void  ImageProcess::inverseMapping(MyImage& img, double strength, double cx, double cy){

	int newImageWidth = img.width;
	int newImageHeight = img.height;
	int newImageChannels = img.channels;
	unsigned char* newImageData = new unsigned char[newImageWidth * newImageHeight * newImageChannels];

	memset(newImageData, 0, newImageWidth* newImageHeight * newImageChannels);

	double centerX = newImageWidth* cx;
	double centerY = newImageHeight* cy;
	double mD;
	if(img.width> img.height){
		mD = img.height;
	}else {
		mD = img.width;
	}

	for(int y = 0; y != newImageHeight ;y ++){
		for(int x =0; x != newImageWidth; x ++){

			/* 
			   using 	u = x*cos(a)+ y*sin(a)
			   v = -x*sin(a)+ y*cos(a)
			   a = strength(r - minDim)/minDim
			   this is a derivation of the inversed twirl mapping formula
			 */
			double r=sqrt(pow(x-centerX, 2)+ pow(y-centerY, 2));

			double a = strength* ( r -mD  )/mD;

			int ox =round( (x-centerX)*cos(a) + (y-centerY)* sin(a) + centerX);
			int oy =round( -(x-centerX)*sin(a) + (y-centerY)* cos(a) + centerY);

			for(int c = 0; c < newImageChannels ;c ++){

				if(ox>=0 && ox < img.width && oy >= 0 && oy < img.height){
					newImageData[y*newImageWidth*newImageChannels + x*newImageChannels +c]=	
						img.data[oy*img.width*img.channels + ox*img.channels + c];
				}
				else{
					newImageData[y*newImageWidth*newImageChannels + x*newImageChannels +c]=	0;
				}
			}
		}
	}

	img = MyImage(newImageWidth, newImageHeight, newImageChannels , newImageData);

}






