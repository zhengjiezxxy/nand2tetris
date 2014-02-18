// AUTHOR: Jack Chin
// Date: 15/01/2014

#include "codewriter.h"

CodeWriter::CodeWriter()
{
  }

CodeWriter::~CodeWriter()
{}

void CodeWriter::WriteCom(trivec tvec)
{
	m_sCom = tvec.first;
	m_sArg1 = tvec.second.first;
	m_sArg2 = tvec.second.second;

		if(m_sCom ==  "push") 
    {
				if(m_sArg1 == "constant") 
				{
          // @2
          // D=A
          // @SP
          // A=M
          // M=D   (*sp) = 2
          // @SP
          // M=M+1 (sp = sp-1)
					m_ofs << "@" << m_sArg2 << endl;
					m_ofs << "D=A" << endl;
					m_ofs << "@" << SP << endl;
          m_ofs << "A=M" << endl;
					m_ofs << "M=D" << endl;
          m_ofs << "@SP" << endl;
          m_ofs << "M=M+1" << endl;
				}
        else if(m_sArg1 ==  "static") 
				{
					if(IsNum(m_sArg2))
						m_ofs << "@" << STATIC(0) + stol(m_sArg2) << endl;
					else
						cout << "push a symbol address of static segment" << endl;
					m_ofs << "D=M" << endl;
					m_ofs << "@" << SP << endl;
          m_ofs << "A=M" << endl;
					m_ofs << "M=D" << endl;
          m_ofs << "@SP" << endl;
          m_ofs << "M=M+1" << endl;
				}
        else if(m_sArg1 == "temp")
        {
          if(IsNum(m_sArg2))
						m_ofs << "@" <<TEMP(0) + stol(m_sArg2) << endl;
					else
						cout << "push a symbol address of static segment" << endl;
					m_ofs << "D=M" << endl;
					m_ofs << "@" << SP << endl;
          m_ofs << "A=M" << endl;
					m_ofs << "M=D" << endl;
          m_ofs << "@SP" << endl;
          m_ofs << "M=M+1" << endl;
        }

        else if( m_sArg1 == "local")
				{
					//@LCL  (push local 2)
					//A=M
					//A=A+1
          //A=A+1  //DO IT TWICE
					//D=M
					//@SP
					//A=M
          //M=D
          //@SP
          //M=M+1
					m_ofs << "@" << "LCL"  << endl;
					m_ofs << "A=M" << endl;

					if(IsNum(m_sArg2))
            {
              int n = stol(m_sArg2);
              for(int i=0;i<n;++i)
                m_ofs << "A=A+1" << endl;
            }
					else
						cout << "push a symbol address of local,temp,argument segment" << endl;

					m_ofs << "D=M" << endl;
					m_ofs << "@" << SP << endl;
          m_ofs << "A=M" << endl;
					m_ofs << "M=D" << endl;
          m_ofs << "@SP" << endl;
          m_ofs << "M=M+1" << endl;
				}
				
        else if(m_sArg1 == "argument" )
				{				
					//@ARG  (push argument 2)
					//A=M
					//A=A+1
          //A=A+1  //DO IT TWICE
					//D=M
					//@SP
					//A=M
          //M=D
          //@SP
          //M=M+1
					m_ofs << "@" << "ARG"  << endl;
					m_ofs << "A=M" << endl;

					if(IsNum(m_sArg2))
            {
              int n = stol(m_sArg2);
              for(int i=0;i<n;++i)
                m_ofs << "A=A+1" << endl;
            }
					else
						cout << "push a symbol address of local,temp,argument segment" << endl;

					m_ofs << "D=M" << endl;
					m_ofs << "@" << "SP" << endl;
          m_ofs << "A=M" << endl;
					m_ofs << "M=D" << endl;
          m_ofs << "@SP" << endl;
          m_ofs << "M=M+1" << endl;
      }
      else if (m_sArg1 == "this")
      {
      //@ARG  (push argument 2)
					//A=M
					//A=A+1
          //A=A+1  //DO IT TWICE
					//D=M
					//@SP
					//A=M
          //M=D
          //@SP (SP = SP+1)
          //M=M+1
					m_ofs << "@" << "THIS"  << endl;
					m_ofs << "A=M" << endl;

					if(IsNum(m_sArg2))
            {
              int n = stol(m_sArg2);
              for(int i=0;i<n;++i)
                m_ofs << "A=A+1" << endl;
            }
					else
						cout << "push a symbol address of local,temp,argument segment" << endl;

					m_ofs << "D=M" << endl;
					m_ofs << "@" << "SP" << endl;
          m_ofs << "A=M" << endl;
					m_ofs << "M=D" << endl;
          m_ofs << "@SP" << endl;
          m_ofs << "M=M+1" << endl;
      }
      else if (m_sArg1 == "that" )
      {
          //@THAT  (push argument 2)
					//A=M
					//A=A+1
          //A=A+1  //DO IT TWICE
					//D=M
					//@SP
					//A=M
          //M=D
          //@SP
          //M=M+1
					m_ofs << "@" << "THAT"  << endl;
					m_ofs << "A=M" << endl;

					if(IsNum(m_sArg2))
            {
              int n = stol(m_sArg2);
              for(int i=0;i<n;++i)
                m_ofs << "A=A+1" << endl;
            }
					else
						cout << "push a symbol address of local,temp,argument segment" << endl;

					m_ofs << "D=M" << endl;
					m_ofs << "@" << "SP" << endl;
          m_ofs << "A=M" << endl;
					m_ofs << "M=D" << endl;
          m_ofs << "@SP" << endl;
          m_ofs << "M=M+1" << endl;
    }
        else if (m_sArg1 == "pointer")    //it's different from other segements
        {
        	m_ofs << "@" << "3"  << endl; //RAM[3] 
					if(IsNum(m_sArg2))
            {
              int n = stol(m_sArg2);
              for(int i=0;i<n;++i)
                m_ofs << "A=A+1" << endl;
            }
					else
						cout << "push a symbol address of local,temp,argument segment" << endl;

					m_ofs << "D=M" << endl;
					m_ofs << "@" << "SP" << endl;
          m_ofs << "A=M" << endl;
					m_ofs << "M=D" << endl;
          m_ofs << "@SP" << endl;
          m_ofs << "M=M+1" << endl;
        }
  } //switch(m_Arg1)

    else if(m_sCom == "pop") 
    {
					if(m_sArg1 == "static")  // pop static 1
					{
						// @SP
            // M=M-1
						// D=M
						// @STATIC+2
						// M=D
						// D=D-1 stack pointer deccrement
						// @SP
						// M=D
            // @SP
            //  M=M-1
              m_ofs << "@SP" << endl;
              m_ofs << "A=M" << endl;
              m_ofs << "A=A-1" << endl;
							m_ofs << "D=M" << endl;
							if(IsNum(m_sArg2))
								m_ofs << "@" << STATIC(0) + stol(m_sArg2) << endl;
							else
								cout << "pop a symbol address" << endl;
							m_ofs << "M=D" << endl;
              m_ofs << "@SP" << endl;
              m_ofs << "M=M-1" << endl;
					}
          else if (m_sArg1 == "temp")
          {
            // @SP
						// D=M
						// @STATIC+2
						// M=D
						// D=D-1 stack pointer deccrement
						// @SP
						// M=D
            // @SP
            //  M=M-1
              m_ofs << "@SP" << endl;
              m_ofs << "A=M" << endl;
              m_ofs << "A=A-1" << endl;
							m_ofs << "D=M" << endl;
							if(IsNum(m_sArg2))
								m_ofs << "@" << TEMP(0) + stol(m_sArg2) << endl;
							else
								cout << "pop a symbol address" << endl;
							m_ofs << "M=D" << endl;
              m_ofs << "@SP" << endl;
              m_ofs << "M=M-1" << endl;

          }

          else if(m_sArg1 == "constant")
					{
						// pop constant 2
						// @SP
						// D=M
						// D=D-1
						// @SP
						// M=D
            // @SP
            // M=M-1
						//m_ofs << "@SP" << endl;
           //m_ofs << "A=M" << endl;
            //m_ofs << "A=A-1" << endl;
						//m_ofs << "D=M" << endl;
						//m_ofs << "D=D-1" << endl;
						//m_ofs << "@SP" << endl;
						//m_ofs << "M=D" << endl;
            //m_ofs << "@SP" << endl;
            //m_ofs << "M=M-1" << endl;
					}

          else if( m_sArg1 ==  "local")
					{
            // pop local 2
            // @SP
            // A=M
            // A=A-1
            // D=M
            // @LCL
            // A=M
            // A=A+1
            // A=A+1  //twice
            // M=D
            // @SP
            // M=M-1
            m_ofs << "@" << "SP"  << endl;
            m_ofs << "A=M" << endl;
            m_ofs << "A=A-1" << endl;
            m_ofs << "D=M" << endl;
            m_ofs << "@" << "LCL" << endl;
            m_ofs << "A=M" << endl;
            if(IsNum(m_sArg2))
            {
              int n = stol(m_sArg2);
              for(int i=0;i<n;++i)
              m_ofs << "A=A+1" << endl;
            }
            else
                cout << "push a symbol address of local,temp,argument segment" << endl;
            m_ofs << "M=D" << endl;
            m_ofs << "@SP" << endl;
            m_ofs << "M=M-1" << endl;
				  }
			    else if( m_sArg1 ==  "argument")
					{
            m_ofs << "@" << "SP"  << endl;
            m_ofs << "A=M" << endl;
            m_ofs << "A=A-1" << endl;
            m_ofs << "D=M" << endl;
            m_ofs << "@" << "ARG" << endl;
            m_ofs << "A=M" << endl;
            if(IsNum(m_sArg2))
            {
              int n = stol(m_sArg2);
              for(int i=0;i<n;++i)
              m_ofs << "A=A+1" << endl;
            }
            else
                cout << "push a symbol address of local,temp,argument segment" << endl;
            m_ofs << "M=D" << endl;
            m_ofs << "@SP" << endl;
            m_ofs << "M=M-1" << endl;
				  }
          else if( m_sArg1 ==  "this")
					{
            m_ofs << "@" << "SP"  << endl;
            m_ofs << "A=M" << endl;
            m_ofs << "A=A-1" << endl;
            m_ofs << "D=M" << endl;
            m_ofs << "@" << "THIS" << endl;
            m_ofs << "A=M" << endl;
            if(IsNum(m_sArg2))
            {
              int n = stol(m_sArg2);
              for(int i=0;i<n;++i)
              m_ofs << "A=A+1" << endl;
            }
            else
                cout << "push a symbol address of local,temp,argument segment" << endl;
            m_ofs << "M=D" << endl;
            m_ofs << "@SP" << endl;
            m_ofs << "M=M-1" << endl;
				  }
          else if( m_sArg1 ==  "that")
					{
            m_ofs << "@" << "SP"  << endl;
            m_ofs << "A=M" << endl;
            m_ofs << "A=A-1" << endl;
            m_ofs << "D=M" << endl;
            m_ofs << "@" << "THAT" << endl;
            m_ofs << "A=M" << endl;
            if(IsNum(m_sArg2))
            {
              int n = stol(m_sArg2);
              for(int i=0;i<n;++i)
              m_ofs << "A=A+1" << endl;
            }
            else
                cout << "push a symbol address of local,temp,argument segment" << endl;
            m_ofs << "M=D" << endl;
            m_ofs << "@SP" << endl;
            m_ofs << "M=M-1" << endl;
				  }
          else if( m_sArg1 ==  "pointer")
					{
            // pop local 2
            // @SP
            // A=M
            // A=A-1
            // D=M
            // @LCL
            // A=M
            // A=A+1
            // A=A+1  //twice
            // M=D
            // @SP
            // M=M-1
            m_ofs << "@" << "SP"  << endl;
            m_ofs << "A=M" << endl;
            m_ofs << "A=A-1" << endl;
            m_ofs << "D=M" << endl;
            m_ofs << "@" << "3" << endl;
            if(IsNum(m_sArg2))
            {
              int n = stol(m_sArg2);
              for(int i=0;i<n;++i)
              m_ofs << "A=A+1" << endl;
            }
            else
                cout << "push a symbol address of local,temp,argument segment" << endl;
            m_ofs << "M=D" << endl;
            m_ofs << "@SP" << endl;
            m_ofs << "M=M-1" << endl;
				  }
}// (pop)
    else if(m_sCom == "add")
    {
      //@SP
      //A=M
      //A=A+1
      //D=M    get mem(stackpointer)
      //A=A+1
      //D=D+M  add *sp+*(sp+1)
      //M=D    save into *(sp+1)
      //@SP
      //M=M+1  sp = sp +1
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "D=D+M" << endl;
      m_ofs << "M=D" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;
    }
    else if(m_sCom == "sub")
    {
      //@SP
      //A=M
      //A=A+1  (SP -> first unallocated mem)
      //D=M    get mem(stackpointer)
      //A=A+1
      //D=M-D  sub *(sp+1)-*(sp)
      //M=D    save into *(sp+1)
      //@SP
      //M=M+1  sp = sp +1
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "D=M-D" << endl;
      m_ofs << "M=D" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;
//
    }
    else if(m_sCom == "neg")
    {
      //@SP
      //A=M
      //A=A+1
      //M=-M
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "M=-M" << endl;
    }
    else if(m_sCom == "eq")
    {
      // @SP
      // A=M
      // A=A+1
      // D=M
      // A=A+1
      // D=M-D
      // @TRUE100
      // D;JEQ  //D=0;JUMP TRUE
      // @SP
      // M=M+1
      // @SP
      // M=M+1
      // @0
      // D=A  PUSH 0
      // @SP
      // M=D
      // @SP
      // M=M-1 
      // @END100
      // 0;JMP
      // (TRUE100)
      // @SP
      // M=M+2
      // @32767
      // D=A  PUSH 1111 1111 1111 1111
      // @SP
      // M=M-1
      // (END100)
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "D=M-D" << endl;
      m_ofs << "@TRUE" << m_truetag << endl;
      m_ofs << "D;JEQ" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;
      m_ofs << "@0" << endl;
      m_ofs << "D=A" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "M=D" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M+1" << endl;
      m_ofs << "@END" << m_endtag << endl;
      m_ofs << "0;JMP" << endl;
      m_ofs << "(TRUE" << m_truetag++ << ")" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;
      m_ofs << "@0" << endl;
      m_ofs << "D=!A" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "M=D" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M+1" << endl;
      m_ofs << "(END" << m_endtag++ << ")" << endl;

    } 
    else if (m_sCom == "gt" )
    {
      // @SP
      // A=M
      // A=A+1
      // D=M
      // A=A+1
      // D=M-D
      // @TRUE100
      // D;JGT  //D=0;JUMP TRUE
      // @SP
      // M=M+2 
      // @0
      // D=A  PUSH 0
      // @SP
      // M=D
      // @SP
      // M=M-1 
      // @END100
      // 0;JMP
      // (TRUE100)
      // @SP
      // M=M+2
      // @32767
      // D=A  PUSH 1111 1111 1111 1111
      // @SP
      // M=M-1
      // (END100)
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "D=M-D" << endl;
      m_ofs << "@TRUE" << m_truetag << endl;
      m_ofs << "D;JGT" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;
      m_ofs << "@0" << endl;
      m_ofs << "D=A" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "M=D" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M+1" << endl;
      m_ofs << "@END" << m_endtag << endl;
      m_ofs << "0;JMP" << endl;
      m_ofs << "(TRUE" << m_truetag++ << ")" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;
      m_ofs << "@SP"  << endl;
      m_ofs << "M=M-1" << endl;
      m_ofs << "@0" << endl;
      m_ofs << "D=!A" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "M=D" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M+1" << endl;
      m_ofs << "(END" << m_endtag++ << ")" << endl;


    }
    else if (m_sCom == "lt" )
    {
      // @SP
      // A=M
      // A=A+1
      // D=M
      // A=A+1
      // D=M-D
      // @TRUE100
      // D;JLT  //D=0;JUMP TRUE
      // @SP
      // M=M+2 
      // @0
      // D=A  PUSH 0
      // @SP
      // M=D
      // @SP
      // M=M-1 
      // @END100
      // 0;JMP
      // (TRUE100)
      // @SP
      // M=M+2
      // @32767
      // D=A  PUSH 1111 1111 1111 1111
      // @SP
      // M=M-1
      // (END100)
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "D=M"  << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "D=M-D" << endl;
      m_ofs << "@TRUE" << m_truetag << endl;
      m_ofs << "D;JLT" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;
      m_ofs << "@0" << endl;
      m_ofs << "D=A" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "M=D" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M+1" << endl;
      m_ofs << "@END" << m_endtag << endl;
      m_ofs << "0;JMP" << endl;
      m_ofs << "(TRUE" << m_truetag++ << ")" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;
      m_ofs << "@0" << endl;
      m_ofs << "D=!A" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "M=D" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M+1" << endl;
      m_ofs << "(END" << m_endtag++ << ")" << endl;
    }
    else if (m_sCom == "and")
    {
      //@SP
      //A=M
      //A=A+1  (SP -> first unallocated mem)
      //D=M    get mem(stackpointer)
      //A=A+1
      //D=M-D  sub *(sp+1)-*(sp)
      //M=D    save into *(sp+1)
      //@SP
      //M=M+1  sp = sp +1
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "D=D&M" << endl;
      m_ofs << "M=D" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;

    }
    else if (m_sCom == "or")
    {
      //@SP
      //A=M
      //A=A+1  (SP -> first unallocated mem)
      //D=M    get mem(stackpointer)
      //A=A+1
      //D=M-D  sub *(sp+1)-*(sp)
      //M=D    save into *(sp+1)
      //@SP
      //M=M+1  sp = sp +1
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "D=D|M" << endl;
      m_ofs << "M=D" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;
    }
    else if(m_sCom == "not")
    {
      //@SP
      //A=M
      //A=A+1
      //M=!M
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "M=!M" << endl;
    }
    else if (m_sCom == "label")
    {
      m_ofs << "(" << m_sArg1 << ")" << endl;
    }
    else if(m_sCom == "goto")
    {
      //@END
      //0;JMP
      m_ofs << "@" << m_sArg1 << endl;
      m_ofs << "0;JMP" << endl;
    }
    else if(m_sCom == "if-goto")
    {
      //@SP
      //A=M
      //A=A-1
      //D=M
      //@LABEL
      //D;JNE
      m_ofs << "@SP" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "A=A-1" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@" << m_sArg1 << endl;
      m_ofs << "D;JNE" << endl;
    }
    //else if (m_sCom == "



	}// WriteCom
			
				

bool CodeWriter::IsNum(string s)
{
// Is this string a number string
  int n = s.size();
  for(int i=0;i<n;i++)
  {
    if(!isdigit(s[i]))
      return false;
  }
  if(n == 0 )
    return false;
  return true;
}

void CodeWriter::Init()
{
	m_truetag = 0;
  m_endtag = 0;
  m_ofs << "@256" << endl;  //SP->256
	m_ofs << "D=A" << endl;
	m_ofs << "@0" << endl;
	m_ofs << "M=D" << endl;
}
