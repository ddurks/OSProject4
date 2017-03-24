//David Durkin and Chris Beaufils
//Configuration file processing class

#include "Config.h"
#include <string.h>
#include <string>
#include <iostream>

//Constructor, set defaults
Config::Config(){
    PERIOD_FETCH = 180.0;
    NUM_FETCH = 1;
    NUM_PARSE = 1;
    SEARCH_FILE = "Search.txt";
    SITE_FILE = "Sites.txt";
}

//Read in config file
void Config::readConfig(std::string filename){
    infile.open(filename.c_str());
    if(!infile){
        std::cout << "Config Does Not Exist\n";
        exit(1);
    }
    read();
    SiteSearch();
}

//Set variables based on config file
void Config::read(){
    std::string line, delimiter="=", var, val;
    while(getline(infile, line)){
        var = line.substr(0, line.find(delimiter));
        val = line.substr(line.find(delimiter)+1);
        //std::cout << var << "~" << val << std::endl;
        if(var == "PERIOD_FETCH"){
            if(val != "")
                PERIOD_FETCH = std::stod(val);
        }
        else if(var == "NUM_FETCH"){
            if(val != "")
                NUM_FETCH = std::stoi(val);
            if(NUM_FETCH > 8){
                std::cout << "Too many fetch threads, set to maximum value of 8.\n";
                NUM_FETCH = 8;
            }
            else if(NUM_FETCH < 1){
                std::cout << "Too few fetch threads, set to minimum value of 1.\n";
                NUM_FETCH = 1;
            }
        }
        else if(var == "NUM_PARSE"){
            if(val != "")
                NUM_PARSE = std::stoi(val);
            if(NUM_PARSE > 8){
                std::cout << "Too many parse threads, set to maximum value of 8.\n";
                NUM_PARSE = 8;
            }
            else if(NUM_PARSE < 1){
                std::cout << "Too few parse threads, set to minimum value of 1.\n";
                NUM_PARSE = 1;
            }
        }
        else if(var == "SEARCH_FILE"){
            SEARCH_FILE = val;
        }
        else if(var == "SITE_FILE"){
            SITE_FILE = val;
        }
        else{
            std::cout << "Warning: unknown variable in config file\n";
        }
    }
}

//Fill vectors from site and search files
void Config::SiteSearch(){
    sitefile.open(SITE_FILE);
    if(!sitefile){
        std::cout << "SITE_FILE: " << SITE_FILE << " does not exist\n";
        exit(1);
    }
    std::string line;
    while(getline(sitefile, line)){
        sites.push_back(line);
    }
    searchfile.open(SEARCH_FILE);
    if(!searchfile){
        std::cout << "SEARCH_FILE: " << SEARCH_FILE << " does not exist\n";
        exit(1);
    }
    while(getline(searchfile, line)){
        searches.push_back(line);
    }
}
