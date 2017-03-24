Operating Systems Project 4
David Durkin and Chris Beaufils

In order to configure and build this program, simply set the appropriate variables in the file named "config", run the command "make", which will automatically clean and compile the code. In order to run the program, use the command "./site-tester config".
Variables in the config file should be set like "PARAM=XXXXX".
The config file variables determine the fetch period (PERIOD_FETCH), the number of fetch threads (NUM_FETCH), the number of parse threads (NUM_PARSE), the file to retrieve the site names from (SITE_FILE), and the file to retrieve the search terms from (SEARCH_FILE).
If an error occurs when retrieving/curling a site, the program will return a descriptive error with the problematic site and will skip that site when parsing.
