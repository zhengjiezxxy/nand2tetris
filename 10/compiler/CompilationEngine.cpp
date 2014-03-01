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
	while(true)
	{
		getToken();
		if(m_token == "constructor" ||m_token == "function" ||m_token == "method")
		{
			m_bPutback = true;
			break;
		}
		else if(m_token == "static" || m_token == "field")
		{
			printNonterminal("classVarDec");
			numOfTab++;
			printCurrentToken(false); //<keyword> static|field </keyword>
			printCurrentToken(); //<keyword> type </keyword>
			printCurrentToken(); //<identifier> varName </identifier>
			printMultipleVarDec(); //;or ,varName,varName;
			numOfTab--; //restore format
			printNonterminal("classVarDec",false); //end of classVarDec
		}
		else //debug
		{
			m_ofs << m_token << endl;
			break;
		}
	}
}

void CompilationEng::compileSubroutine()
{
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
			if(m_token == "constructor" || m_token == "function" || m_token == "method")
			{
				printNonterminal("subroutineDec");
				numOfTab++;
				printCurrentToken(false); //<keyword> constructor|function|method </keyword>
				printCurrentToken(true);  //<keyword> void|type </keyword>  void is also a keyword
				printCurrentToken(true);  //<symbol> subroutineName </keyword>
				printCurrentToken(true);  //<symbol> ( </symbol>
				compileParameterList();
				printCurrentToken(false); // <symbol> ) </symbol>
				compileSubroutineBody();
				numOfTab--;
				printNonterminal("subroutineDec",false); //end of subroutine
				}
				else
				{
					m_ofs << m_token << endl;
					break;
				}
			}
			
		}
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
	printCurrentToken(); //<symbol> } </symbol>
	numOfTab--;
	printNonterminal("subroutineBody",false); // end of subroutineBody
}

void CompilationEng::compileVarDec()
{
	while(true)
	{
		getToken();
		if(m_token == "let" || m_token =="do" || m_token == "if" 
			||m_token == "while" ||m_token =="return")
		{
			m_bPutback = true;
			break;
		}
		else if(m_token == "var")
		{
			printNonterminal("varDec");
			numOfTab++;
			printCurrentToken(false); //<keyword> var </keyword>
			printCurrentToken(); //<keyword> type </keyword>
			printCurrentToken(); //<id> varName </id>
			printMultipleVarDec();//<id> varName,varName </id>
			numOfTab--;
			printNonterminal("varDec",false); //end of varDec
		}
		else 
		{
			m_ofs << m_token << endl;
			break;
		}
	}
}

void CompilationEng::compileStatements()
{
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
			if(m_bZeroStatements)
			{
				printNonterminal("statements");
				numOfTab++;
			}
			m_bZeroStatements = false;
			if(m_token == "let")
			{
				compileLet();
				m_bZeroStatements =false;
			}
			else if(m_token == "if")
			{
				compileIf();
				m_bZeroStatements=false;
			}
			else if(m_token == "while")
			{
				compileWhile();
				m_bZeroStatements = false;
			}
			else if(m_token == "do")
			{
				compileDo();
				m_bZeroStatements =false;
			}
			else if(m_token == "return")
			{
				compileReturn();
				m_bZeroStatements=false;
			}
			else
			{
				m_ofs << m_token << endl;
				break;
			}
		}
		
	}
	if(!m_bZeroStatements)
	{
		numOfTab--;
		printNonterminal("statements",false); //end of statements
	}
	m_bZeroStatements = true;
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
	printCurrentToken();  //<symbol> ; </symbol>
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
	m_bZeroStatements=true;
	compileStatements(); 
	printCurrentToken(); //<symbol> } </symbol>

	//else part
	getToken();
	if(m_token == "else")
	{
		printCurrentToken(false); //<keyword> else </keyword>
		printCurrentToken(); //<symbol> { </symbol>
		m_bZeroStatements=true;
		compileStatements(); 
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
	m_bZeroStatements =true;
	compileStatements();
	printCurrentToken(); //<symbol> } </symbol>

	numOfTab--;
	printNonterminal("whileStatement",false);
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
	while(true)
	{
		getToken();
		char c = m_token[0];
		if(m_token == ")" )
		{
			if(stringStack == "(") //empty expression
			{
			}
			else
			{
				numOfTab--;
				printNonterminal("expression",false);
			}
			m_bPutback = true;
			break;
		}
		if( m_token == "," || m_token == ";")  //expressionList
		{
			m_bPutback =true;
			numOfTab--;
			printNonterminal("expression",false);
			break;
		}
		else if(m_sOp.count(c) >0)
		{
			printCurrentToken(false); //<symbol> op </symbol>
			compileTerm();
		}
		else
		{
			printNonterminal("expression"); //<expression>
			numOfTab++;
			m_bPutback = true;
			compileTerm();
		}
	}
}

void CompilationEng::compileTerm()
{
	getToken();
	printNonterminal("term");
	numOfTab++;

	if(tokenizer.tokenType() == "keyword")
	{
		printCurrentToken(false); //<keyword> keyword </keyword>
	}
	else if(tokenizer.tokenType() == "stringconst")
	{
		printCurrentToken(false);
	}
	else if(tokenizer.tokenType() == "integerConstant")
	{
		printCurrentToken(false);
	}
	else if(tokenizer.tokenType() == "symbol")
	{
		if(m_token == "(") // (expression)
		{
			printCurrentToken(false);
			compileExpression();
			printCurrentToken();  //<symbol> )</symbol>
		}
		else if(m_token == "-" || m_token == "~")
		{
			printCurrentToken(false); //<symbol> -|~ </symbol>
			compileTerm();
		}
		else //empty term
		{

			m_bPutback = true;
			}
	}
	else if(tokenizer.tokenType() == "identifier")
	{
		getToken();
		if(m_token == "[") //varName [ expression ]
		{
			printToken(stringStack);
			printCurrentToken(false);
			compileExpression();
			printCurrentToken(); //<symbol> ] </symbol>
		}
		else if(m_token == "(" ) // subroutineCall
		{
			printToken(stringStack);
			printCurrentToken(false); //<symbol> ( </symbol>
			compileExpressionList();
			printCurrentToken();
		}
		else if(m_token == ".") 
		{
			printToken(stringStack); //className
			printCurrentToken(false); //<symbol> . </symbol>
			printCurrentToken(); //<id> subroutineName </id>
			printCurrentToken(); //<symbol> ( </symbol>
			compileExpressionList();
			printCurrentToken(); //<symbol> ) </symbol>
		}
		else  if(m_sOp.count(m_token[0]) > 0) //term op term
		{
			printToken(stringStack); //<id> </id>
			m_bPutback = true;
		}
		else//varName 
		{
			printToken(stringStack); //<id> varName </id>
			m_bPutback = true;
		}
	}

	numOfTab--;
	printNonterminal("term",false); //end of term
}

void CompilationEng::compileSubroutineCall()
{
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
}
void CompilationEng::compileExpressionList()
{
	printNonterminal("expressionList");
	numOfTab++;
	compileExpression();

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
			m_ofs << m_token << endl;
			break;
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
	for(int i=0; i<numOfTab; ++i)
		m_ofs << " "<< " " ;
	m_ofs << "<" << s << ">" << " " << m_token << " " << "</" << s << ">" << endl;
}

void CompilationEng::printToken(string s)
{
	string tokenType = tokenizer.tokenType(s);
	for(int i=0; i<numOfTab; ++i)
		m_ofs << " "<< " ";
	m_ofs << "<" << tokenType  << ">" << " " << s << " " << "</" << tokenType << ">" << endl;
}

															
void CompilationEng::printNonterminal(string nonterminal, bool isstart)
{
	for(int i=0;i<numOfTab;++i)
		m_ofs << " "<< " ";
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
			stringStack = m_token;
			m_token = tokenizer.m_token;
	}
	m_bPutback = false;
}

void CompilationEng::init()
{
		m_sOp = {'+','-','/','*','&','|','<','>','='};
			numOfTab = 0;
			m_bPutback =false;
			m_bZeroStatements = true;
				tokenizer.m_ifs.open(m_sifs,ios_base::in);
}
