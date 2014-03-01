// Arthor: Jack Chin
// Date: 09/02/2014
#include "JackTokenizer.h"

Tokenizer::Tokenizer()
{
	inBlank = false;
	inComment = false;
	inComment1 = false;
	m_sKeyword = {"class","method","function","constructor",
				"int","boolean","char","void","var","field","static",
				"let","do","if","else","while","return","true","false",
				"null","this"};

}

Tokenizer::~Tokenizer()
{}

bool Tokenizer::hasMoreToken()
{
	return m_ifs.good();
}

void Tokenizer::advance()
{
	char c;
	string tmpS="";
	m_token = "";
	m_ifs >> std::noskipws;
	while(m_ifs>> c)  //don't use >> operator
	{
		if( (c>= 'A' && c<='Z' ) ||(c >='a' && c <='z') ||(c>='0' && c<='9'))
		{
			if(inComment ||inComment1) //inComment /* */ inComment1 //
			{
				continue;
			}
			else
			{
				tmpS += c;
				continue;
			}
		}
		else if ( c == ' ' )
		{
			if( tmpS.size() >0)
			{
				m_token = tmpS;
				tmpS = "";
				return;
			}
			else
			{
				continue;
			}	
		}
		else if( c == '\r')
		{
			continue;
		}
		else if ( c == '\n')
		{
			if(inComment1) // needs special treatement
			{
				inComment1 = false;
				continue;
			}
			else 
				continue;
		}
		else if( c == '/')
		{
			if(!inComment && !inComment1)
			{
				m_ifs >> c;
				if(c == '/')
					inComment1 = true;
				else if(c == '*')
					inComment = true;
				else
					perror("not a correct comment");
			}
		}

		else if( c == '*')
		{
			if(inComment)
			{
				m_ifs >> c;
				if(c == '/')
				{
					inComment = false;
					continue;
				}
				else 
					continue;
			}
			else if(inComment1)
					continue;
			else //mult operator
			{
				if(tmpS.size() == 0)
				{
					m_token = c;
					return ;
				}
				else
				{
					m_ifs.putback(c);
					m_token = tmpS;
					tmpS = "";
					return;
				}
			}
		}

		else if ( std::ispunct(c)) 
		{
			if(inComment || inComment1)
				continue;
			else
			{
				if(tmpS.size() == 0)
				{
					m_token = c;
					return;
				}
				else
				{
					m_ifs.putback(c);
					m_token = tmpS;
					tmpS = "";
					return;
				}
			}
		}
	}
}

string Tokenizer::tokenType()
{
	if(!m_token.empty())
	{
	if(m_sKeyword.count(m_token) != 0)
		return "keyword";
	else if(std::ispunct(m_token[0]))
		return "symbol";
	else if(m_token.size() >0 && m_token[0] == '"')
		return "string_const";
	else if(isDigit())
		return "integerConstant";
	else 
		return "identifier";
	}
	else
		return "";
}

string Tokenizer::tokenType(string s)
{
	if(!s.empty())
	{
	if(m_sKeyword.count(s) != 0)
		return "keyword";
	else if(std::ispunct(s[0]))
		return "symbol";
	else if(s.size() >0 &&s[0] == '"')
		return "string_const";
	else if(isDigit())
		return "integerConstant";
	else 
		return "identifier";
	}
	else
		return "";
}

string Tokenizer::keyWord()
{
	if(m_token == "class")
		return "CLASS";
	else if(m_token == "method")
		return "METHOD";
	else if(m_token == "function")
		return "FUNCTION";
	else if(m_token == "constructor")
		return "CONSTRUCTOR";
	else if(m_token == "int")
		return "INT";
	else if(m_token == "boolean")
		return "BOOLEAN";
	else if(m_token == "char")
		return "CHAR";
	else if(m_token == "void")
		return "VOID";
	else if(m_token == "var")
		return "VAR";
	else if(m_token == "static")
		return "STATIC";
	else if(m_token == "field")
		return "FIELD";
	else if(m_token == "let")
		return "LET";
	else if(m_token == "do")
		return "DO";
	else if(m_token == "if")
		return "IF";
	else if(m_token == "else")
		return "ELSE";
	else if(m_token == "while")
		return "WHILE";
	else if(m_token == "return")
		return "RETURN";
	else if(m_token == "true")
		return "TRUE";
	else if(m_token == "false")
		return "FALSE";
	else if(m_token == "null")
		return "NULL";
	else if(m_token == "this")
		return "THIS";
	else 
		return "";
}

char Tokenizer::symbol()
{
	if(!m_token.empty())
	return m_token[0];
	return '\0';
}

string Tokenizer::identifier()
{
	return m_token;
}

int Tokenizer::intVal()
{
	int val,n;
	n = m_token.size();
	for(int i=0;i<n;i++)
	{
		char c = m_token[i];
		val += 10^(n-i-1)*((int)c);
	}

	return val;
}

string Tokenizer::stringVal()
{
	return m_token;
}

bool Tokenizer::isDigit()
{
	int n = m_token.size();
	for(int i=0;i<n;i++)
	{
		char c = m_token[i];
		if(!std::isdigit(c))
		return false;
	}
	if(n==0)
		return false;
	else 
		return true;
}

void Tokenizer::printToken()
{
	m_ofs << "<tokens>" << std::endl;
	string s,sType;
	while(hasMoreToken())
	{
		advance();
		s = tokenType();
		if(m_token != "") //excluding ending blank line and other
			m_ofs << "<" <<s << ">" 
			  <<" "<< m_token<< " " << "</"
			  << s << ">" << std::endl;
	}
	m_ofs << "</tokens>" << std::endl;
}

			
		
	
