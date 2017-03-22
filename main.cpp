#include "Config.h"
#include "parser.h"
#include "getinmemory.h"
#include <iostream>

int main(int argc, char *argv[]){
    Config set("testconfig");
    std::cout << "period=" << set.PERIOD_FETCH << "  fetch=" << set.NUM_FETCH << "  parse=" << set.NUM_PARSE << "  search=" << set.SEARCH_FILE << "  sites=" << set.SITE_FILE << std::endl;
    for(int i = 0; i < set.searches.size(); i++){
        std::cout << set.searches[i];
    }
    std::cout << std::endl;
    for(int i = 0; i < set.sites.size(); i++){
        std::cout << set.sites[i];
    }
    std::cout << std::endl;

    curl();

    //occurences(get_file_contents("testString.txt"));
}
