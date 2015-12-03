#include<cstdlib>
#include<string>
int main(int argc, char**  argv){	
	std::string s1 = "git add -A && git commit -m ";
	std::string s2 (argv[1]);
	s1 += s2;
	s1 += " && git push 6040original master";
	system(s1.c_str());
	return 0;
}
