//the implementation of parser for the assembler
//Author: Jack Chin
//Data: 25/11/2013

Class Parser{
public:
	Parser();
	Parser(File* pFile);  //encapsulate the parse process, file is the input source code
	~Parser();

	bool hasNext();   //whether reach the EOF
	bool ACom();      //if this command a A type command?
	bool CCom();	  //if this command a C type command?
	bool LCom(); 	  //if this command a Label?
	advance();		  //advance to next setence if there is another command.
	string dest();	  //return the dest string
	string comp();	  //return the compare string
	string jmp();	  //return the jump string

	string address(); //return address string of A type command

private:
	const char * m_rawString;      //every line excluding the comment
	m_comp;
	m_dest;
	m_jmp;
	m_address;
	void analyze();
};
	
	
