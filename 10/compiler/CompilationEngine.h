// Arthor: Jack Chin
// Date: 10/02/2014

#include "include/include.h"
#ifndef JACKTOKENIZER_H
	#include "JackTokenizer.h"
#endif

class CompilationEng
{
public:
	 CompilationEng();
	~CompilationEng();
	void compileClass();
	void compileClassVarDec();
	void compileSubroutine();
	void compileParameterList();
	void compileSubroutineBody();
	void compileVarDec();
	void compileStatements();
	void compileDo();
	void compileLet();
	void compileWhile();
	void compileReturn();
	void compileIf();
	void compileExpression();
	void compileTerm();
	void compileExpressionList();
	void compileSubroutineCall();
	//if get == true; call getToken()
	// m_token m_tokenType numOfTab before call this function
	void printCurrentToken(bool get=true);										
	void printToken(string s);
	//bool start is start nonterminal(<nonterminal> not </nonterminal>)
	void printNonterminal(string noterminal,bool start=true); //print nonterminal 
	void getToken(); //get token from tokenizer and give it to compilationEngine
	//paraList==true print ParameterList
	void printMultipleVarDec(); //this function is a recursive function
	void printMultipleParameterList(); //print multiple parameterlist
	void init(); //initiation of tokenizer

public:
	ofstream m_ofs; //output stream
	std::set<char> m_sOp; //operator set
	const char* m_sifs; //input file path
	string m_token; //current token
	string m_tokenType;
	int numOfTab; //print how many tabs everyline.
	bool m_bPutback; //need putback m_token;
	Tokenizer tokenizer;
	std::vector<string> stringStack; //store string temporarily
};
