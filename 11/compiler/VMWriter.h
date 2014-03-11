// Arthor: Jack Chin
// Date: 02/03/2014

#include "include/include.h"
#define VMWRITER_H

class VMWriter{
public:
	VMWriter();
	~VMWriter();

public:
	void writePush(string seg,int index);
	void writePop(string seg,int index);
	void writeArithmetic(string command);
	void writeLabel(string label);
	void writeGoTo(string label);
	void writeIf(string label);
	void writeCall(string name,int nArgs);
	void writeFunction(string name,int nLocals);
	void writeReturn();
	void close(); //close the output file
public:
	std::ofstream m_ofs;//outputstream
	std::vector<string> vecCom;
};
