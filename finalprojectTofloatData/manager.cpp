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
	char* tmpFilenameList[2];

	for(int i = 1; i!= argc; i++){

		if(fileCount <3){
			tmpFilenameList[fileCount] = argv[i];
			fileCount++;
		}else {
			return false;
		}
	}

	imageFilename= tmpFilenameList[0];
	if(fileCount==2){
		writeFlag= true;
		resultFilename = tmpFilenameList[1];
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
	originImage = originImage.to4ChannelsImage();
	resultImage = originImage;
	historyImages.push_back(MyImage(resultImage));
	float* maskData = new float[resultImage.width* resultImage.height];
	for(int i = 0; i!= resultImage.width* resultImage.height; i++){
		maskData[i] = 0.0;
	}
	maskImage = MyImage(resultImage.width, resultImage.height, 1,maskData );

}

bool Manager::save(){
	//save the current result
	if(!FileIO::getInstance().writeImageToFile(resultImage,resultFilename)){
		return false;
	}
	return true;
}

void Manager::savemask(){
	char maskimagename[] = "masked.jpg";
	FileIO::getInstance().writeImageToFile(maskImage,maskimagename);
}

void Manager::resetImage(){
	//reset the image to original Image
	resultImage = originImage;
	historyImages.clear();
	historyImages.push_back(MyImage(resultImage));
}

void Manager::undo(){
	//todo 
	if(historyImages.size()>1){
		historyImages.pop_back();
		if(!historyImages.empty())
			resultImage= historyImages.back();
	}
}

bool Manager::canWrite(){
	//there are output filename
	return writeFlag;
}

void Manager::display(float* des){
	resultImage.displayOutput(des);
}

void Manager::displayOriginal(float* des){
	originImage.displayOutput(des);
}

void Manager::prepare(int& w, int& h, int& c){
	//set weight height channels for displaying
	w = originImage.getWidth();
	h = originImage.getHeight();
	c = originImage.getChannels();
}

void Manager::setMode(int i){
	if(i < '7' && i > '0'){
		mode = i-48;
	}
}

void Manager::addBrushPaint(int x, int y){
	ip.brushMaskImage(maskImage, x ,y, rSolid, rFading);
}


void Manager::setUseBrush(int i){
	useBrush= i;
	if(i == 0){
		for(int i = 0; i!= resultImage.width* resultImage.height; i++){
			maskImage.data[i] = 1;
		}
	}
	else{
		for(int i = 0; i!= resultImage.width* resultImage.height; i++){
			maskImage.data[i] = 0;
		}

	}
}

void Manager::magBrush(){
	rSolid*=1.11;
	rFading*=1.11;

}
void Manager::minBrush(){
	rSolid*=0.9;
	rFading*=0.9;
}

void Manager::magFading(){
	rFading *=1.1;
}

void Manager::minFading(){
	rFading*=0.9;
	if(rFading < rSolid){
		rFading= rSolid;
	}	
}


void Manager::adjust(double value){
	//std::cout << "adjusting " << mode  << std::endl;
	switch(mode){
		case 1:
			ip.adjustBrightness(resultImage, maskImage, value);
			break;
		case 2:
			ip.adjustSaturation(resultImage, maskImage, value);
			break;
		case 3:

			ip.adjustHighlight(resultImage,maskImage, value);
			break;
		case 4:
			ip.adjustShadow(resultImage,maskImage, value);
			break;
		case 5:
			ip.adjustWhitebalance(resultImage, maskImage, value);
			break;
		case 6:
			ip.adjustContrast(resultImage, maskImage,value);
			break;
	}

	historyImages.push_back(MyImage(resultImage));

}






