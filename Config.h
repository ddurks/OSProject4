//David Durkin and Chris Beaufils
//Configuration file processing class

#include <iostream>
#include <string.h>
#include <fstream>

class Config {
public:
    double PERIOD_FETCH;
    int NUM_FETCH, NUM_PARSE;
    std::string SEARCH_FILE, SITE_FILE;
    Config(std::string filename);
    void read(void);
private:
    std::ifstream infile;
};
