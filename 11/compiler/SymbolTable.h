// Arthour: Jack Chin
// Date: 02/03/2014

#include "include/include.h"
#define SYMBOLTABLE_H

class SymbolTable{
public:
	SymbolTable();
	~SymbolTable();

public:
	struct TABLEITEM{
		string type;
		string kind;
		int index;
	};
	void define(string name,string type,string kind);
	int varCount(string kind); //return the running index of type
	string kindOf(string name);
	string typeOf(string name);
	int indexOf(string name);
	bool contain(string name);

public:
	std::unordered_map<std::string,TABLEITEM> classSymTab;
	std::unordered_map<std::string,TABLEITEM> subSymTab;
	bool bInClass; //in the class scope?
	bool m_ciStatic; //index static  class Scope
	bool m_ciField;
	bool m_siArg;
	bool m_siVar;
};
