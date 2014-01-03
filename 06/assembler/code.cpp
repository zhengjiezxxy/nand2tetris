//Author: Jack Chin
//Date: 03/12/2013
//Author: Jack Chin
//For: turn assembly code into binary code for exceution
#include "code.h"
#include <string>

Code::Code(){};

Code::init(){  // establish four maps
	ifstream ifs_comp,ifs_dest,ifs_jmp;

	//open files
	ifs_comp.open("./comp.ini",ios::in);
	ifs_dest.open("./dest.ini",ios::in);
	ifs_jmp.open("./jmp.ini",ios::in);

	//construct comp map
	std::foreach(std::istream_iterator(ifs),\
					std::istream_iterator(),\
						SplitAndFill());  //todo 	
	string s;
		ifs_comp.getline(s);	
		string key =value= "";
		int i;
		for(i=0;s[i]!='\b'||s[i]!='t';i++)
				key += s[i];
		for(;s[i]!='\n';i++){
				if(s[i] !='\b' ||s[i] != '\t')
					value += s[i];
		}
		m_MapComp[key] = value;

		//todo dest jmp
