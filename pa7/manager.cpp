/************************************
 *    name: cong qiu                 *
 *    email: congq@g.clemson.edu     *
 *    date: OCT, 4th, 2015           *
 *************************************/

#include"manager.h"
#include"colorwindow.h"

bool Manager::parseArgs(int argc, char** argv){
	//at least ./warp filename1
	if(argc < 2)
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
		//end of else
	}

	imageFilename = tmpFilenameList[0];

	if(fileCount==2){
		writeFlag= true;
		resultFilename = tmpFilenameList[1];
	}

	return true;

}
void Manager::takeMatrix(Matrix3x3 mat){

	for(int row = 0; row < 3; row++) {
		for(int col = 0; col < 3; col++) {
			matrix3[row][col] = mat[row][col];
		}
	}


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
	originImage = originImage.to4ChannelsImage();
	
	//initialize the result image
	resultImage = originImage;
	if(twrilModeOn){
		ip.inverseMapping(resultImage, strength, centerX , centerY);
	}	
	else{
		ip.inverseMapping(resultImage, matrix3, 0);
	}
//	save();

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

void Manager::turnTwrilModeOn(double s, double x,double y){
	twrilModeOn = true;
	strength = s;
	centerX = x;
	centerY = y;

}

void Manager::repairInverseMapping(){
	resultImage= originImage;
	ip.inverseMapping(resultImage, matrix3 ,1);
}



void Manager::display(unsigned char* des){
	resultImage.displayOutput(des);
}

void Manager::prepare(int& w, int& h, int& c){
	//set weight height channels for displaying
	w = resultImage.getWidth();
	h = resultImage.getHeight();
	c = resultImage.getChannels();
//	w = originImage.getWidth();
//	h = originImage.getHeight();
//	c = originImage.getChannels();
	
}

