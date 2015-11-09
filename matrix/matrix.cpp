#include"matrix.h"

void Matrix::printData(){
	for(int y = 0;y != height;y++){
		for(int x=0;x != width; x ++){
			std::cout << data[y*width + x] << "\t" ;
		}
	
		std::cout << std::endl;	
	}

}








