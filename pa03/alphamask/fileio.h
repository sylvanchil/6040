/*
*  name: cong qiu
*  email: congq@g.clemson.edu
*  date: Sep, 30th, 2015
*/

#include"myimage.h"

class FileIO{
public:
	static FileIO& getInstance();
	bool readFromFileToImage(MyImage& my, char* filename);
	bool writeImageToFile(const MyImage& my, char* filename);


private:
	FileIO();
	FileIO(const FileIO& fi);
};

