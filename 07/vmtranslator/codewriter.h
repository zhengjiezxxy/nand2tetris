// Author: Jack Chin
// Date: 15/01/2014

#include "include/include.h"
#ifndef PASER_H
#include "parser.h"
#endif

#define SP 0
#define LCL 1
#define ARG 2
#define THIS 3
#define THAT 4
#define STATIC(x) 16+(x)

class CodeWriter
{

public:
	CodeWriter();
	~CodeWriter();

	void WriteCom(trivec tvec);
  bool IsNum(string s);
  void Init();


public:
	string m_sCom; //command 
	string m_sArg1; //argument 1
    string m_sArg2; //argument 2
  ofstream m_ofs;   // output stream
  int m_truetag;
  int m_endtag;
};

