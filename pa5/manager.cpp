/************************************
 *    name: cong qiu                 *
 *    email: congq@g.clemson.edu     *
 *    date: OCT, 4th, 2015           *
 *************************************/

#include"manager.h"

bool Manager::parseArgs(int argc, char** argv){
	if(argc < 3)
		return false;
	int fileCount=0;
	char* tmpFilenameList[3];

	for(int i = 1; i!= argc; i++){
		// argument "-xx"
		if(argv[i][0]=='-'){
			if(argv[i][1] =='c'){
				cFlag = true;
				i++;
				cvalue= atof(argv[i]);
			}else if(argv[i][1] == 'g'){
				gFlag = true;
				i ++;
				gm = atof(argv[i]);
			}else if(argv[i][1] == 'b'){
				bFlag = true;
				i++;
				cvalue= atof(argv[i]);
			}
		}
		//end of if "-xx"
		//start of else
		else{
			if(fileCount <4){
				tmpFilenameList[fileCount] = argv[i];
				fileCount++;
			}else {
				return false;
			}
		}
		//end of else
	}

	imageFilename= tmpFilenameList[0];
	if(fileCount >1){
		resultFilename = tmpFilenameList[1];
		writeFlag = true;
	}
	return true;
}


void Manager::helpInfo(){
	//use cat command to output the manual
	system("cat man");	
	std::cout << "Or see README for usage" <<std::endl;
}

void Manager::run(){	
	//read image
	if(!FileIO::getInstance().readFromFileToImage(originImage,imageFilename)){
		exit(-1);	
	}
	//initialize the result image
	resultImage = originImage;
	if(bFlag){
		ip.bilateralToneMapping(resultImage, cvalue);	
	}else if(cFlag){
		ip.toneMappingWithConvolution(resultImage, cvalue);
	}else if(gFlag){
		ip.simpleToneMapping(resultImage, gm);
	}else{
		std::cout << "no gamma value" << std::endl;
	}
	//	ip.toneMappingWithConvolution(resultImage, 0.2);
}

bool Manager::save(){
	//save the current result
	if(!FileIO::getInstance().writeImageToFile(resultImage,resultFilename)){
		return false;
	}
	return true;
}


bool Manager::canWrite(){
	//there are output filename
	return writeFlag;
}

void Manager::display(float* des){
	if(sFlag ==1){
		resultImage.displayOutput(des);
	}
	if(sFlag ==0){
		originImage.displayOutput(des);
	}

}

void Manager::prepare(int& w, int& h, int& c){
	//set weight height channels for displaying
	w = originImage.getWidth();
	h = originImage.getHeight();
	c = originImage.getChannels();
}

void Manager::switchImage(){
	sFlag= (sFlag+1)%2;
	//std::cout << sFlag << std::endl;

}




