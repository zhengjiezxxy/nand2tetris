//Date: 03/12/2013
//Author: Jack Chin
//For: turn assembly code into binary code for exceution
#include "code.h"
#include <string>
#include <cstdlib>
#include <iterator>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

Code::Code(){init();}

Code::~Code(){}

void Code::init(){  // establish four maps

	//open files
	ifstream ifs_comp("comp.ini",std::ios::in);
	ifstream ifs_dest("dest.ini",ios::in);
	ifstream ifs_jmp("jmp.ini",ios::in);

	string s;

	//construct comp map
	while(getline(ifs_comp,s,'\n'))
	{
		Tab2Space(s);
		vector<string> vec = Split(s);
		m_MapComp[vec[0]] = vec[1]; //key and value
	}

	//construct jmp map
	while(getline(ifs_dest,s,'\n'))
	{
		Tab2Space(s);
		vector<string> vec = Split(s);
		m_MapDest[vec[0]] = vec[1]; //key and value
	}

	//construct jmp map
		
	while(getline(ifs_jmp,s,'\n'))
	{
		Tab2Space(s);
		vector<string> vec = Split(s);
		m_MapJmp[vec[0]] = vec[1]; //key and value
	}
}

//helper function 
// convert tab to space
void Code::Tab2Space(string s)
{
	replace(s.begin(),s.end(),'\t',' ');
}


vector<string> Code::Split(string s)
{
	vector<string>  vecRes;
	istringstream iss(s);
	copy(istream_iterator<string>(iss),istream_iterator<string>(),\
			back_inserter<vector<string> >(vecRes));
	if (vecRes.size()<2)
		vecRes.insert(vecRes.begin(),"");
	return vecRes;
}

//get the binary code
string Code::Dest(string s)
{
	if(s == "")
	return m_MapDest["NUL"];
	return m_MapDest[s];
}

//get the binary code
string Code::Jmp(string s)
{
	if(s == "")
	return m_MapJmp["NUL"];
	return m_MapJmp[s];
}

//get the binary code
string Code::Comp(string s)
{
	if(s == "")
	return m_MapComp["NUL"];
	return m_MapComp[s];
}		

string Code::Addr(string s)
{
	unsigned long ul=0;
	string bs; //binary string
	int n = s.size();
	bool digit=1;
	for(int i=0;i<n;++i)
	{
		if(!isdigit(s[i]))
			digit = 0;
			break;
	}
	
	if(digit&&n!=0)   //  prevent stoul collapse at alpha number
	ul = stoul(s);  // convert sting to unsigned long
	bs = DecToBin(ul);
	return bs;
}

string Code::Str(char* c)
{
	string s(c);
	return s;
}

string Code::DecToBin(unsigned long ul)
{	
	string s="";
	while(ul!=0)
	{
		s += (ul & 1)?'1':'0'; //c++ builtin bitwise operation
		ul >>= 1;
	}

	int n = s.size();
	for(int i=0;i<15-n;i++)
		s += '0';

	std::reverse(s.begin(),s.end());
	return s;
}	
