#include <iostream>
#include <string>

int main()
{
  std::string s("I very much_am a programmer \r\n");
  s.erase(s.begin()+s.find_first_of("/"),s.end());
  std::cout << s << std::endl;
}
