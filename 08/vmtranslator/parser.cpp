// Author: Jack Chin
// Date: 14/01/2014

#include "codewriter.h"

Parser::Parser()
{
	m_set = {"constant","argument","local","static",
				"temp", "pointer", "this", "that"};

}

Parser::~Parser(){}

trivec Parser::Advance()
{
	string s;
  m_sCom = "";
  m_sArg1 = "";
  m_trivec.first="";
  m_trivec.second.first="";
  m_trivec.second.second="";
  m_sArg2 = "";  //clear as there is a blank line at the end of the file.
	while(getline(m_ifs,s))
	{
		//trim space at the begining
		s.erase(s.begin(),find_if_not(s.begin(),s.end(),(int(*)(int))isspace));

		//ignore blank line and  comment line
		if(s.size() == 0  || s.front() == '/')
		{
			continue;
		}

		//extract different command element from a line
		vector<string> vec ;  //output vector container
    //trim comment at the end
    if(s.find("/") != std::string::npos)
      s.erase(s.begin()+s.find_first_of("/"),s.end());
    istringstream iss(s);
		copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter<vector<string> > (vec));
		if(vec.size() == 2)
    {
      m_trivec.first = vec[0];
      m_trivec.second.first = vec[1];
      m_trivec.second.second = "";
			break;
    }
    else if(vec.size() == 1)
    {
      m_trivec.first = vec[0];
      m_trivec.second.first = "";
      m_trivec.second.second = "";
      break;
    }
		else
		{
			m_trivec.first = vec[0];  //command 

			if(m_set.count(vec[1])>0)
			{
				m_trivec.second.first = vec[1];  //first argument
				m_trivec.second.second = vec[2]; //second argument
			}
			else
				m_trivec.second.second = vec[1];
			break;
		}

	} //while
	return m_trivec;
}

bool Parser::HasNext()
{
	return !m_ifs.eof();
}



























		
