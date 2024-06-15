/**
 * @file main.cpp
 * @brief Defines the driver program to run the load balancer project
 */

#include "loadbalancer.h"
#include "request.h"
#include "requestqueue.h"
#include "webserver.h"
#include "unistd.h"

#include <iostream>

using namespace std;

/**
 * Generates a random IP address.
 * 
 * @return A string representing a random IP address.
 */

#include <cstdlib>
#include <ctime>
#include <sstream>
string getRandomIP()
{
    stringstream ip;
    ip << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    return ip.str();
}

/**
 * Generates a random request.
 * 
 * @return A Request object with random IP addresses and time.
 */
Request getRandomRequest()
{
    string ipIn = getRandomIP();
    string ipOut = getRandomIP();
    
    int time = rand() % 20 + 1;

    return Request(ipIn, ipOut, time);
}

/**
 * Adds random requests to the load balancer indefinitely.
 * 
 * @param loadbalancer The LoadBalancer object to add requests to.
 */
void addRandomRequests(LoadBalancer& loadbalancer) {
    while (1) {
        Request to_add = getRandomRequest();

        sleep(rand() % 2 + 1);

        loadbalancer.addRequest(to_add);
        cout << "A new request has been added." << endl;
    }
}

/**
 * The main function of the program.
 * 
 * @return 0 on successful execution.
 */
int main()
{
    int num_servers = 0;
    int time_to_run = 0;

    cout << "Enter number of servers: ";
    cin >> num_servers;
    cout << "\nEnter time in seconds to run: ";
    cin >> time_to_run;

    srand(time(0));

    LoadBalancer loadbalancer(num_servers);

    int num_requests = num_servers * 100;

    for (int i = 1; i <= num_servers; i++)
        loadbalancer.addRequest(getRandomRequest());

    auto t = thread(addRandomRequests, ref(loadbalancer));
    loadbalancer.handleAllRequests();

    t.join();

    return 0;
}