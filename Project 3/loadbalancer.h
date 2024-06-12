#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <iostream>
#include "request.h"
#include "webserver.h"
#include "requestqueue.h"
#include <queue>
#include <thread>
#include <vector>

using namespace std;

class LoadBalancer {
    private:
        vector<WebServer*> servers;
        RequestQueue req_queue;
        int MAX_SERVERS;

    public:
        // void cullServers();
        vector<thread> all_threads;
        void handleNextRequest();
        void addRequest(Request req);
        void handleAllRequests();
        LoadBalancer(int num_servers);
        ~LoadBalancer();
        int getNextFree();
        int pollServers();
};

#endif 