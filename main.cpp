#include "Config.h"
#include "parser.h"
#include "getinmemory.h"
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

std::string get_time_now(){
    std::chrono::time_point<std::chrono::system_clock> start;
    start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    std::string time_now = std::ctime(&start_time);
    time_now.pop_back();
    return time_now;
}

int main(int argc, char *argv[]){
    std::string site;
    int num_occ;
    char* s;
    Config set("testconfig");
    /*
    std::cout << "period=" << set.PERIOD_FETCH << "  fetch=" << set.NUM_FETCH << "  parse=" << set.NUM_PARSE << "  search=" << set.SEARCH_FILE << "  sites=" << set.SITE_FILE << std::endl;
    for(int i = 0; i < set.searches.size(); i++){
        std::cout << set.searches[i];
    }
    std::cout << std::endl;
    for(int i = 0; i < set.sites.size(); i++){
        std::cout << set.sites[i];
    }
    std::cout << std::endl;
    */

    //std::cout << get_time_now() << std::endl;


    for(int i = 0; i < set.sites.size(); i++){
        site = set.sites[i];
        s = &site[0];
        std::string got(curl(s));

        for(int j = 0; j < set.searches.size(); j++){
            num_occ = occurrences(got, set.searches[j]);

            std::cout << get_time_now() << "," << set.searches[j] << "," << set.sites[i] << "," << num_occ << std::endl;
        }
    }

/*
    site = "http://www.cnn.com/";
    s = &site[0];
    std::string got(curl(s));

    int num = occurrences(got, "sports");
    std::cout << num << std::endl;
    */

}
