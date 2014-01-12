//main module
//Author: Jack Chin
//Date: 25/11/2013

#include <fstream>
#include <string>
#include "code.h"
#include "parser.h"
using namespace std;

int main(int argc, char* argv[]){
	ifstream ifs;
	ofstream ofs;
	ofs.open(argv[2],std::ifstream::app);
	
	Parser parser;
	parser.m_ifs.open(argv[1],std::ifstream::in);
	Code code ;
	
	while(parser.HasNext()){
		parser.Advance();
		switch(parser.Type()){
			case 0 :
				ofs << "0"<< code.Addr(parser.Addr()) << std::endl;
				break;
			case 1 :
				ofs <<"111" <<  code.Comp(parser.Comp())+code.Dest(parser.Dest()) \
						+code.Jmp(parser.Jmp()) << std::endl;
				break;
		}
	}
}
				
		
