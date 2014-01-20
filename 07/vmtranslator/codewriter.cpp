// AUTHOR: Jack Chin
// Date: 15/01/2014

#include "codewriter.h"

CodeWriter::CodeWriter(ofstream ofs)
{
	//initialization of SP
	ofs << "@2047" << endl;  //SP->256
	ofs << "D=A" << endl;
	ofs << "@0" << endl;
	ofs << "M=D" << endl;
}

CodeWriter::~CodeWriter()
{}

void CodeWriter::WriteCom(trivec tvec)
{
	m_sCom = tvec.first;
	m_sArg1 = tvec.second.first;
	m_sArg2 = tvec.second.second;

	switch(m_sCom)
	{
		case "push" :
			switch (m_sArg1)
			{
				case "constant" :
				{
					ofs << "@" << m_sArg2 << endl;
					ofs << "D=M" << endl;
					ofs << "@" << SP << endl;
					ofs << "M=D" << endl;
				}
				case "static" :
				{
					if(IsNum(m_sArg2))
						ofs << "@" << STATIC+stol(m_sArg2) << endl;
					else
						cout << "push a symbol address of static segment" << endl;
					ofs << "D=M" << endl;
					ofs << "@" << SP << endl;
					ofs << "M=D" << endl;
				}

//				case "local" :
//				{
//					//@LCL
//					//D=A
//					//AD=D+2
//					//D=M
//					//@SP
//					//M=D
//					ofs << "@" << "LCL"  << endl;
//					ofs << "D=A" << endl;
//
//					if(IsNum(m_sArg2)
//						ofs << "AD=D+" << stol(m_sArg2) << endl;
//					else
//						cout << "push a symbol address of local,temp,argument
//									segment" << endl;
//
//					ofs << "D=M" << endl;
//					ofs << "@" << SP << endl;
//					ofs << "M=D" << endl;
//				}
				
//				case "argument" :
//				{				
//					//@LCL
//					//D=A
//					//AD=D+2
//					//D=M
//					//@SP
//					//M=D
//
//					ofs << "@" << "ARG" << endl;
//					ofs << "D=A" << endl;
//
//					if(IsNum(m_sArg2)
//						ofs << "AD=D+" << stol(m_sArg2) << endl;
//					else
//						cout << "push a symbol address of local,temp,argument
//									segment" << endl;
//
//					ofs << "D=M" << endl;
//					ofs << "@" << SP << endl;
//					ofs << "M=D" << endl;
//				}
			} //switch(m_Arg1)

			case "pop" :
				switch(m_sArg1)
				{
					case "static" :  // pop static 1
					{
						// @SP
						// D=M
						// @STATIC+2
						// M=D
						// D=D-1 stack pointer deccrement
						// @SP
						// M=D
						if(IsNum(m_sArg2)
							ofs << "@SP" << endl;
							ofs << "D=M" << endl;
							if(IsNum(m_sArg2)
								ofs << "@" << STATIC + stol(m_sArg2) << endl;
							else
								cout << "pop a symbol address" << endl;
							ofs << "M=D" << endl;
							ofs << "D=D-1" << endl;
							ofs << "@SP" << endl;
							ofs << "M=D" << endl;
					}

					case "constant" :
					{
						// pop constant 2
						// @SP
						// D=M
						// D=D-1
						// @SP
						// M=D
						ofs << "@SP" << endl;
						ofs << "D=M" << endl;
						ofs << "D=D-1" << endl;
						ofs << "@SP" << endl;
						ofs << "M=D" << endl;
					}

					//case  "local" :
					//{
						// pop local 2
						// 
				//}
			}// switch(m_sArg1)
		}//switch(m_sCom)
	}// WriteCom
			
				

	
