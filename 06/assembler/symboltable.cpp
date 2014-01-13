#include "symboltable.h"
#define ERR_NOT_EXIST 0; // memory address 0x0

SymTable::SymTable(){
	m_addr = 16; //first available memory address
	Init(); // initilize predefined symbols
}

SymTable::~SymTable(){}

//initilize predefined symbos
void SymTable::Init()
{
	m_mEntry["R0"] = 0;
	m_mEntry["R1"] = 1;
	m_mEntry["R2"] = 2;
	m_mEntry["R3"] = 3;
	m_mEntry["R4"] = 4;
	m_mEntry["R5"] = 5;
	m_mEntry["R6"] = 6;
	m_mEntry["R7"] = 7;
	m_mEntry["R8"] = 8;
	m_mEntry["R9"] = 9;
	m_mEntry["R10"] =10;
	m_mEntry["R11"] =11;
	m_mEntry["R12"] =12;
	m_mEntry["R13"] =13;
	m_mEntry["R14"] =14;
	m_mEntry["R15"] =15;
	
	m_mEntry["SP"] = 0;
	m_mEntry["LCL"] = 1;
	m_mEntry["ARG"] = 2;
	m_mEntry["THIS"] = 3;
	m_mEntry["THAT"] =4;

	m_mEntry["KBD"] =24576;
	m_mEntry["SCREEN"] =16384;
}
void SymTable::Add(string entry)
{
	m_mEntry[entry] = m_addr;
	m_addr++;
}

void SymTable::AddSym(string entry, int instaddr)
{
	m_mEntry[entry] = instaddr;
}

string SymTable::Value(string key)
{
	string bs; //binary string
	if(Exist(key))
		bs = Code::DecToBin(m_mEntry[key]);
		return bs;
	return ERR_NOT_EXIST;
}

//is the key exist?
bool SymTable::Exist(string key)
{
	if(m_mEntry.count(key) == 0)
		return false;
	else
		return true;
}
