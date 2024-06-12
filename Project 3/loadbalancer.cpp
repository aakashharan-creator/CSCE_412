#include "loadbalancer.h"
#include <unistd.h>
#include <thread>


void LoadBalancer::addRequest(Request req) {
    req_queue.addRequest(req);
}

LoadBalancer::~LoadBalancer() {
    cout << "Gracefully terminating..." << endl;

    for (thread &t : all_threads)
        if (t.joinable())
            t.join();

    for (int i = 0; i < servers.size(); i++)
        delete servers[i];
}

void LoadBalancer::handleAllRequests() {
    while (req_queue.hasNext())
        handleNextRequest();
}

void LoadBalancer::handleNextRequest() {
    Request nextRequest = req_queue.getNextRequest();
    int serverId = getNextFree();

    cout << "Server " << serverId << " is handling request for " << nextRequest.getIpIn() << " and " << nextRequest.getIpOut() << " for " << nextRequest.getTime() << " seconds" << endl;
    all_threads.emplace_back(&WebServer::handleRequest, servers[serverId], nextRequest);

    this_thread::sleep_for(0.1s);
}

int LoadBalancer::getNextFree() {
    int serverId = pollServers();
    
    while (serverId == -1) {
        cout << "no free servers, waiting" << endl;
        sleep(1); 
        serverId = pollServers();
    }

    return serverId;
}

int LoadBalancer::pollServers() {
    int i = 0;
    for (i = 0; i < servers.size(); i++)
    {
        if (servers[i]->isReady())
            return i;
    }
    
    // if (i < MAX_SERVERS) {
    //     servers.push_back(new WebServer(rand()));
    //     return servers.size() - 1;
    // }

    return -1;
}

LoadBalancer::LoadBalancer(int num_servers) {
    for (int i = 0; i < num_servers; i++)
        servers.push_back(new WebServer(i));
}