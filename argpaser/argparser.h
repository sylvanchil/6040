#include<vector>
#include<algorithm>
class ArgParser{
public:
	bool parseArg(int argc, char* argv){
		//to do
		return true;
	}
	void addArg(char* argname){
		argsList.push_back(argname);	
	}
	bool hasArg(char* arg){
		return find(argsList.begin(), argsList.end(), arg)=argsList.end();
	}

private:
	std::vector<char*> argsList;	
};

