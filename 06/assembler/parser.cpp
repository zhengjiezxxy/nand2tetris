//Author: Jack Chin
//Date: 25/11/2013

#include "parser.h"
#define E_NO_INPUT 0
#define ERR_LEX -1

Parser::Parser(){m_line = 0;}

Parser::~Parser(){}

bool Parser::HasNext(){
	return m_ifs.good();
}

void Parser::Advance(){
	getline(m_ifs,m_rawString,'\n');
	m_rawString.erase(remove_if(m_rawString.begin(), m_rawString.end(), (int(*)(int))std::isspace), m_rawString.end());  //delete space
	
	while(m_rawString[0]=='\n'||m_rawString[0]=='\r' ||(m_rawString[0] =='/' && \
		m_rawString[1]=='/')){
		getline(m_ifs,m_rawString,'\n');	
}

	m_rawString.erase(remove_if(m_rawString.begin(), m_rawString.end(), (int(*)(int))std::isspace), m_rawString.end());  //delete space

	//delete comment after instrcutions
	//let's assume that there aren't any '/' in the symbols
	size_t n = m_rawString.find('/',0);
	if( n != std::string::npos)
		m_rawString.erase(m_rawString.begin()+n,m_rawString.end());
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

bool Parser::ASym()  //if A commnad has defined a new symbol
{
	int n = m_address.size();
	for(int i=0;i<n;++i)
	{
		if(!isdigit(m_address[i]))
	
		return 1;  //false
	}
	return 0; //true
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
	return "";
}

string Parser::Sym(){
	if(LCom())
		return m_sym;
	return "";
}

void Parser::analyze(){
	if(!LCom())
		m_line++; //line number = instruction address
	m_address.clear();
	m_comp.clear();
	m_dest.clear();
	m_jmp.clear();   //clear previous anlysis results
	m_sym.clear();
	
	string tmp = m_rawString;
	if(ACom()){
		copy(tmp.begin()+1,tmp.end(),back_inserter(m_address));
	}

	if(CCom()){
		std::string::size_type n1 = tmp.find('=',0);  //dest subcommand end postion
		std::string::size_type n2 = tmp.find(';',0);  //jmp subcommand start postion
		if ( n1 != std::string::npos )
			copy(tmp.begin(),tmp.begin()+n1,back_inserter(m_dest));
		if ( n2 != std::string::npos )
			copy(tmp.begin()+n2+1,tmp.end(),back_inserter(m_jmp));  // end()-1 because has \r characters
		if ( n1==std::string::npos && n2 == std::string::npos)
			copy(tmp.begin(),tmp.end()-1,back_inserter(m_comp));
		else if( n1 != std::string::npos && n2 == std::string::npos)
			copy(tmp.begin()+n1+1,tmp.end(),back_inserter(m_comp));
		else if( n1 == std::string::npos && n2 != std::string::npos)
			copy(tmp.begin(),tmp.begin()+n2,back_inserter(m_comp));
		else 
			copy(tmp.begin()+n1+1,tmp.begin()+n2,back_inserter(m_comp));
	}

	if(LCom())
		copy(tmp.begin()+1,tmp.end()-1,back_inserter(m_sym));
}

int Parser::Type()
{
	if(ACom()) return 0;
	if(CCom()) return 1;
	if(LCom()) return 2;
	return ERR_LEX;
}
//TODO LCom

