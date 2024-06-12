#include "loadbalancer.h"
#include "request.h"
#include "requestqueue.h"
#include "webserver.h"
#include "unistd.h"

#include <iostream>

using namespace std;

// getRandomIP is an AI generated function
#include <cstdlib>
#include <ctime>
#include <sstream>

string getRandomIP()
{
    stringstream ip;
    ip << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    return ip.str();
}

Request getRandomRequest()
{
    string ipIn = getRandomIP();
    string ipOut = getRandomIP();
    
    int time = rand() % 10 + 1;

    return Request(ipIn, ipOut, time);
}

void addRandomRequests(LoadBalancer& loadbalancer) {
    while (1) {
        Request to_add = getRandomRequest();
        loadbalancer.addRequest(to_add);
        sleep(rand() % 15 + 1);
        cout << "added a new request" << endl;
    }
}

int main()
{
    int num_servers = 0;
    int time_to_run = 0;

    cout << "enter number of servers: ";
    cin >> num_servers;
    cout << "\nenter time to run: ";
    cin >> time_to_run;

    srand(time(0)); // Seed the random number generator with current time

    LoadBalancer loadbalancer(num_servers);

    int num_requests = num_servers * 100;

    for (int i = 1; i <= num_requests; i++)
        loadbalancer.addRequest(getRandomRequest());

    auto t = thread(addRandomRequests, ref(loadbalancer));

    loadbalancer.handleAllRequests();

    t.join();

    return 0;
}