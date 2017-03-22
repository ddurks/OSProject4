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
    SiteSearch();
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

void Config::SiteSearch(){
    sitefile.open(SITE_FILE);
    std::string line;
    while(getline(sitefile, line)){
        sites.push_back(line);
    }
    searchfile.open(SEARCH_FILE);
    while(getline(searchfile, line)){
        searches.push_back(line);
    }
}
