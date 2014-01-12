//Author: Jack Chin
//Date: 25/11/2013

#include "parser.h"
#define E_NO_INPUT 0

Parser::Parser(){}

Parser::~Parser(){}

bool Parser::HasNext(){
	return m_ifs.good();
}

void Parser::Advance(){
	getline(m_ifs,m_rawString,'\n');
	while(m_rawString[0]=='\n'||m_rawString[0]=='\r' ||(m_rawString[0] =='/' && \
		m_rawString[1]=='/')){
		getline(m_ifs,m_rawString,'\n');	
}
	analyze();
		
}

bool Parser::ACom(){  //A Type Command
	if(m_rawString.size()>0)
	return m_rawString[0] == '@';
	return E_NO_INPUT;
}

bool Parser::CCom(){ // C Type Command
		if(m_rawString.size()>0)
	return m_rawString[0] != '@' && m_rawString[0] !='(';
	return E_NO_INPUT;
}

bool Parser::LCom(){ // Label
	if(m_rawString.size()>0)
	return m_rawString[0] == '(';
	return E_NO_INPUT;
}

string Parser::Dest(){
	if(CCom()){
		return m_dest;
	}
	return "";
}

string Parser::Comp(){
	if(CCom()){
		return m_comp;
	}
	return "";
}

string Parser::Jmp(){
	if(CCom()){
		return m_jmp;
	}
	return "";
}

string Parser::Addr(){
	if(ACom()){
		return m_address;
	}
	return 0;
}

void Parser::analyze(){
	m_address.clear();
	m_comp.clear();
	m_dest.clear();
	m_jmp.clear();   //clear previous anlysis results
	
	string tmp = m_rawString;
	if(ACom()){
		copy(tmp.begin()+1,tmp.end()-1,back_inserter(m_address));
	}

	if(CCom()){
		std::string::size_type n1 = tmp.find('=',0);  //dest subcommand end postion
		std::string::size_type n2 = tmp.find(';',0);  //jmp subcommand start postion
		if ( n1 != std::string::npos )
			copy(tmp.begin(),tmp.begin()+n1,back_inserter(m_dest));
		if ( n2 != std::string::npos )
			copy(tmp.begin()+n2+1,tmp.end()-1,back_inserter(m_jmp));  // end()-1 because has \r characters
		if ( n1==std::string::npos && n2 == std::string::npos)
			copy(tmp.begin(),tmp.end()-1,back_inserter(m_comp));
		else if( n1 != std::string::npos && n2 == std::string::npos)
			copy(tmp.begin()+n1+1,tmp.end()-1,back_inserter(m_comp));
		else if( n1 == std::string::npos && n2 != std::string::npos)
			copy(tmp.begin(),tmp.begin()+n2,back_inserter(m_comp));
		else 
			copy(tmp.begin()+n1+1,tmp.begin()+n2,back_inserter(m_comp));
	}
}

int Parser::Type()
{
	if(ACom()) return 0;
	if(CCom()) return 1;
//	if(LCom()) return 2;
	return 2;
}
//TODO LCom

