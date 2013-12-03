//Author: Jack Chin
//Date: 03/12/2013

#include "code.h"
#include <string>

Code::Code(){};

Code::init(){
	ifstream ifs_comp,ifs_dest,ifs_jmp;
	string s;
	do
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
