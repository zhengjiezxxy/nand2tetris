//implemetation of a symtable for assembler
//Author: Jack Chin
//Date: 25/11/2013

#include <string>
#include <vector>
#include <map>
#ifndef CODE_H
	#include "code.h"
#endif
#include <cstdbool>
using namespace std;

class SymTable{
public:
	SymTable();
	~SymTable();
	void Init();  // init predefined symbols
	void Add(string entry);	// add an entry into the symboltable
	void AddSym(string entry, int instadd);  //
	string Value(string key);  // return the value of key s
	bool Exist(string key); // is the key exist?

protected:
	map<string,int > m_mEntry; 
	int m_addr;  // memory address allocated so far
};
	
