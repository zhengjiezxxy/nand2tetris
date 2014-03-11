// Arthor: Jack Chin
// Date: 03/03/2014
#include "VMWriter.h"

VMWriter::VMWriter()
{
}

VMWriter::~VMWriter()
{}

void VMWriter::writePush(string seg,int index)
{
	m_ofs << "push " << seg << " " << index << endl;
}

void VMWriter::writePop(string seg,int index)
{
	m_ofs << "pop " << seg << " " << index << endl;
}

void VMWriter::writeArithmetic(string command)
{
	m_ofs << command << endl;
}

void VMWriter::writeLabel(string label)
{
	m_ofs << "label " << label << endl;
}

void VMWriter::writeGoTo(string label)
{
	m_ofs << "goto " << label << endl;
}

void VMWriter::writeIf(string label)
{
	m_ofs << "if-goto " << label << endl;
}

void VMWriter::writeCall(string name,int nArgs)
{
	m_ofs << "call "<< name << " " << nArgs << endl;
}

void VMWriter::writeFunction(string name,int nLocals)
{
	m_ofs << "function " << name << " " << nLocals << endl;
}

void VMWriter::writeReturn()
{
	m_ofs << "return" << endl;
}
