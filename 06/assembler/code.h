//implementation of code module for the assembler
//Author: Jack Chin
//Date: 25/11/2013

#include <string>
#include <vector>
#include <map>
using namespace std;

class Code{
public:
	Code();
	void init();  //establish four maps from file
	~Code();
	map<string,string> m_MapComp; // compare map
	map<string,string> m_MapJmp; // Jump Map
	map<string,string> m_MapDest; // Destionation map
	string Dest(string s); // get binary code
	string Jmp(string  s); // get binary code
	string Comp(string s); // get bianry code
	string Addr(string s); //get binary address
	void Tab2Space(string s); // helper function
	std::vector<string> Split(string s); // split a string into parts by space(std::isspace())
	string Str(char* c);  //helper function for debugging
	string DecToBin(unsigned long l); // convert decimal to binary string
};
