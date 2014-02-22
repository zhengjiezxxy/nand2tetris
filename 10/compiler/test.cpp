#include <iostream>
#include <fstream>
#include <sstream>

int main(int agrc, char** argv)
{
	char c1, c2, c3;
	std::istringstream("a\nb c") >> c1 >> c2 >> c3;
	std::cout << "Default  behavior: c1 = " << c1 << " c2 = " << c2 << " c3 = " << c3 << '\n';
	std::istringstream("a\nb c") >> std::noskipws >> c1 >> c2 >> c3;
	std::cout << "noskipws behavior: c1 = " << c1 << " c2 = " << c2 << " c3 = " << c3 << '\n';
}
