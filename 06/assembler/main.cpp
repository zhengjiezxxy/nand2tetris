//main module
//Author: Jack Chin
//Date: 25/11/2013

#include <fstream>
#include <string>
#include "code.h"
#include "parser.h"
#include "symboltable.h"
using namespace std;

int main(int argc, char* argv[]){
	ifstream ifs;
	ofstream ofs;
	ofs.open(argv[2],std::ifstream::app);
	
	Parser parser;
	parser.m_ifs.open(argv[1],std::ifstream::in);
	Code code ;
	SymTable symTab;
	
	//first pass to establish symbol table in label command
	while(parser.HasNext())
	{
		parser.Advance();
		switch(parser.Type()){
			case 2:
				symTab.AddSym(parser.Sym(),parser.m_line);
			default:
				break;
		}
	}

	//second pass to establish label defined in the A command
	parser.m_ifs.close();
	parser.m_ifs.open(argv[1],std::ifstream::in);
	parser.m_line = 0;
	while(parser.HasNext())
	{
		parser.Advance();
		switch(parser.Type()){
			case 0:
				if(parser.ASym())
				{
					if(!symTab.Exist(parser.Addr()))
						symTab.Add(parser.Addr());
				}
			default:
				break;
		}
	}

	parser.m_ifs.close();
	parser.m_ifs.open(argv[1],std::ifstream::in);
	parser.m_line = 0;
	while(parser.HasNext()){
		parser.Advance();
		switch(parser.Type()){
			case 0 :
				if(symTab.Exist(parser.Addr()))
			   		ofs << "0" << symTab.Value(parser.Addr()) << std::endl;
				else
					ofs << "0"<< code.Addr(parser.Addr()) << std::endl;
				break;
			case 1 :
				ofs <<"111" <<  code.Comp(parser.Comp())+code.Dest(parser.Dest()) \
						+code.Jmp(parser.Jmp()) << std::endl;
				break;
			default: 
				break;
		}
	}
}
				
		
