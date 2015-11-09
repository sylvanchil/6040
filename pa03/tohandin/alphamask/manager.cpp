#include"manager.h"
#include"imageprocess.h"

void Manager::setParam(bool pf, bool sf, float k, char* inamea, char* inameb){
	pvFlag = pf;
	ssFlag = sf;
	pvK = k;
	inputFilenameA = new char[sizeof(inamea)+1];
	strcpy(inputFilenameA, inamea);
	inputFilenameB = new char[sizeof(inameb)+1];
	strcpy(inputFilenameB, inameb);

}


bool Manager::parseArgs(int argc, char** argv){
	bool pf = false;
	bool sf = false;
	float k = 0.5;
	char* inamea;
	char* inameb;

	//record the number of filename 
	int filenameCount=0;

	for(int i = 1; i!= argc; i++){
		if(argv[i][0]=='-'){
			if(0==strcmp(argv[i], "-pv")){
				pf = true; 
			}else if(0==strcmp(argv[i], "-ss")){
				sf = true;
			}else if(0==strcmp(argv[i], "-k")){
				if(i == (argc-1)){
					return false;
				}
				i++;
				try{
					k = atof(argv[i]);
					throw 1;
				}
				catch(int e){
					return false;
				}
			}else{
				return false;
			}
		}

		else{
			if(filenameCount ==0){
				inamea = new char[sizeof(argv[i])+1];
				strcpy(inamea, argv[i]);
				filenameCount++;
			} else if(filenameCount ==1){
				inameb = new char[sizeof(argv[i])+1];
				strcpy(inameb, argv[i]);
				filenameCount++;
			} else {
				return false;
			}
		}
	}
	
	if(filenameCount<2){
		return false;
	}
	setParam(pf,sf,k, inamea,inameb);
	return true;
}


void Manager::helpInfo(){
	std::cout << 	"usage: "
		<<	"\n\talphamask file1 file2"
		<<	 "\n\talphamask -pv file1 file2"
		<<	"\n\talphamask -ss file1 file2"
		<<	"\n\talphamask -pv -ss file1 file2"
		<< std::endl;

}

void Manager::run(){
	MyImage inputImage;

//read from file
	if(!FileIO::getInstance().readFromFileToImage(inputImage,inputFilenameA )){
		exit(-1);	
	}
//to 4channels image 
	MyImage imageWithAlplaMask(inputImage.to4ChannelsImage());

	

	ImageProcess ip;
	ip.setAlpha(imageWithAlplaMask, pvFlag, ssFlag);
	
	if(!FileIO::getInstance().writeImageToFile(imageWithAlplaMask,inputFilenameB)){
		exit(-1);
	}

}
































