#include "loadbalancer.h"
#include <unistd.h>
#include <thread>
#include <vector>

using namespace std;

void LoadBalancer::addRequest(Request req)
{
    if (!req_queue->addRequest(req))
        cout << "Discarding a request." << endl;
}

LoadBalancer::~LoadBalancer()
{
    cout << "Gracefully terminating..." << endl;

    for (thread &t : all_threads)
        if (t.joinable())
            t.join();

    for (int i = 0; i < servers.size(); i++)
        delete servers[i];
}

LoadBalancer::LoadBalancer(int num_servers)
{
    MAX_SERVERS = 8;
    req_queue = new RequestQueue(num_servers * 100);
}

void LoadBalancer::handleAllRequests()
{
    vector<int> servers_for_thresholds = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<float> thresholds = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};
    
    while (1)
    {
        while (req_queue->hasNext())
        {
            int curr = 0;
            int num_servers = servers.size();
            float occupancy = req_queue->currThreshold();

            while (thresholds[curr] < occupancy){
                curr++;
            }

            if (num_servers < servers_for_thresholds[curr])
            {
                cout << "entered " << thresholds[curr] << " threshold, scaling up to " << servers_for_thresholds[curr] << " servers." << endl;
                for (int i = num_servers; i < servers_for_thresholds[curr]; i++)
                    servers.push_back(new WebServer(i));
            }
            else if (num_servers > servers_for_thresholds[curr])
            {
                cout << "entered " << thresholds[curr] << " threshold, scaling down to " << servers_for_thresholds[curr] << " servers." << endl;
                for (int s = num_servers; s > servers_for_thresholds[curr]; s--) {
                    while (!servers[s - 1]->isReady()) {}
                    servers.pop_back();
                }
            }

            handleNextRequest();
        }
        cout << "REQUEST QUEUE EMPTY" << endl;
        this_thread::sleep_for(1s);
    }
}

void LoadBalancer::handleNextRequest()
{
    Request nextRequest = req_queue->getNextRequest();
    int serverId = getNextFree();

    cout << "Server " << serverId << " is handling request for " << nextRequest.getIpIn() << " and " << nextRequest.getIpOut() << " for " << nextRequest.getTime() << " seconds" << endl;
    all_threads.emplace_back(&WebServer::handleRequest, servers[serverId], nextRequest);

    this_thread::sleep_for(0.1s);
}

int LoadBalancer::getNextFree()
{
    int serverId = pollServers();

    while (serverId == -1)
    {
        cout << "no free servers, waiting" << endl;
        sleep(1);
        serverId = pollServers();
    }

    return serverId;
}

int LoadBalancer::pollServers()
{
    int i = 0;
    for (i = 0; i < servers.size(); i++)
    {
        if (servers[i]->isReady())
            return i;
    }

    return -1;
}