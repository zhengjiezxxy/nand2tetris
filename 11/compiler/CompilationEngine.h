// Arthor: Jack Chin
// Date: 10/02/2014

#include "include/include.h"
#ifndef JACKTOKENIZER_H
	#include "JackTokenizer.h"
#endif

#ifndef SYMBOLTABLE_H
	#include "SymbolTable.h"
#endif

#ifndef VMWRITER_H
	#include "VMWriter.h"
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


	//writer related helper function
	void writePush(string identifier);
	void writePop(string identifier);

public:
	ofstream m_ofs; //output stream
	ofstream m_vmofs;//vm output stream
	std::set<char> m_sOp; //operator set
	std::map<string,string> mapOp; //operator map +->add

	////vm writer related variable
	VMWriter writer;
	const char* m_sifs; //input file path
	string className; //
	string functionName;
	string functionType;
	int nLocals;
	int nClassField;
	int nArgs;
	int iftag;
	int whiletag;

	/////symbol table related variable
	SymbolTable symT;
	string m_token; //current token
	string m_tokenType;
	string m_idType; //int string and so on
	string m_idKind; //var arg static field
	string letleftType;
	bool bType;

	////xml output related
	int numOfTab; //print how many tabs everyline.
	bool m_bZeroStatements; //zero statements
	bool m_bPutback; //need putback m_token;
	bool bInClass; //class scope
	bool bInSubroutine; //method scope
	bool bAtSubroutine; //subroutine name
	Tokenizer tokenizer;
	string stringStack; //store string temporarily
};
