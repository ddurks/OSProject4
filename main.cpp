#include "Config.h"
#include "parser.h"
#include "getinmemory.h"
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include "WorkQueue.h"

Config set("testconfig");
int timer = 1;

struct siteItem {
    pthread_t id;
    std::string site;
};

struct parseItem {
    pthread_t id;
    std::string site;
    std::string data;
};

WorkQueue<siteItem> siteQueue;
WorkQueue<parseItem> parseQueue;

void fetchSiteNames(int s){
    for(int i = 0; i < set.sites.size(); i++){
        siteItem temp;
        temp.site = set.sites[i];
        siteQueue.add(temp);
    }
    alarm(1);
}

void* callCurl(void *in){
    struct siteItem *newItem;
    newItem = (struct siteItem *) in;
    char *s = &newItem->site[0];
    std::string data = curl(s);
    parseItem temp;
    temp.site = newItem->site;
    temp.data = data;
    parseQueue.add(temp);

    return NULL;
}

std::string get_time_now(){
    std::chrono::time_point<std::chrono::system_clock> start;
    start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    std::string time_now = std::ctime(&start_time);
    time_now.pop_back();
    return time_now;
}


int main(int argc, char *argv[]){
    curl_global_init(CURL_GLOBAL_ALL);
    std::string site;
    int num_occ, rc;
    char* s;
    pthread_t fetchthreads[set.NUM_FETCH];
    struct siteItem sIs[set.NUM_FETCH];

    signal(SIGALRM, fetchSiteNames);
    alarm(timer);

    for(int i = 0; i < set.NUM_FETCH; i++){
        sIs[i].id = i;
        siteItem temp = siteQueue.remove();
        sIs[i].site = temp.site;
        std::cout << "thread creation" << std::endl;
        rc = pthread_create(&fetchthreads[i], NULL, callCurl, (void*)&sIs[i]); assert (rc == 0);
        std::cout << "thread created:" << i << std::endl;
    }

    for (int i = 0; i < set.NUM_FETCH; i++) {
        rc = pthread_join(fetchthreads[i], NULL); assert(rc == 0);
    }

    for(int i = 0; i < set.sites.size(); i++){
        parseItem temp = parseQueue.remove();
        std::cout << temp.site << "\n-----------\n";
    }

/*
    for(int i = 0; i < set.sites.size(); i++){
        site = set.sites[i];
        s = &site[0];
        std::string got(curl(s));

        for(int j = 0; j < set.searches.size(); j++){
            num_occ = occurrences(got, set.searches[j]);

            std::cout << get_time_now() << "," << set.searches[j] << "," << set.sites[i] << "," << num_occ << std::endl;
        }
    }
*/
}
