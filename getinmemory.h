#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct MemoryStruct;

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
void curl(void);
