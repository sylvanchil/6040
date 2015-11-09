/*
*  name: cong qiu
*  email: congq@g.clemson.edu
*  date: Sep, 30th, 2015
*/

#include"manager.h"
#include"colorwindow.h"

void Manager::setParam(bool pf, bool sf, float k, char* inamea, char* inameb){
	pvFlag = pf;
	ssFlag = sf;
	pvK = k;
	originFilename= new char[sizeof(inamea)+1];
	strcpy(originFilename, inamea);
	maskedFilename= new char[sizeof(inameb)+1];
	strcpy(maskedFilename, inameb);

}


bool Manager::parseArgs(int argc, char** argv){
	if(argc < 3)
		return false;
	
	int filenameCount=0;

	for(int i = 1; i!= argc; i++){
		// argument "-xx"
		if(argv[i][0]=='-'){
			switch(argv[i][1]){
			case 'p':
				pvFlag = true;
				break;
			case 's':
				if(argv[i][2]=='s'){
					ssFlag =true;
				}else{
					sFlag = true;
					i ++;
					try{
						sRangeB = atof(argv[i]);
						i ++ ;
						sRangeU = atof(argv[i]);
					}
					catch(int e){
						return false;
					}
				}
				break;
			case 'h':
				hFlag = true;
				i ++;
				try{
					hRangeB = atof(argv[i]);
					i ++ ;
					hRangeU = atof(argv[i]);
				}
				catch(int e){
					return false;
				}
				break;
		//	case 's';
			case 'v':
				vFlag = true;
				i ++;
				try{
					vRangeB = atof(argv[i]);
					i ++ ;
					vRangeU = atof(argv[i]);
				}
				catch(int e){
					return false;
				}
				break;
			case 'g':
				gFlag = true;
				break;
			case 'k':
				kFlag= true;
				if(i == (argc-1)){
					return false;
				}
				i++;
				try{
					pvK = atof(argv[i]);
					//throw 1;
				}
				catch(int e){
					return false;
				}
				break;
			case 'l':
				lFlag = true;
				break;
			case 'c':
				cFlag = true;
				i++;
				backgroundFilename = argv[i];
				break;
			case 'o':
				oFlag = true;
				i++;
				outputFilename = argv[i];
				break;
			case 'i':
				return false;
			default: 
				return false;
			}
		}
		//end of if "-xx"
		//start of else
		else{
			if(filenameCount==0){
				originFilename = argv[i];
				filenameCount++;
			}else if(filenameCount == 1){
				maskedFilename = argv[i];
				filenameCount++;
			}else {
				return false;
			}
		}
		//end of else
	}

	//no hsv with pv flag and vice verse
	if((pvFlag&&(hFlag||sFlag||vFlag))||
		(pvFlag&&gFlag)
	){
		return false;
	}

	return true;
}


void Manager::helpInfo(){
	std::cout << "basic usage:" <<std::endl;
	std::cout << "\t alphamask [originalFile] [maskedfile]"<<std::endl;
	std::cout << ""<<std::endl;
	std::cout << "Options"<<std::endl;
	std::cout << "\t-pv\n\t\tuse pv algorithm"<<std::endl;
	std::cout << "\t-ss\n\t\tapply spill suppression"<<std::endl;
	std::cout << "\t-k kvalue\n\t\tpreset k value"<<std::endl;
	std::cout << "\t-h,s,v [buttom] [upper]\n\t\tspecify range of h or s of v"<<std::endl;
	std::cout << "\t-g\n\t\tgreyscale"<<std::endl;
	std::cout << "\t-c [filename]\n\t\tcomposit with background image"<<std::endl;
	std::cout << "\t-l\n\t\tview live change"<<std::endl;
	std::cout << "\t-o [filename]\n\t\toutput composited image"<<std::endl;
	std::cout << "\t\t"<<std::endl;
	std::cout << "Or see README for usage" <<std::endl;
}

void Manager::run(){
	//read from file
	if(!FileIO::getInstance().readFromFileToImage(originImage,originFilename)){
		exit(-1);	
	}

	maskedImage = originImage.to4ChannelsImage();
	//process the image base on the flags
	if(pvFlag){
		ip.pvMask(maskedImage, pvK);
	}else if(ssFlag){
		ip.ssMask(maskedImage, pvK);
	}else {
		if(!gFlag){
			ip.hsvMask(maskedImage,hRangeB,hRangeU,sRangeB,sRangeU,vRangeB,vRangeU);	
		}else{
			ip.hsvGSMask(maskedImage,hRangeB,hRangeU,sRangeB,sRangeU,vRangeB,vRangeU);	
		}
	}
	//output masked image
	if(!FileIO::getInstance().writeImageToFile(maskedImage,maskedFilename)){
		exit(-1);
	}
	if(cFlag&&oFlag){

		if(!FileIO::getInstance().readFromFileToImage(bgImage,backgroundFilename)){
			exit(-1);	
		}
		outputImage =maskedImage.over(bgImage, 0,0);
		if(!FileIO::getInstance().writeImageToFile(outputImage, outputFilename)){
			exit(-1);
		}
		
	}

}

bool Manager::isLive(){
	return lFlag;
}

void Manager::display(unsigned char* des){
	if(!cFlag){
		maskedImage.displayOutput(des);
	}else{
		outputImage.displayOutput(des);
	}

}

void Manager::prepare(int& w, int& h, unsigned char* dD){
	if(!cFlag){
		w = maskedImage.getWidth();
		h = maskedImage.getHeight();
		dD = new unsigned char[w*h*4];
	}else{
		w= outputImage.getWidth();
		h = outputImage.getHeight();
		dD = new unsigned char[w*h*4];
	}
}

void Manager::incrK(){
	pvK+=0.1;
}

void Manager::decK(){
	pvK-=0.1;
}

void Manager::directHSVMask(int x, int y){
	unsigned char r, g,b;
	r = maskedImage.data[x*4 + y*maskedImage.width*4];
	g = maskedImage.data[x*4 + y*maskedImage.width*4];
	b = maskedImage.data[x*4 + y*maskedImage.width*4];
	float h,s,v;
	RGBtoHSV(r,g,b,h,s,v);
	hRangeB = h-10;
	hRangeU = h+10;
	

}




















