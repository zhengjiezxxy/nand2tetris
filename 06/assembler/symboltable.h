//implemetation of a symtable for assembler
//Author: Jack Chin
//Date: 25/11/2013

using namespace std;

Class SymTable{
pulic:
	Symtable();
	Symtable(FIle file);  //initialize the symtable using a txt file
	~Symtable();
	add(pair<String,int> entry);	// add an entry into the symboltable
	value(String s);  // return the value of key s
}
	
