#include "./include/include.h"
#include "codewriter.h"
#ifndef PARSER_H
#include "parser.h"
#endif
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

	Parser parser; //ifstream has move constructor since c++11, I have
                 // g++ 4.6 only!
	CodeWriter writer;

	parser.m_ifs.open(sourcefile.c_str(),std::ios_base::in);
  writer.m_ofs.open(outfile.c_str(),std::ios_base::out);

	//initialization of parser and codewriter


	while(parser.HasNext())
	{
    trivec tvec = parser.Advance();
		writer.WriteCom(tvec);
	}

	return 0;
}
		

	

	
