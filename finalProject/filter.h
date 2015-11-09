/************************************
*    name: cong qiu                 *
*    email: congq@g.clemson.edu     *
*    date: OCT, 4th, 2015           *
*************************************/

#ifndef FILTER_H_
#define FILTER_H_

#include<cstdlib>
#include<cstring>

class Filter{
private:
	int size;
	int sumType;
	float* value;
public:
	Filter():
		size(0),
		sumType(0),
		value(new float[0]){
		
	}
	Filter(const Filter& f):
		size(f.size),
		sumType(f.sumType),
		value(new float[size*size])
	{
		memcpy(value, f.value, size* size* sizeof(float));		
	}
	Filter& operator=(const Filter& f)
	{
		if(&f == this){
			return *this;
		}
		delete value;
		size = f.size;
		sumType = f.sumType;
		value= new float[size*size];
		memcpy(value, f.value, size*size*sizeof(float));	
		return *this;
	}
	Filter(int s,int t, float* v) :
		size(s),
		sumType(t),
		value(new float[s*s]){
		memcpy(value, v, s*s*sizeof(float));
	}
	float valueAt(int x, int y){
		return (y*size+x);
	}
	int type(){
		return sumType;
	}
	~Filter(){
		delete value;
	};

	friend class FileIO;
	friend class ImageProcess;
};

#endif
