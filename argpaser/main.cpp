#include"argparser.h"
#include<cstdio>
int main(){
	ArgParser ap;
	ap.addArg("-g");
	ap.addArg("-c");
	if(ap.hasArg("-g")){
		printf("has -g\n");
	}else{
		printf("does no have -g\n");
	}
	if(ap.hasArg("-b")){
		printf("has -b\n");
	}else{
		printf("does no have -b\n");
	}
	if(ap.hasArg("-c")){
		printf("has -c\n");
	}else{
		printf("does no have -c\n");
	}
}
