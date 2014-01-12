//the implementation of parser for the assembler
//Author: Jack Chin
//Data: 25/11/2013

#include <string>
#include <fstream>
using namespace std;

class Parser{
public:
	Parser();
	~Parser();
 
	int Type();  // 0-ACom; 1-CCom; 2-LCom
	bool HasNext();   //whether reach the EOF
	bool ACom();      //if this command a A type command?
	bool CCom();	  //if this command a C type command?
	bool LCom(); 	  //if this command a Label?
	void Advance();		  //advance to next setence if there is another command.
	string Dest();	  //return the dest string
	string Comp();	  //return the compare string
	string Jmp();	  //return the jump string

	string Addr(); //return address string of A type command

public:
	string m_rawString;      //every line excluding the comment
	string m_comp;
	string m_dest;
	string m_jmp;
	string m_address;
	void analyze();

public:
	ifstream m_ifs;  // source code input stream
};
	
	
