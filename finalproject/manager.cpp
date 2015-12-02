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
}

bool Manager::save(){
	//save the current result
	if(!FileIO::getInstance().writeImageToFile(resultImage,resultFilename)){
		return false;
	}
	return true;
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

void Manager::display(unsigned char* des){
	resultImage.displayOutput(des);
}

void Manager::prepare(int& w, int& h, int& c){
	//set weight height channels for displaying
	w = originImage.getWidth();
	h = originImage.getHeight();
	c = originImage.getChannels();
}

void Manager::adjustBrightness(){
	ip.adjustBrightness(resultImage, resultImage, 0.1);
	historyImages.push_back(MyImage(resultImage));
}
void Manager::adjustSaturation(){
	ip.adjustSaturation(resultImage, resultImage, 0.1);
	historyImages.push_back(MyImage(resultImage));

}
void Manager::adjustContrast(){
	ip.adjustContrast(resultImage, resultImage, 0.1);
	historyImages.push_back(MyImage(resultImage));
}


void Manager::adjustWhitebalance(){
	ip.adjustWhitebalance(resultImage, resultImage, -0.01);
	historyImages.push_back(MyImage(resultImage));

}

void Manager::adjustHighlight(){
	ip.adjustHighlight(resultImage,resultImage, 0.1);
	historyImages.push_back(MyImage(resultImage));
}
void Manager::adjustShadow(){
	ip.adjustShadow(resultImage,resultImage, 0.1);
	historyImages.push_back(MyImage(resultImage));
}







