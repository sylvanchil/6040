/************************************
*    name: cong qiu                 *
*    email: congq@g.clemson.edu     *
*    date: OCT, 4th, 2015           *
*************************************/

#include"manager.h"
#include"colorwindow.h"

bool Manager::parseArgs(int argc, char** argv){
	if(argc < 3)
		return false;
	int fileCount=0;
	char* tmpFilenameList[3];

	for(int i = 1; i!= argc; i++){
		// argument "-xx"
		if(argv[i][0]=='-'){
			if(argv[i][1] =='g'){
				if((i+3)<argc){
					gFlag = true;
					i ++ ;
					theta= atof(argv[i]);
					i++;
					sigma = atof(argv[i]);
					i ++ ;
					period = atof(argv[i]);
				}else{
					return false;
				}
			}else if(argv[i][1] == 't'){
				tFlag = true;
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
	if(gFlag&& fileCount ==3){
		return false;
	}
	//if there are -g, the 1st filename is the input image
	if(gFlag){
		imageFilename= tmpFilenameList[0];
		if (fileCount ==2){
			writeFlag= true;
			resultFilename = tmpFilenameList[1];
		}
	}
	//else the 1st filename is the name of filter	
	else{
		filterFilename = tmpFilenameList[0];
		imageFilename= tmpFilenameList[1];
		if(fileCount==3){
			writeFlag= true;
			resultFilename = tmpFilenameList[2];
		}
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
	if(!gFlag){
		if(!FileIO::getInstance().readFromFileToFilter(filter,filterFilename)){
			exit(-1);	
		}	
	}
}

bool Manager::save(){
	//save the current result
	if(!FileIO::getInstance().writeImageToFile(resultImage,resultFilename)){
		return false;
	}
	return true;
}

void Manager::applyFilterToResult(){
	//apply filter to current resultimage accordingly 
	if(!gFlag){
		ip.applyFilterTo(resultImage, filter);
	}else{
		ip.applyGaborFilterTo(resultImage, theta, sigma, period);
	}
}

void Manager::resetImage(){
	//reset the image to original Image
	resultImage = originImage;
}

bool Manager::thunderModeOn(){
	return tFlag;
}

void Manager::quickRun(){
	run();
	applyFilterToResult();
	save();
}

bool Manager::canWrite(){
	//there are output filename
	return writeFlag;
}

void Manager::display(unsigned char* des){
	resultImage.displayOutput(des);
}

void Manager::prepare(int& w, int& h, int& c){
	//set weight height channels for displaying
	w = originImage.getWidth();
	h = originImage.getHeight();
	c = originImage.getChannels();
}











