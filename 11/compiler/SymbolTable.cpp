	// Arthor: Jack Chin
// Date: 02/03/14

#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
	bInClass = true;
	m_siArg = 0;
	m_siVar = 0;
	m_ciStatic = 0;
	m_ciField = 0;
}

SymbolTable::~SymbolTable()
{}

void SymbolTable::define(string name,string type,string kind)
{
	if(bInClass)  //class table
	{
		TABLEITEM ti;
		ti.type = type;
		ti.kind = kind;
		if(kind == "static")
			ti.index = m_ciStatic++;
		else if(kind == "field")
			ti.index = m_ciField++;
		else
			perror("classname subname shouldn't be defined");
		classSymTab[name] = ti;
	}
	else
	{
		TABLEITEM ti;
		ti.type = type;
		ti.kind = kind;
		if(kind == "arg")
			ti.index = m_siArg++;
		else if(kind == "var") 
			ti.index = m_siVar++;
		else
			perror("classname subname shouldn't be defined");
		subSymTab[name] = ti;
	}
}

int SymbolTable::varCount(string kind)
{
	int res;
	if(bInClass)
	{
		if(kind == "static")
			res = m_ciStatic?m_ciStatic-1:m_ciStatic;
		else if(kind == "field")
			res = m_ciField?m_ciField-1:m_ciField;
		else if(kind == "arg")
			res = m_ciArg?m_ciArg-1:m_ciArg;
		else if(kind == "var")
			res = m_ciVar?m_ciVar-1:m_ciVar;
		else
			perror("not a kind");
	}
	else
	{
		if(kind == "static")
			res = m_siStatic?m_siStatic-1:m_siStatic;
		else if(kind == "field")
			res = m_siField?m_siField-1:m_siField;
		else if(kind == "arg")
			res = m_siArg?m_siArg-1:m_siArg;
		else if(kind == "var")
			res = m_siVar?m_siVar-1:m_siVar;
		else
			perror("not a kind");
	}

	return res;
}

string SymbolTable::kindOf(string name)
{
	string kind;
	if(bInClass)
	{
		if(classSymTab.count(name) >0)
			kind = classSymTab[name].kind;
		else
			kind = "NOTDEFINED";
	}
	else
	{
		if(subSymTab.count(name)>0)
			kind = subSymTab[name].kind;
		else if(classSymTab.count(name)>0)
			kind = classSymTab[name].kind;
		else
			kind = "NOTDEFINED";
	}
	
	return kind;
}

string SymbolTable::typeOf(string name)
{
	string type;
	if(bInClass)
	{
		if(classSymTab.count(name) >0)
			type  = classSymTab[name].type;
		else
			type = "notdefined";
	}
	else
	{
		if(subSymTab.count(name)>0)
			type = subSymTab[name].type;
		else if(classSymTab.count(name)>0)
			type = classSymTab[name].type;
		else
			type = "notdefined";
	}
	
	return type;
}

int SymbolTable::indexOf(string name)
{
	int index;
	if(bInClass)
	{
		if(classSymTab.count(name) >0)
			index  = classSymTab[name].index;
		else
			index = INT_MAX;
	}
	else
	{
		if(subSymTab.count(name)>0)
			index = subSymTab[name].index;
		else if(classSymTab.count(name)>0)
			index = classSymTab[name].index;
		else
			index = INT_MAX;
	}
	
	return index;
}

bool SymbolTable::contain(string name)
{
	bool res;
	if(bInClass)
	{
		if(classSymTab.count(name) >0)
			res = true;
		else
			res = false;
	}
	else
	{
		if(subSymTab.count(name) > 0)
			res = true;
		else if(classSymTab.count(name)>0)
			res = true;
		else
			res = false;
	}
	return res;
}
