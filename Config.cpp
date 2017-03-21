//David Durkin and Chris Beaufils
//Configuration file processing class

#include <iostream>
#include <string.h>

class Config {
public:
    double PERIOD_FETCH;
    int NUM_FETCH, NUM_PARSE;
    string SEARCH_FILE, SITE_FILE;
    Config(string filename){
        PERIOD_FETCH = 180.0;
        NUM_FETCH = 1;
        NUM_PARSE = 1;
        SEARCH_FILE = "Search.txt";
        SITE_FILE = "Sites.txt";
        file.open(filename);
        read();
    }
    void read(){
        string line;
        while(getline(file, line)){
            std::cout << line << std::endl;
        }
    }
private:
    ifstream file;
};

int main(int argc, char argv[]){
    Config settings = Config("testconfig");
    return 0;
}
