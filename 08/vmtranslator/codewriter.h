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
#define TEMP(x) 5+(x)

class CodeWriter
{

public:
	CodeWriter();
	~CodeWriter();

	void WriteCom(trivec tvec);
  //push num to stack ,excluding get the num
  void PushToStack();
  //get value from stack *(sp-1) not change *(SP)
  void GetFromStack();
  // push back stack pointer back one step
  void BackOneStep();
  //get value from segement, is the Segement const
  //if reverse == true , put value onto segement
  void GetValueFromSegment(bool reverse=false);
  bool IsNum(string s);
  void Init();


public:
	string m_sCom; //command 
	string m_sArg1; //argument 1
    string m_sArg2; //argument 2
  ofstream m_ofs;   // output stream
  int m_truetag;
  int m_endtag;
  bool bConst;  // const segment
  bool bStatic;  // static segment
  bool bTemp;  // temp segment
  bool bArg;
  bool bPointer;
  std::map<string,string> m_mMacroSeg; //map "this that argument local" segment to Macro name
};

