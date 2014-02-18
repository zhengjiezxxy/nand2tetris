#include "./include/include.h"
#define PARSER_H
typedef	pair<string,pair<string,string> > trivec; 

class Parser
{
public:
	Parser();
	~Parser();

	//three element vector, the first one is the command
	//the second and third are arguments

	trivec Advance(); //return trivec perline
	bool HasNext();  // 

public:
	string m_sCom;  //command element of trivec
	string m_sArg1; //argument 1
	string m_sArg2;
	ifstream m_ifs; 
	set<string> m_set;  // segements set
	trivec m_trivec;
};
