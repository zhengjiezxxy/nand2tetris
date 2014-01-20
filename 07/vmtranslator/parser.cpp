// Author: Jack Chin
// Date: 14/01/2014

#include "codewriter.h"

Parser::Parser(ifstream ifs)
{
	m_ifs(ifs);
	m_set = {"constant","argument","local","static",
				"temp", "pointer", "this", "that"};

}

Parser::~Parser(){}

trivec Parser::Advance()
{
	string s;
	while(getline(m_ifs,s))
	{
		//trim space at the begining
		s.erase(s.begin(),find_if_not(s.begin(),s.end(),(int(*)(int))isspace));

		//ignore blank line and  comment line
		if(s.size() == 0  || s.front() = '/')
		{
			getline(m_ifs,s);
			continue;
		}

		//extract different command element from a line
		vector<string> vec ;  //output vector container
		istringstream iss(s);
		copy(istream_iterator<string>(iss),istream_iterator<string>(),vec.beign());
		if(vec.size()<3)
			cout << "command error in the source file" << endl;
			break;
		else
		{
			m_trivec.first = vec[0];  //command 

			if(m_set.find(vec[1]))
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

Parser::HasNext()
{
	return !m_ifs.eof();
}



























		
