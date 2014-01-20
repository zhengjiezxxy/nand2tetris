#include "./include/include.h"
#include "codewriter.h"
#include "parser.h"

int main(int argc, char* argv[])
{
	string sourcefile,outfile;
	if(argc < 2)
	{
		cout << "Usage tm [sourcefile] [outputfile]" << endl;
		cout << "Please input sourcefile name:";
		cin >> sourcefile;
		cout << "PLease input outputfile:" ;
		cin >> outfile;
	}
	else
	{
		string t1(argv[1]);
		string t2(argv[2]);  // convert char* to string
		sourcefile = t1;
		outfile = t2;
	}


	ifstream ifs(sourcefile.c_str(),std::ios_base::in);
	ifstream ofs(outfile.c_str(),std::ios_base::out);

	//initialization of parser and codewriter
	Parser parser(ifs);
	CodeWriter writer(ofs);


	while(parser.HasNext())
	{
		writer.WriteCom(parser.Advance());
	}

	return 0;
}
		

	

	
