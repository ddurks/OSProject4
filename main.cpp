//David Durkin and Chris Beaufils
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
#include <mutex>
#include "WorkQueue.h"

//Setting Global Variables
Config set;
int timer = 5, loop = 1, csvnum = 1;
vector<std::string> csv;
std::mutex mtx;
vector<pthread_t> fetchthreads;
vector<pthread_t> parsethreads;

//Get current timestamp function
std::string get_time_now(){
    std::chrono::time_point<std::chrono::system_clock> start;
    start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    std::string time_now = std::ctime(&start_time);
    time_now.pop_back();
    return time_now;
}

//Exit Program
void exitNow( int i = 0 ){
    loop = 0;
    std::cout << "Joining threads...\n";
}

//Structure for siteQueue items
struct siteItem {
    pthread_t id;
    std::string site;
};

//Structure for parseQueue items
struct parseItem {
    pthread_t id;
    std::string site;
    std::string data;
    std::string timestamp;
};

//site and parse queues
WorkQueue<siteItem> siteQueue;
WorkQueue<parseItem> parseQueue;

//Alarm function to fill siteQueue and thus nudge fetch threads
void fetchSiteNames(int s){
    for(unsigned int i = 0; i < set.sites.size(); i++){
        siteItem temp;
        temp.site = set.sites[i];
        siteQueue.add(temp);
    }
    alarm(timer);
}

//Add a line to the csv vector
void addLine(std::string line){
    mtx.lock();
    csv.push_back(line);
    mtx.unlock();
}

//Function called by fetch threads
void* callCurl(void *in){
    struct siteItem *newItem;
    newItem = (struct siteItem *) in;
    siteItem transfer = siteQueue.remove();
    newItem->site = transfer.site;
    char *s = &newItem->site[0];
    parseItem temp;
    temp.timestamp = get_time_now();
    std::string data = curl(s);
    temp.site = newItem->site;
    temp.data = data;
    parseQueue.add(temp);

    return NULL;
}

//Function called by parse threads
void * callOccurrences(void *in){
    int occ;
    std::string occ_string, line;
    parseItem transfer = parseQueue.remove();
    if(transfer.data != ""){
        for(unsigned int i = 0; i < set.searches.size(); i++){
            occ = occurrences(transfer.data, set.searches[i]);
            occ_string = std::to_string(occ);
            line = transfer.timestamp + "," + set.searches[i] + "," + transfer.site + "," + occ_string;
            addLine(line);
        }
    }
    return NULL;
}

//Main execution
int main(int argc, char *argv[]){
    //Set variables based on config file
    if(argc !=2){
        std::cout << "Usage: ./tester <ConfigFile>\n";
        exit(1);
    }
    set.readConfig(argv[1]);

    curl_global_init(CURL_GLOBAL_ALL);

    std::string site, csvtitle, titles = "Date & Time,Search Phrase,Site,Count";
    int rc;

    //Set up threading arrays
    fetchthreads.resize(set.NUM_FETCH);
    parsethreads.resize(set.NUM_PARSE);
    struct siteItem sIs[set.NUM_FETCH];
    struct parseItem pIs[set.NUM_PARSE];

    //Set up period fetch alarm
    signal(SIGALRM, fetchSiteNames);
    alarm(timer);

    //Main loop for threading
    while(loop){
        signal(SIGINT, exitNow);

        //Create fetch threads
        for(int i = 0; i < set.NUM_FETCH; i++){
            sIs[i].id = i;
            //std::cout << "fetch thread creation" << std::endl;
            rc = pthread_create(&fetchthreads[i], NULL, callCurl, (void*)&sIs[i]);
            if (rc != 0){
                std::cout << "Could not create fetch thread\n";
                exit(1);
            }
            //std::cout << "fetch thread created:" << i << std::endl;
        }

        //Join fetch threads
        for (int i = 0; i < set.NUM_FETCH; i++) {
            rc = pthread_join(fetchthreads[i], NULL);
            if (rc != 0){
                std::cout << "Could not join fetch thread\n";
                exit(1);
            }
        }

        //Create parse threads
        for(int i = 0; i < set.NUM_PARSE; i++){
            pIs[i].id = i;
            //std::cout << "parse thread creation" << std::endl;
            rc = pthread_create(&parsethreads[i], NULL, callOccurrences, (void*)&pIs[i]);
            if (rc != 0){
                std::cout << "Could not create parse thread\n";
                exit(1);
            }
            //std::cout << "parse thread created:" << i << std::endl;
        }

        //Join parse threads
        for (int i = 0; i < set.NUM_PARSE; i++){
            rc = pthread_join(parsethreads[i],NULL);
            if (rc != 0){
                std::cout << "Could not join parse thread\n";
                exit(1);
            }
        }

        //Write csv vector to file
        ofstream outputfile;
        csvtitle = std::to_string(csvnum) + ".csv";
        outputfile.open(csvtitle);

        outputfile << titles << "\n";
        for(unsigned int i = 0; i < csv.size(); i++){
            outputfile << csv[i] << "\n";
        }

        csvnum++;
        csv.clear();

    }
    return 0;

}
