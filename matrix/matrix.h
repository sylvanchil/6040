#include<vector>
#include<iostream>
#include<cstring>

class Matrix{
public:

	Matrix():width(0),height(0),data(new float[0]){
	}
	Matrix(int w, int h,float* d):width(w),height(h),data(new float[w*h]){
		memcpy(data, d, w*h* sizeof(float));
	
	}
	Matrix(const Matrix& m): width(m.width), height(m.height), data(new float[width*height]){}

	~Matrix(){
		delete data;
	};

	void printData();
	Matrix operator*(const Matrix& m);
	Matrix operator*(int n);
	Matrix operator+(const Matrix& m);
	Matrix inverse();

private:
	int width;
	int height;
	float* data;

};
