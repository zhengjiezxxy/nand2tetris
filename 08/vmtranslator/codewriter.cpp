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
          bConst = true;
          GetValueFromSegment();
          PushToStack();
        }
        else if(m_sArg1 ==  "static") 
				{
          bStatic = true;
          GetValueFromSegment();
          PushToStack();
				}
        else if(m_sArg1 == "temp")
        {
          bTemp = true;
          GetValueFromSegment();
          PushToStack();
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
            bArg = true;
            GetValueFromSegment();
	          PushToStack();
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
          bArg = true;
          GetValueFromSegment();
          PushToStack();
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
          bArg = true;
          GetValueFromSegment();
          PushToStack();
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
          bArg = true;
          GetValueFromSegment();
          PushToStack();
    }
        else if (m_sArg1 == "pointer")    //it's different from other segements
        {
          bPointer = true;
          GetValueFromSegment();
          PushToStack();
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
              GetFromStack();
              bStatic = true;
              GetValueFromSegment(true);
              BackOneStep();
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
              GetFromStack();
              bTemp = true;
              GetValueFromSegment(true);
              BackOneStep();
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
            GetFromStack();
            bArg = true;
            GetValueFromSegment(true);
            BackOneStep();
				  }
			    else if( m_sArg1 ==  "argument")
					{
            GetFromStack();
            bArg = true;
            GetValueFromSegment(true);
            BackOneStep();
				  }
          else if( m_sArg1 ==  "this")
					{
            GetFromStack();
            bArg = true;
            GetValueFromSegment(true);
            BackOneStep();
				  }
          else if( m_sArg1 ==  "that")
					{
            GetFromStack();
            bArg = true;
            GetValueFromSegment(true);
            BackOneStep();
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
            GetFromStack();
            bPointer = true;
            GetValueFromSegment(true);
            BackOneStep();
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
      //pop comparator
      m_ofs << "@SP" << endl;
      m_ofs << "M=M-1" << endl;
      m_ofs << "@" << m_sArg1 << endl;
      m_ofs << "D;JNE" << endl;
    }
    else if (m_sCom == "call")
    {
      //push returnAddress
      //@returnAddress100
      //D=A  //(resemble to const segment)
      //pushtostack();
      m_ofs << "@RETURNADDRESS" << m_rettag  << endl;
      m_ofs << "D=A" << endl;
      PushToStack();
      
      //push LCL
      //@LCL
      //D=M  
      //PUSHTOSTACK
      m_ofs << "@LCL" << endl;
      m_ofs << "D=M" << endl;
      PushToStack();

      //push arg
      m_ofs << "@ARG" << endl;
      m_ofs << "D=M" << endl;
      PushToStack();
       
      //push this
      m_ofs << "@THIS" << endl;
      m_ofs << "D=M" << endl;
      PushToStack();
      
      //push that
      m_ofs << "@THAT" << endl;
      m_ofs << "D=M" << endl;
      PushToStack();

      //Arg = SP-nArgs-5
      //@SP
      //D=M
      //ARG = D(SP-1) - nArgs -4
      //@SP
      //D=M
      //@4
      //D=D-A
      //@m_sArg2
      //D=D-A
      //PUSHTOSTACK
      m_ofs << "@SP" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@5" << endl;
      m_ofs << "D=D-A" << endl;
      if(IsNum(m_sArg2))
        m_ofs << "@" << std::stoi(m_sArg2) << endl;
      else
        std::cout << "second argument is not a number" << endl;
      m_ofs << "D=D-A" << endl;
      //push to lcl 
      m_ofs << "@ARG" << endl;
      m_ofs << "M=D" << endl;

      //LCL = SP
      m_ofs << "@SP" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@LCL" << endl;
      m_ofs << "M=D" << endl;

      //goto g
      m_ofs << "@" << m_sArg1 << endl;
      m_ofs << "0;JMP" << endl;

      //returnAddress
      m_ofs << "(RETURNADDRESS" << m_rettag++ << ")"<< endl;

    }
    else if( m_sCom == "function" )
    {
      //push 0 repeat nVars times
      if(IsNum(m_sArg2))
      {
        m_ofs << "(" << m_sArg1 << ")" << endl;
        int n = std::stoi(m_sArg2);
            for(int i=0;i<n;++i)
        {
          m_ofs << "@0" << endl;
          m_ofs << "D=A" << endl;
          PushToStack();
        }
      }
      else
        std::cout << "second argument isn't a number" << endl ;
    }
    else if(m_sCom == "return")
    {
      //save return value
      m_ofs << "@SP" << endl;
      m_ofs << "A=M-1" << endl;
      m_ofs << "D=M" << endl;
      m_ofs <<  "@R13" << endl;
      m_ofs << "M=D" << endl;

      //frame = LCL is a temp register
      m_ofs << "@LCL" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@R14" << endl;
      m_ofs << "M=D" << endl;

      //retAddr = *(frame-5)
      m_ofs << "@R14" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@5" << endl;
      m_ofs << "A=D-A" <<endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@R15" << endl;
      m_ofs << "M=D" << endl;

      //*(arg0) = returnvalue
      m_ofs << "@R13" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@ARG" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "M=D" << endl;

      //SP = argument1
      m_ofs << "@ARG" << endl;
      m_ofs << "D=M+1" << endl;
      m_ofs << "@SP" << endl;
      m_ofs << "M=D" << endl;

      //THAT = *(frame-1)
      m_ofs << "@R14" << endl;
      m_ofs << "A=M-1" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@THAT" << endl;
      m_ofs << "M=D" << endl;

      //THIS = *(frame-2)
      m_ofs << "@R14" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@2" << endl;
      m_ofs << "A=D-A" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@THIS" << endl;
      m_ofs << "M=D" << endl;

      //ARG= *(frame-3)
      m_ofs << "@R14" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@3" << endl;
      m_ofs << "A=D-A" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@ARG" << endl;
      m_ofs << "M=D" << endl;

      //LCL = *(frame-4)
      m_ofs << "@R14" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@4" << endl;
      m_ofs << "A=D-A" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@LCL" << endl;
      m_ofs << "M=D" << endl;

      //go to retAddr
      m_ofs << "@R15" << endl;
      m_ofs << "A=M" << endl;
      m_ofs << "0;JMP" << endl;
    }



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
  bConst = false;
  bArg = false;
  bTemp = false;
  bPointer = false;
  bStatic = false;
  m_mMacroSeg["local"] = "LCL";
  m_mMacroSeg["this"] = "THIS";
  m_mMacroSeg["that"] = "THAT";
  m_mMacroSeg["argument"] = "ARG";
	m_truetag = 0;
  m_endtag = 0;
  m_rettag = 0;
  m_ofs << "@256" << endl;  //SP->256
	m_ofs << "D=A" << endl;
	m_ofs << "@0" << endl;
	m_ofs << "M=D" << endl;
  //call Sys.init
      m_ofs << "@RETURNADDRESS" << m_rettag  << endl;
      m_ofs << "D=A" << endl;
      PushToStack();
      
      m_ofs << "@LCL" << endl;
      m_ofs << "D=M" << endl;
      PushToStack();
      m_ofs << "@ARG" << endl;
      m_ofs << "D=M" << endl;
      PushToStack();
       
      m_ofs << "@THIS" << endl;
      m_ofs << "D=M" << endl;
      PushToStack();
      
      m_ofs << "@THAT" << endl;
      m_ofs << "D=M" << endl;
      PushToStack();

      m_ofs << "@SP" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@5" << endl;
      m_ofs << "D=D-A" << endl;
      m_ofs << "@" << "0" << endl;
      m_ofs << "D=D-A" << endl;
      //push to lcl 
      m_ofs << "@ARG" << endl;
      m_ofs << "M=D" << endl;

      //LCL = SP
      m_ofs << "@SP" << endl;
      m_ofs << "D=M" << endl;
      m_ofs << "@LCL" << endl;
      m_ofs << "M=D" << endl;

      //goto g
      m_ofs << "@" << "Sys.init" << endl;
      m_ofs << "0;JMP" << endl;

      //returnAddress
      m_ofs << "(RETURNADDRESS" << m_rettag++ << ")"<< endl;

}

void CodeWriter::PushToStack()
{
  m_ofs << "@" << SP << endl;
  m_ofs << "A=M" << endl;
  m_ofs << "M=D" << endl;
  m_ofs << "@SP" << endl;
  m_ofs << "M=M+1" << endl;
}

void CodeWriter::GetFromStack()
{
  m_ofs << "@SP" << endl;
  m_ofs << "A=M" << endl;
  m_ofs << "A=A-1" << endl;
  m_ofs << "D=M" << endl;
}

void CodeWriter::BackOneStep()
{
  m_ofs << "@SP" << endl;
  m_ofs << "M=M-1" << endl;
}

void CodeWriter::GetValueFromSegment(bool reverse)
{
  if(IsNum(m_sArg2))
  {
    if(bConst)
      m_ofs << "@" << stol(m_sArg2) << endl;
    else if(bStatic)
      m_ofs << "@" << STATIC(0) + stol(m_sArg2) << endl;
    else if(bTemp)
      m_ofs << "@" << TEMP(0) + stol(m_sArg2) << endl;
    else if(bPointer)
    {
      m_ofs << "@" << "3"  << endl; //RAM[3] 
      int n = stol(m_sArg2);
      for(int i=0;i<n;++i)
      m_ofs << "A=A+1" << endl;
    }

    else if(bArg)
    {
      m_ofs << "@" << m_mMacroSeg[m_sArg1]  << endl;
      m_ofs << "A=M" << endl;
      int n = stol(m_sArg2);
      for(int i=0;i<n;++i)
          m_ofs << "A=A+1" << endl;
    
    }
  }
  else
    cout << "push a symbol address of static segment" << endl;
  if(!reverse)
  {
    if(bConst)
      m_ofs << "D=A" << endl;
    else if(bStatic||bTemp||bArg||bPointer)
      m_ofs << "D=M" << endl;
  }
  else
  {
    m_ofs << "M=D" << endl;
  }

  //restore all flags
  bConst = false;
  bStatic = false;
  bTemp = false;
  bArg = false;
  bPointer = false;
}

