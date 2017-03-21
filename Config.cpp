//David Durkin and Chris Beaufils
//Configuration file processing class

#include "Config.h"
#include <string.h>
#include <string>
#include <iostream>

Config::Config(std::string filename){
    PERIOD_FETCH = 180.0;
    NUM_FETCH = 1;
    NUM_PARSE = 1;
    SEARCH_FILE = "Search.txt";
    SITE_FILE = "Sites.txt";
    infile.open(filename.c_str());
    read();
}

void Config::read(){
    std::string line, delimiter="=", var, val;
    while(getline(infile, line)){
        var = line.substr(0, line.find(delimiter));
        val = line.substr(line.find(delimiter)+1);
        std::cout << var << "~" << val << std::endl;
        if(var == "PERIOD_FETCH"){
            PERIOD_FETCH = std::stod(val);
        }
        else if(var == "NUM_FETCH"){
            NUM_FETCH = std::stoi(val);
        }
        else if(var == "NUM_PARSE"){
            NUM_PARSE = std::stoi(val);
        }
        else if(var == "SEARCH_FILE"){
            SEARCH_FILE = val;
        }
        else if(var == "SITE_FILE"){
            SITE_FILE = val;
        }
    }
}

int main(int argc, char *argv[]){
    Config set("testconfig");
    std::cout << "period=" << set.PERIOD_FETCH << "  fetch=" << set.NUM_FETCH << "  parse=" << set.NUM_PARSE << "  search=" << set.SEARCH_FILE << "  sites=" << set.SITE_FILE << std::endl;
}
