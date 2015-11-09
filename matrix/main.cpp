#include<iostream>
#include"matrix.h"


int main(){
	int w = 2;
	int h = 2;
	float data[]= {1,2,3,4};
	Matrix test(w,h, data);
	test.printData();
	return 0;
}
