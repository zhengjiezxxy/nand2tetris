//Author: Jack Chin
//Date: 25/11/2013

#include <iostream>



Parser::Parser(){}

Parser::Parser(ifstream ifs):m_ifs(ifs){}

Parser::hasNext(){
	return m_ifs::good();
}

Parser::advance(){
	m_ifs >> m_rawString;
	if(*m_rawString=="\n" ||(*m_rawString++=="/" && \
		*(m_rawString+1)=="/")){
		advance();
	}
		
}

bool Parser::ACom(){
	return *m_rawString == "@";
}

bool Parser::CCom(){
	return *m_rawString != "@" && *m_rawString !="(";
}

bool Parser::LCom(){
	return *m_rawString == "(";
}

stirng dest(){
	if(CCom){
		return m_dest;
	}
}

string comp(){
	if(CCom){
		return m_comp;
	}
}

string jmp(){
	if(CCom){
		return m_jmp;
	}
}

string address(){
	if(ACom){
		return m_address;
	}
}

void analyze(){
	char * tmp = m_rawString;
	if(ACom){
		tmp++;
		while(*tmp != '\0'){
			m_address+=*tmp++;
		}
	}

	if(CCom){
		while(*tmp != "="){
			m_dest += *tmp++;
		}
		tmp++;
		while(*tmp != ";"){
			m_comp += *tmp++;
		}
		tmp++;
		while(*tmp != "\b"){
			m_comp += *tmp++;
		}
	}

//TODO LCom

			
	


	
	
	
	
