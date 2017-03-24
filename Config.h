//David Durkin and Chris Beaufils
//Configuration file processing class

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

class Config {
public:
    std::vector<std::string> sites;
    std::vector<std::string> searches;
    double PERIOD_FETCH;
    int NUM_FETCH, NUM_PARSE;
    std::string SEARCH_FILE, SITE_FILE;
    Config();
    void readConfig(std::string filename);
    void read(void);
    void SiteSearch(void);
private:
    std::ifstream infile, sitefile, searchfile;
};
