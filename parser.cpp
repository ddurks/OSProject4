#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "parser.h"

int occurrences(std::string in, std::string word) {

  int occurrences = 0;
  std::string::size_type pos = 0;
  while ((pos = in.find(word, pos )) != std::string::npos) {
    ++ occurrences;
    pos += 1;
  }
  return occurrences;

}
