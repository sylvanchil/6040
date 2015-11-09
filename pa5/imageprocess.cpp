/************************************
 *    name: cong qiu                 *
 *    email: congq@g.clemson.edu     *
 *    date: OCT, 4th, 2015           *
 *************************************/

#include"imageprocess.h"
#include<cstdlib>
#include<cmath>
#include<iostream>

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


float ImageProcess::clamp(float d){
		if(d>1.0)
			return 1.0;
		if(d< 0)
			return 0;
		return d;
	}

void ImageProcess::applyFilterWithClampTo(MyImage& m,Filter f){
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
						
						float w = exp(-clamp(
									pow(mbk.data[rindex+c]- 
										mbk.data[(int)(w*m.channels + h*m.width*m.channels+c)],2
									)
									)
									);

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


void ImageProcess::simpleToneMapping(MyImage& img, float gm){
	MyImage bkimg = img;
	float* lwArray= new float[bkimg.height*bkimg.width];
	float* ldArray= new float[bkimg.height*bkimg.width];

	for (int y =0; y<bkimg.height; y++ ){
		for(int x =0; x < bkimg.width; x ++){
			lwArray[x+y*bkimg.width] = (
					20*bkimg.data[ x*bkimg.channels + y*bkimg.width*bkimg.channels ]+
					40*bkimg.data[ 1+ x*bkimg.channels + y*bkimg.width*bkimg.channels ]+
					1* bkimg.data[ 2+ x*bkimg.channels + y*bkimg.width*bkimg.channels ])
				/61.0;
		}
	}

	for(int i= 0; i< bkimg.height * bkimg.width; i++){
		ldArray[i] = exp(gm*log(lwArray[i]));
	}
	for (int y =0; y<bkimg.height; y++ ){
		for(int x =0; x < bkimg.width; x ++){	

			int i = x + y * bkimg.width;

			bkimg.data[ x*bkimg.channels + y*bkimg.width*bkimg.channels ] *= (ldArray[i]/lwArray[i]);
			bkimg.data[1+ x*bkimg.channels + y*bkimg.width*bkimg.channels ] *= (ldArray[i]/lwArray[i]);
			bkimg.data[2+ x*bkimg.channels + y*bkimg.width*bkimg.channels ] *= (ldArray[i]/lwArray[i]);
		}
	}
	img = bkimg;
}

void ImageProcess::toneMappingWithConvolution(MyImage& img, float cvalue){

	MyImage bkimg = img;
	float* lwArray= new float[bkimg.height*bkimg.width];
	float* logLwArray= new float[bkimg.height*bkimg.width];
	float* BArray= new float[bkimg.height*bkimg.width];
	float* SArray= new float[bkimg.height*bkimg.width];
	float* ldArray= new float[bkimg.height*bkimg.width];
	float* logLdArray= new float[bkimg.height*bkimg.width];

	float* lwldRatioArray= new float[bkimg.height*bkimg.width];



	for (int y =0; y<bkimg.height; y++ ){
		for(int x =0; x < bkimg.width; x ++){
			lwArray[x+y*bkimg.width] = (
					20*bkimg.data[ x*bkimg.channels + y*bkimg.width*bkimg.channels ]+
					40*bkimg.data[ 1+ x*bkimg.channels + y*bkimg.width*bkimg.channels ]+
					1* bkimg.data[ 2+ x*bkimg.channels + y*bkimg.width*bkimg.channels ])
				/61.0;
		}
	}

	//log(lw)
	for (int i = 0; i < bkimg.height* bkimg.width ; i++){
		logLwArray[i] = log(lwArray[i]);
	}	
	//contruct a mean filter
	int size = 19;

	float* filterData = new float[size*size];
	for(int i =0 ; i < size* size;i ++){
		filterData[i] = 1.0/size/size;
	}
	//convole
	MyImage imageBtoBeConvolve(bkimg.height, bkimg.width, 1, logLwArray);
	applyFilterTo(imageBtoBeConvolve, Filter(size, 1, filterData));
	//only need the data
	memcpy(BArray, imageBtoBeConvolve.data , bkimg.height* bkimg.width* sizeof(float));


	float max=BArray[0];
	float min = BArray[0];
	for(int i =0; i != bkimg.height* bkimg.width;i ++){
		if(BArray[i] > max){ max = BArray[i]; }
		else if(BArray[i]< min) { min= BArray[i];}
	}

	float gm =  log(cvalue)/(max-min);


	for(int i = 0;i < bkimg.height* bkimg.width ;i ++){
		ldArray[i] = exp(
				gm*BArray[i]+ logLwArray[i] -BArray[i]			
				);
	}

	for (int y =0; y<bkimg.height; y++ ){
		for(int x =0; x < bkimg.width; x ++){	

			int i = x + y * bkimg.width;

			bkimg.data[ x*bkimg.channels + y*bkimg.width*bkimg.channels ] *= (ldArray[i]/lwArray[i]);
			bkimg.data[1+ x*bkimg.channels + y*bkimg.width*bkimg.channels ] *= (ldArray[i]/lwArray[i]);
			bkimg.data[2+ x*bkimg.channels + y*bkimg.width*bkimg.channels ] *= (ldArray[i]/lwArray[i]);
		}
	}

	img= bkimg;
}


void ImageProcess::bilateralToneMapping(MyImage& img, float cvalue){

	MyImage bkimg = img;
	float* lwArray= new float[bkimg.height*bkimg.width];
	float* logLwArray= new float[bkimg.height*bkimg.width];
	float* BArray= new float[bkimg.height*bkimg.width];
	float* SArray= new float[bkimg.height*bkimg.width];
	float* ldArray= new float[bkimg.height*bkimg.width];
	float* logLdArray= new float[bkimg.height*bkimg.width];

	float* lwldRatioArray= new float[bkimg.height*bkimg.width];

	for (int y =0; y<bkimg.height; y++ ){
		for(int x =0; x < bkimg.width; x ++){
			lwArray[x+y*bkimg.width] = (
					20*bkimg.data[ x*bkimg.channels + y*bkimg.width*bkimg.channels ]+
					40*bkimg.data[ 1+ x*bkimg.channels + y*bkimg.width*bkimg.channels ]+
					1* bkimg.data[ 2+ x*bkimg.channels + y*bkimg.width*bkimg.channels ])
				/61.0;
		}
	}

	//log(lw)
	for (int i = 0; i < bkimg.height* bkimg.width ; i++){
		logLwArray[i] = log(lwArray[i]);
	}	
	//contruct a mean filter
	int size = 19;

	float* filterData = new float[size*size];
	for(int i =0 ; i < size* size;i ++){
		filterData[i] = 1.0/size/size;
	}


	//convole
	MyImage imageBtoBeConvolve(bkimg.height, bkimg.width, 1, logLwArray);
	applyFilterWithClampTo(imageBtoBeConvolve, Filter(size, 1, filterData));
	//only need the data
	memcpy(BArray, imageBtoBeConvolve.data , bkimg.height* bkimg.width* sizeof(float));


	float max=BArray[0];
	float min = BArray[0];
	for(int i =0; i != bkimg.height* bkimg.width;i ++){
		if(BArray[i] > max){ max = BArray[i]; }
		else if(BArray[i]< min) { min= BArray[i];}
	}

	float gm =  log(cvalue)/(max-min);


	for(int i = 0;i < bkimg.height* bkimg.width ;i ++){
		ldArray[i] = exp(
				gm*BArray[i]+ logLwArray[i] -BArray[i]			
				);
	}

	for (int y =0; y<bkimg.height; y++ ){
		for(int x =0; x < bkimg.width; x ++){	

			int i = x + y * bkimg.width;

			bkimg.data[ x*bkimg.channels + y*bkimg.width*bkimg.channels ] *= (ldArray[i]/lwArray[i]);
			bkimg.data[1+ x*bkimg.channels + y*bkimg.width*bkimg.channels ] *= (ldArray[i]/lwArray[i]);
			bkimg.data[2+ x*bkimg.channels + y*bkimg.width*bkimg.channels ] *= (ldArray[i]/lwArray[i]);
		}
	}

	img= bkimg;
}




























