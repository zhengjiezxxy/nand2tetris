//main module
//Author: Jack Chin
//Date: 25/11/2013

#include <fstream.h>

int main(int argc, String[] argv){
	ifstream ifs;
	ofstream ofs;
	ifs.open(argv[1],std::ifstream::in);
	ofs.open(argv[2],std::ifstream::app);
	
	Parser parser = new Parser(ifs_in);
	Code code = new Code();
	
	while(parser.hasNext()){
		parser.advance();
		switch(parser.type()){
			case 1 :
				ofs << code.address(parser.address()) << std::endl;
			case 2 :
				ofs << code.dest(parser.dest())+code.comp(parser.comp()) \
						+code.jmp(code.jmp())+\n" << std::endl;
		}
	}
}
				
		
