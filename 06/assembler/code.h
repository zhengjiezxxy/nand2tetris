//implementation of code module for the assembler
//Author: Jack Chin
//Date: 25/11/2013

Class Code{
public:
	Code();
	Code(File file);  //establish four hash table from file
	~Code();
	String dest(String s);
	String jmp(Stirng  s);
	String comp(String s);
}
	
