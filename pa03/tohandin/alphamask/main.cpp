/*	name: cong qiu
 *	email: congq@g.clemson.edu
 *  date: 7th Sep 2015
 */
#include<OpenImageIO/imageio.h>
OIIO_NAMESPACE_USING
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<string>
#include<algorithm>
#include<iostream>
#include<vector>
#include"manager.h"


Manager manager;

int main(int argc, char** argv){
	
	if(!manager.parseArgs(argc, argv)){
		manager.helpInfo();	
		exit(-1);
	}

	manager.run();
	return 0;

}



