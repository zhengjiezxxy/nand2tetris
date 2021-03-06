#include "./include/include.h"
#define JACKTOKENIZER_H

class Tokenizer
{
public:
	Tokenizer();  //since there is no g++ 4.7, so there need a ifstream member variable.
	~Tokenizer();
	bool hasMoreToken();
	void advance();  // get next token from input stream and make it the current token.
	string tokenType(); 
	string tokenType(string s); //overloaded tokenType
	string keyWord(); // should be called when the tokentype is keyword
	char symbol(); // should be called when tokentype is symbol
	string identifier(); // should be called when tokentype is id
	int intVal(); // should be called when tokentype is int_const
	string stringVal(); //should be called when tokentype is string_const
	bool isDigit(); // is this token a digit string
	void printToken(); //print tokens one by one to the end;

public:
	ifstream m_ifs; //jack source file
	ofstream m_ofs; //jack output file
	set<char> m_sDelim; // delimiter set, including ' ', '\n', ';', '(', 
			//')', '+', '-', '*'
	string m_token; // current token
	set<string> m_sKeyword; //keyword set
	bool inComment; // /*  such comment */ or /** such comment */
	bool inComment1; // such comment
	bool inBlank; // is the inputstream process into blank zone
};
