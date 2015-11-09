/************************************
*    name: cong qiu                 *
*    email: congq@g.clemson.edu     *
*    date: OCT, 4th, 2015           *
*************************************/

#include"myimage.h"
#include"filter.h"

class FileIO{
public:
	static FileIO& getInstance();
	bool readFromFileToImage(MyImage& my, char* filename);
	bool writeImageToFile(const MyImage& my, char* filename);
	bool readFromFileToFilter(Filter& f, char* filename);

private:
	FileIO(){}
	FileIO(const FileIO& fi);
};

