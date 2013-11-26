//main module
//Author: Jack Chin
//Date: 25/11/2013

int main(int argc, String[] argv){
	File* pFile = fopen(argv[1],"r");
	File* pOutFile = fopen(argv[2],"a");
	Parser parser = new Parser(pFile);
	Code code = new Code();
	while(parser.hasNext()){
		parser.advance();
		switch(parser.type()){
			case 1 :
				printf(code.address(parser.address())+"\n",pOutFile);
			case 2 :
				printf(code.dest(parser.dest())+code.comp(parser.comp()) \
						+code.jmp(code.jmp())+\n",pOutFile);
		}
	}
}
				
		
