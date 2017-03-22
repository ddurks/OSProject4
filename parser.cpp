#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "parser.h"

std::string get_file_contents(const char *filename){
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    std::ostringstream contents;
    contents << in.rdbuf();
    in.close();
    return(contents.str());
  }
}

void occurences(std::string in) {

  int occurrences = 0;
  std::string::size_type pos = 0;
  std::string target = "cnn";
  while ((pos = in.find(target, pos )) != std::string::npos) {
    ++ occurrences;
    pos += target.length();
  }
  std::cout << occurrences << std::endl;

}
