#include <string>
#include <iostream>

int main(int argc, char* argv[]) {

  int occurrences = 0;
  std::string::size_type pos = 0;
  std::string s = "FooBarFooBarFoo";
  std::string target = "Foo";
  while ((pos = s.find(target, pos )) != std::string::npos) {
    ++ occurrences;
    pos += target.length();
  }
  std::cout << occurrences << std::endl;

}
