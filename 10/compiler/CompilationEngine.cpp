// Arthor: Jack Chin
// Date: 10/02/2014

#include "CompilationEngine.h"

CompilationEng::CompilationEng()
{
}

CompilationEng::~CompilationEng()
{}

void CompilationEng::compileClass()
{
	getToken();
	printNonterminal("class");
	numOfTab++;
	printCurrentToken(false); //<keyword> class </keyword>
	printCurrentToken(true); //<identifier> className </identifier>
	printCurrentToken(true);  //<symbol> { </symbol>
	compileClassVarDec();
	compileSubroutine();
	printCurrentToken(true); //<symbol> } </symbol>
	numOfTab--;
	printNonterminal("class",false); //end of class
}

void CompilationEng::compileClassVarDec()
{
	getToken();
	if(m_token == "static" || m_token == "field")
	{
		printNonterminal("classVarDec");
		numOfTab++;
		printCurrentToken(false); //<keyword> static|field </keyword>
		printCurrentToken(); //<keyword> type </keyword>
		printCurrentToken(); //<identifier> varName </identifier>
		printMultipleVarDec(); //;or ,varName,varName;
		numOfTab--; //restore format
		printNonterminal("classVarDec",false); //end of classVarDec
			
		//compile next classvardec
		compileClassVarDec();
	}
}

void CompilationEng::compileSubroutine()
{
	printNonterminal("subroutine");
	numOfTab++;
	while(true)
	{
		getToken();
		if(m_token == "}")
		{
			m_bPutback = true;
			break;
		}
		else
		{
			if(m_token == "constructor" || m_token == "function" ||
										m_token == "method")
			{
				printCurrentToken(false); //<keyword> constructor|function|method </keyword>
				printCurrentToken(true);  //<keyword> void|type </keyword>  void is also a keyword
				printCurrentToken(true);  //<symbol> subroutineName </keyword>
				printCurrentToken(true);  //<symbol> ( </symbol>
				compileParameterList();
				printCurrentToken(false); // <symbol> ) </symbol>
				compileSubroutineBody();
			}
		}
	}
	numOfTab--;
	printNonterminal("subroutine",false); //end of subroutine
}

void CompilationEng::compileParameterList()
{
	printNonterminal("parameterList");
	numOfTab++;
	printMultipleParameterList();

	numOfTab--;
	printNonterminal("parameterList",false); //end of parameterList
}	


void CompilationEng::compileSubroutineBody()
{
	getToken();
	printNonterminal("subroutineBody"); //<subroutine>
	numOfTab++;
	printCurrentToken(); //<symbol> { </symbol>
	compileVarDec();
	compileStatements();
	numOfTab--;
	printCurrentToken(); //<symbol> } </symbol>
	printNonterminal("subroutineBody",false); // end of subroutineBody
}

void CompilationEng::compileVarDec()
{
	getToken();
	printNonterminal("varDec");
	numOfTab++;
	printCurrentToken(false); //<keyword> var </keyword>
	printCurrentToken(); //<keyword> type </keyword>
	printCurrentToken(); //<id> varName </id>
	printMultipleVarDec();//<id> varName,varName </id>
	numOfTab--;
	printNonterminal("varDec",false); //end of varDec
}

void CompilationEng::compileStatements()
{
	printNonterminal("statements");
	numOfTab++;
	while(true)
	{
		getToken();
		if(m_token == "}")
		{
			m_bPutback = true;
			break;
		}
		else 
		{
			if(m_token == "let")
				compileLet();
			else if(m_token == "if")
				compileIf();
			else if(m_token == "while")
				compileWhile();
			else if(m_token == "do")
				compileDo();
			else if(m_token == "return")
				compileReturn();
		}
	}
	numOfTab--;
	printNonterminal("statements",false); //end of statements
}
	
void CompilationEng::compileLet()
{
	printNonterminal("letStatement");
	numOfTab++;
	printCurrentToken(false); //<keyword> let </kwyword>
	printCurrentToken(); //<id> varName </id>
	getToken();
	if(m_token == "[")
	{
		printCurrentToken(false); //<symbol> [ </symbol>
		compileExpression();
		printCurrentToken(); //<symbol> ] </symbol>
	}
	else
	{
		printCurrentToken(false); //<symbol> = </symbol>
		compileExpression();
		printCurrentToken(); //<symbol> ; </symbol>
	}

	numOfTab--;
	printNonterminal("letStatement",false);
}

void CompilationEng::compileDo()
{
	printNonterminal("doStatement");
	numOfTab++;
	printCurrentToken(false); //<keyword> do </keyword>
	compileSubroutineCall();
	numOfTab--;
	printNonterminal("doStatement",false);
}

void CompilationEng::compileIf()
{
	printNonterminal("ifStatement");
	numOfTab++;
	printCurrentToken(false); //<keyword> if </keyword>
	printCurrentToken(); //<symbol> ( </symbol>
	compileExpression();
	printCurrentToken(); //<symbol> ) </symbol>
	printCurrentToken(); //<symbol> { </symbol>
	compileStatements(); 
	printCurrentToken(); //<symbol> } </symbol>

	//else part
	getToken();
	if(m_token == "else")
	{
		printCurrentToken(false); //<keyword> else </keyword>
		printCurrentToken(); //<symbol> { </symbol>
		compileExpression(); 
		printCurrentToken(); //<symbol> } </symbol>
	}
	else
	{
		m_bPutback = true;
	}

	numOfTab--;
	printNonterminal("ifStatement",false);
}

void CompilationEng::compileWhile()
{
	printNonterminal("whileStatement");
	numOfTab++;
	printCurrentToken(false);//<keyword> while </keyword>
	printCurrentToken(); //<symbol> ( </symbol>
	compileExpression();
	printCurrentToken(); //<symbol> ) </symbol>
	printCurrentToken(); //<symbol> { </symbol>
	compileStatements();
	printCurrentToken(); //<symbol> } </symbol>

	numOfTab--;
	printNonterminal("whilestatement",false);
}

void CompilationEng::compileReturn()
{
	printNonterminal("returnStatement");
	numOfTab++;
	printCurrentToken(false); //<keyword> return </keyword>
	getToken();
	if(m_token == ";")
	{
		printCurrentToken(false); // <symbol> ; </symbol>
	}
	else 
	{
		m_bPutback = true;
		compileExpression();
		printCurrentToken(); // <symbol> ; </symbol>
	}

	numOfTab--;
	printNonterminal("returnStatement",false);//end of returnStatement
}

void CompilationEng::compileExpression()
{
	getToken();
	printNonterminal("expression"); //<expression>
	numOfTab++;
	compileTerm();
	while(true)
	{
		getToken();
		char c = m_token[0];
		if(m_sOp.count(c) >0)
		{
			printCurrentToken(false); //<symbol> op </symbol>
			compileTerm();
		}
		else
		{
			m_bPutback = true;
			break;
		}
	}
	numOfTab--;
	printNonterminal("expression",false);
}

void CompilationEng::compileTerm()
{
	getToken();
	printNonterminal("term");
	numOfTab++;

	if(tokenizer.tokenType() == "KEYWORD")
	{
		printCurrentToken(false); //<keyword> keyword </keyword>
	}
	else if(tokenizer.tokenType() == "STRINGCONST")
	{
		printCurrentToken(false);
	}
	else if(tokenizer.tokenType() == "INTCONST")
		printCurrentToken(false);
	else if(tokenizer.tokenType() == "SYMBOL")
	{
		if(m_token == "(") // (expression)
		{
			printCurrentToken(false);
			compileExpression();
		}
		else if(m_token == "-" || m_token == "~")
		{
			printCurrentToken(false); //<symbol> -|~ </symbol>
			compileTerm();
		}
	}
	else if(tokenizer.tokenType() == "IDENTIFIER")
	{
		stringStack.push_back(m_token);
		getToken();
		if(m_token == "[") //varName [ expression ]
		{
			printToken(stringStack[0]);
			printCurrentToken(false);
			compileExpression();
			printCurrentToken(); //<symbol> ] </symbol>
		}
		else if(m_token == "(" ) // subroutineCall
		{
			printNonterminal("subroutineCall");
			numOfTab++;
			printToken(stringStack[0]);
			printCurrentToken(false); //<symbol> ( </symbol>
			compileExpressionList();
			printCurrentToken();
			numOfTab--;
			printNonterminal("subroutineCall",false);
		}
		else if(m_token == ".") 
		{
			printNonterminal("subroutineCall");
			numOfTab++;
			printToken(stringStack[0]); //className
			printCurrentToken(false); //<symbol> . </symbol>
			printCurrentToken(); //<id> subroutineName </id>
			printCurrentToken(); //<symbol> ( </symbol>
			compileExpressionList();
			printCurrentToken(); //<symbol> ) </symbol>
			numOfTab--;
			printNonterminal("subroutineCall",false);
		}
		else  //varName 
		{
			m_bPutback = true;
		}
	}

	numOfTab--;
	printNonterminal("term",false); //end of term
}

void CompilationEng::compileSubroutineCall()
{
	printNonterminal("subroutineCall");
	numOfTab++;
	printCurrentToken(); //<id> </id>
	getToken();
	if(m_token == "(")
	{
		printCurrentToken(false); //<symbol> ( </symbol>
		compileExpressionList();
		printCurrentToken(); //<symbol> ) </symbol>
	}
	else if(m_token == ".")
	{
		printCurrentToken(false); //<symbol> . </symbol>
		printCurrentToken(); //<id> subroutineName </symbol>
		printCurrentToken(); //<symbol> ( </symbol>
		compileExpressionList();
		printCurrentToken(); //<symbol> ) </symbol>
	}
	numOfTab--;
	printNonterminal("subroutineCall",false);
}
void CompilationEng::compileExpressionList()
{
	printNonterminal("expressionList");
	numOfTab++;
	while(true)
	{
		getToken();
		if(m_token == ",")
		{
			printCurrentToken(false);
			compileExpression();
		}
		else if(m_token == ")")
		{
			m_bPutback = true;
			break;
		}
		else
		{
			m_bPutback = true;
			compileExpression();
		}
	}

	numOfTab--;
	printNonterminal("expressionList",false);
}



void CompilationEng::printCurrentToken(bool get)
{
	if(get)
	{
		getToken();
	}
	m_tokenType = tokenizer.tokenType();
	string s = m_tokenType;
	std::transform(s.begin(),s.end(),s.begin(),std::ptr_fun<int,int>(std::tolower));
	for(int i=0; i<numOfTab; ++i)
		m_ofs << "\t" ;
	m_ofs << "<" << s << ">" << m_token << "</" << s << ">" << endl;
}

void CompilationEng::printToken(string s)
{
	string tokenType = tokenizer.tokenType(s);
	std::transform(s.begin(),s.end(),s.begin(),std::ptr_fun<int,int>(std::tolower));
	for(int i=0; i<numOfTab; ++i)
		m_ofs << "\t";
	m_ofs << "<" << tokenType  << ">" << s << "</" << tokenType << ">" << endl;
}

															
void CompilationEng::printNonterminal(string nonterminal, bool isstart)
{
	for(int i=0;i<numOfTab;++i)
		m_ofs << "\t";
	if(isstart)
		m_ofs << "<" << nonterminal << ">" << endl;
	else 
		m_ofs << "</" << nonterminal << ">" << endl;
}
	
void CompilationEng::printMultipleVarDec()
{
	getToken();
	if(m_token == ";")
	{
		printCurrentToken(false); // "<symbol> ; </symbol>" 
	}
	else if(m_token == ",")
	{
		printCurrentToken(false); //"<symbol> , </symbol>"
		printCurrentToken(); //<identifier> varName </id>
		printMultipleVarDec();
	}
}

void CompilationEng::printMultipleParameterList()
{
	getToken();
	if(m_token == ")")
	{
		m_bPutback = true;
	}
	else if(m_token == ",")
	{
		printCurrentToken(false); //<symbol> , </symbol>
		printMultipleParameterList();
	}
	else
	{
		printCurrentToken(false); //<keyword> type </keyword>
		printCurrentToken(); //<id> varName </id>
		printMultipleParameterList();
	}
}
	


void CompilationEng::getToken()
{
	if(tokenizer.hasMoreToken())
	{

		if(!m_bPutback)
			tokenizer.advance();
			m_token = tokenizer.m_token;
	}
	m_bPutback = false;
}

void CompilationEng::init()
{
	m_sOp = {'+','-','/','*','&','|','<','>','='};
	numOfTab = 0;
	tokenizer.m_ifs.open(m_sifs,ios_base::in);
}
