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
	className = m_token;
	printCurrentToken(true);  //<symbol> { </symbol>
	bInClass = true;
	compileClassVarDec();
	bInClass = false;
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

			//idkind
			m_idKind = m_token; //m_idKind = static || field
			printCurrentToken(false); //<keyword> static|field </keyword>

			//idtype
			bType = true;
			printCurrentToken(); //<keyword> type </keyword>
			bType = false;
			m_idType = m_token; //m_idType = type

			printCurrentToken(); //<identifier> varName </identifier>

			nClassField++;

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

				//set the function type
				functionType = m_token;


				if(functionType == "method"  )
				{
					symT.bInClass = false;
					symT.define("this",className,"arg");
				}


				//it's "at" the subroutine, so you can find the subroutine name,they 
				//doesn't go into symbol table
				bAtSubroutine = true;

				printCurrentToken(true);  //<keyword> void|type </keyword>  void is also a keyword
				printCurrentToken(true);  //<symbol> subroutineName </keyword>
				
				// reassign functionName every time enter this scope
				functionName = className + "." + m_token;
				
				//It's not at subroutine and not in class.Now,it's in subroutine
				bAtSubroutine = false;
				printCurrentToken(true);  //<symbol> ( </symbol>
				bInSubroutine = true;
				bInClass = false;

				compileParameterList();
				printCurrentToken(false); // <symbol> ) </symbol>


				compileSubroutineBody();
				numOfTab--;
				bInSubroutine = false;
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
	
	//It's time to write Function declaration
	writer.writeFunction(functionName,nLocals);
	if(functionType == "constructor")
	{
		//push how many space needed
		writer.writePush("constant",nClassField);
		writer.writeCall("Memory.alloc",1);
		writer.writePop("pointer",0); //allocated address-> this
	}	
	else if(functionType == "method" )
	{
		//push argument 0 to this	
		writer.writePush("argument",0);
		writer.writePop("pointer",0);
	}

	nLocals = 0;

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
			m_idKind = m_token;

			//distinguish type from varName
			bType = true;
			printCurrentToken(); //<keyword> type </keyword>
			bType = false;
			m_idType = m_token;

			printCurrentToken(); //<id> varName </id>

			//one more var declare that's one more local var
			nLocals++;

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
			if(m_bZeroStatements)  //insure that one statements nonterminal for one statements
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
	//store value into local variable
	string varName= m_token;
	letleftType = symT.typeOf(varName);

	getToken();
	if(m_token == "[")
	{
		printCurrentToken(false); //<symbol> [ </symbol>
		compileExpression();
		printCurrentToken(); //<symbol> ] </symbol>

		//it's array so need add index and address of varName

		//write vm code
		//if is array need add array index
		writePush(varName);
		writer.writeArithmetic("add");
		
		//get value from array
		writer.writePop("pointer",1);

		printCurrentToken(false); //<symbol> = </symbol>
		compileExpression();
		printCurrentToken(); //<symbol> ; </symbol>

		//write expression value into array[index]
		writer.writePop("that",0);
	}
	else
	{
		printCurrentToken(false); //<symbol> = </symbol>
		compileExpression();
		printCurrentToken(); //<symbol> ; </symbol>

		//get value from stack and pop it into the address of var
		writePop(varName);
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

	//pop return value to temp segment according to vm specification
	writer.writePop("temp",0);

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

	//compute the condiont and push !(cond)
	writer.writeArithmetic("neg");
	string label1("IF_1");
	label1 += std::to_string(iftag);
	string label2("IF_2");
	label2 += std::to_string(iftag);
	writer.writeIf(label1);
	iftag++;

	printCurrentToken(); //<symbol> { </symbol>
	m_bZeroStatements=true;
	compileStatements(); 

	//goto label2
	writer.writeGoTo(label2);
	writer.writeLabel(label1);

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

	//end of if
	writer.writeLabel(label2);

	numOfTab--;
	printNonterminal("ifStatement",false);
}

void CompilationEng::compileWhile()
{
	printNonterminal("whileStatement");
	numOfTab++;

	//start of while
	string whilelabel1("WHILE_1");
	whilelabel1 += std::to_string(whiletag);
	string whilelabel2("WHILE_2");
	whilelabel2 += std::to_string(whiletag);
	whiletag ++;

	writer.writeLabel(whilelabel1);

	printCurrentToken(false);//<keyword> while </keyword>
	printCurrentToken(); //<symbol> ( </symbol>
	compileExpression();
	printCurrentToken(); //<symbol> ) </symbol>

	//computing condition and push !(cond)
	writer.writeArithmetic("neg");
	writer.writeIf(whilelabel2);

	printCurrentToken(); //<symbol> { </symbol>
	m_bZeroStatements =true;
	compileStatements();
	printCurrentToken(); //<symbol> } </symbol>

	//loop
	writer.writeGoTo(whilelabel1);
	//end of while
	writer.writeLabel(whilelabel2);

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
		//push 0 to stack vm specification
		writer.writePush("constant",0);

		printCurrentToken(false); // <symbol> ; </symbol>
	}
	else 
	{
		m_bPutback = true;
		compileExpression();
		printCurrentToken(); // <symbol> ; </symbol>
	}

	//write vm code
	writer.writeReturn();

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
			string op;
			if(m_token == "/")
				op = "divide";
			else if( m_token == "*")
				op = "multipe";
			else
				 op = mapOp[m_token];
			printCurrentToken(false); //<symbol> op </symbol>
			compileTerm();

			//it's here to output op command it's very magic 
			if(op == "divide" || op == "multiple")
				writer.writeCall(op,2);
			else
				writer.writeArithmetic(op);

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
		if(m_token == "true")
		{
			writer.writePush("constant",0);
			writer.writeArithmetic("not");
		}
		else if(m_token == "false")
		{
			writer.writePush("constant",0);
		}
		else if(m_token == "this")
		{
			writer.writePush("pointer",0);
		}
		else
			perror("unknown keyword");
	
	}
	else if(tokenizer.tokenType() == "stringconst")
	{
		printCurrentToken(false);
	}
	else if(tokenizer.tokenType() == "integerConstant")
	{
		printCurrentToken(false);

		//it's time to write const integer
		writer.writePush("constant",stoi(m_token));
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
			//save unary operator
			string uOp = m_token;

			compileTerm();
			if(uOp == "-")
				writer.writeArithmetic("neg");
			else
				writer.writeArithmetic("not");
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

			//writer array access 
			writer.writeArithmetic("add");
			writer.writePop("pointer",1);
			writer.writePush("that",0); //push result

			printCurrentToken(); //<symbol> ] </symbol>
		}
		else if(m_token == "(" ) // subroutineCall
		{
			printToken(stringStack);
			string subName = stringStack;
			printCurrentToken(false); //<symbol> ( </symbol>
			compileExpressionList();
			printCurrentToken();


			//call subroutine
			writer.writeCall(className+"."+subName,nArgs);
			nArgs = 1;
		}
		else if(m_token == ".") 
		{
			printToken(stringStack); //className

			string otherClassName = stringStack;
			printCurrentToken(false); //<symbol> . </symbol>
			printCurrentToken(); //<id> subroutineName </id>
			string subName = m_token;

			printCurrentToken(); //<symbol> ( </symbol>
			compileExpressionList();
			printCurrentToken(); //<symbol> ) </symbol>

			//call subroutine
			// if the method is a constructor then needn't pass
			// this pointer
			if(letleftType == otherClassName)
			{
				writer.writeCall(otherClassName+"."+subName,nArgs);
			}
			else
			{
				writer.writeCall(otherClassName+"."+subName,nArgs);
			}
			nArgs =1;
		}

		//this line seems verbose
		else  if(m_sOp.count(m_token[0]) > 0) //term op term
		{
			printToken(stringStack); //<id> </id>
			m_bPutback = true;

			//write vm code
			writePush(stringStack);
			
		}
		else//varName 
		{
			printToken(stringStack); //<id> varName </id>
			m_bPutback = true;

			//write vm code
			writePush(stringStack);

		}
	}

	numOfTab--;
	printNonterminal("term",false); //end of term
}

void CompilationEng::compileSubroutineCall()
{
	//don't put these into symbol table
	// it either use a symbol or a classname
	bType = true;
	printCurrentToken(); //<id> </id>
	bType = false;
	stringStack = m_token;

	getToken();
	if(m_token == "(")
	{
		string subName = stringStack;

		//push this that is the className
		writer.writePush("pointer",0);

		printCurrentToken(false); //<symbol> ( </symbol>
		compileExpressionList();
		printCurrentToken(); //<symbol> ) </symbol>

		//call this function
		writer.writeCall(className+"."+subName,nArgs);
		nArgs = 1;
	}
	else if(m_token == ".")
	{
		string otherClassName;
		//determine do statement call a function or a method
		if(symT.contain(stringStack))  //call a method
		{
			string otherObjectName = stringStack;
			otherClassName = symT.typeOf(otherObjectName);
			//push object address
			writePush(otherObjectName);
		}
		else //a function
		{
			otherClassName = stringStack;
		}


		printCurrentToken(false); //<symbol> . </symbol>
		
		printCurrentToken(); //<id> subroutineName </symbol>
		string subName = m_token;

		printCurrentToken(); //<symbol> ( </symbol>
		compileExpressionList();
		printCurrentToken(); //<symbol> ) </symbol>

		//call this function
		writer.writeCall(otherClassName+"."+subName,nArgs);
		nArgs = 1;
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
			nArgs++;
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
	string sused ;
	int index=0;
	string kind;
	string idCategory;
	if(m_tokenType == "identifier" && (bType==false))
	{
		if((!bInClass&&!bInSubroutine) || bAtSubroutine ) //className and SubroutineName doesn't go into symboltable
		{
			if(!bInClass)
				idCategory ="className";
			else
				idCategory ="subroutineName";

			for(int i=0; i<numOfTab; ++i)
				m_ofs << " "<< " " ;
			m_ofs << "<" << s << ">" << " " << m_token << " "<< idCategory << " " << "</" << s << ">" << endl;
		}
		else if(bInClass ||bInSubroutine)
		{
			if(bInClass)
				symT.bInClass = true; //it means differntly in SymbolTable and ComEngine
			else
				symT.bInClass = false;
			if(symT.contain(m_token))
			{
				sused = "using";
				kind = symT.kindOf(m_token);
				index = symT.indexOf(m_token);
			}
			else
			{
				kind = m_idKind;
				symT.define(m_token,m_idType,kind);
				sused = "defining";
				index = symT.indexOf(m_token);
			}

			for(int i=0; i<numOfTab; ++i)
				m_ofs << " "<< " " ;
			m_ofs << "<" << s << ">" << " " << m_token << " "<< idCategory << " " << sused << " " << kind << " "<< index << " " << "</" << s << ">" << endl;
		}
	}
	else
	{
		for(int i=0; i<numOfTab; ++i)
			m_ofs << " "<< " " ;
		m_ofs << "<" << s << ">" << " " << m_token << " " << "</" << s << ">" << endl;
	}
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

		//one more local var
		if(bInClass)
		{
			nClassField++;
		}
		if(bInSubroutine)
		{
			nLocals++;
		}

		printMultipleVarDec();
	}
}

void CompilationEng::printMultipleParameterList()
{
	m_idKind = "arg";
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
		m_idType = m_token; //idType = type
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
		mapOp = {{"+","add"},{"-","sub"},{"&amp;","and"},{"|","or"},{"&lt;","lt"},{"&gt;","gt"},{"=","eq"}};
		numOfTab = 0;
		m_bPutback =false;
		m_bZeroStatements = true;
		bInClass = false;
		bAtSubroutine = false;
		bInSubroutine = false;
		bType = false;
		tokenizer.m_ifs.open(m_sifs,ios_base::in);

		//vm writer
		nLocals = 0;
		nClassField=0;
		nArgs = 1; //need pass this or object
		iftag = 0;
		whiletag=0;
}

void CompilationEng::writePush(string identifier)
{
	//it's time to push this varName into stack

			//first,determine if the variable in the local scope
			if(!symT.contain(identifier))
				bInClass = true;

			string idKind = symT.kindOf(identifier);
			int index = symT.indexOf(identifier);
			string idType = symT.typeOf(identifier);

			if(!symT.contain(identifier))
				bInClass = false;

			//different kind of var to differnet segment
			if(idKind == "static")
			{
				writer.writePush("static",index);
			}
			else if(idKind == "field")
			{
				writer.writePush("this",index);
			}
			else if(idKind == "arg")
			{
				writer.writePush("argument",index);
			}
			else if(idKind == "var")
			{
				writer.writePush("local",index);
			}
}

void CompilationEng::writePop(string identifier)
{
	//it's time to push this varName into stack

			//first,determine if the variable in the local scope
			if(!symT.contain(identifier))
				bInClass = true;
			string idKind = symT.kindOf(identifier);

			int index = symT.indexOf(identifier);


			if(!symT.contain(identifier))
				bInClass = false;

			if(idKind == "static")
			{
				writer.writePop("static",index);
			}
			else if(idKind == "field")
			{
				writer.writePop("this",index);
			}
			else if(idKind == "arg")
			{
				writer.writePop("argument",index);
			}
			else if(idKind == "var")
			{
				writer.writePop("local",index);
			}
}
