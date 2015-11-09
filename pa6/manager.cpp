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

	int imageWidth= originImage.width;
	int imageHeight= originImage.height;
	int imageChannels= originImage.channels;

	Vector3d topleft(0,0,1);
	Vector3d topright(imageWidth,0,1);
	Vector3d buttomleft(0,imageHeight,1);
	Vector3d buttomright(imageWidth,imageHeight,1);

	Vector3d newTopLeft(matrix3 * topleft); 
	Vector3d newTopRight(matrix3 * topright); 
	Vector3d newButtomLeft(matrix3 * buttomleft); 
	Vector3d newButtomRight(matrix3 * buttomright); 

	cout << newTopLeft<< endl;
	cout << newTopRight << endl;
	cout << newButtomLeft << endl;
	cout << newButtomRight << endl;

	//initialize the result image
	resultImage = originImage;
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

void Manager::display(unsigned char* des){
	resultImage.displayOutput(des);
}

void Manager::prepare(int& w, int& h, int& c){
	//set weight height channels for displaying
	w = originImage.getWidth();
	h = originImage.getHeight();
	c = originImage.getChannels();
}

