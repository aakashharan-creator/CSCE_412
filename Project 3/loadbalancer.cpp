#include "loadbalancer.h"
#include <unistd.h>
#include <thread>

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
    while (1)
    {
        while (req_queue->hasNext())
        {
            if (req_queue->currThreshold() >= 0.75)
            {
                int num_servers = servers.size();

                if (num_servers < 8)
                {
                    cout << "Entering > 0.75 threshold, scaling to 8 servers." << endl;
                    for (int i = num_servers; i < 8; i++)
                        servers.push_back(new WebServer(i));
                }
            }

            if (req_queue->currThreshold() >= 0.5 && req_queue->currThreshold() < 0.75)
            {
                int num_servers = servers.size();

                if (num_servers > 6)
                {
                    cout << "going down to 0.5 < x < 0.75 threshold, scaling to 6 servers" << endl;
                    for (int s = num_servers - 1; s > 5; s--)
                    {
                        while (!servers[s]->isReady()){}
                        servers.pop_back();
                    }
                }
                else if (num_servers < 6)
                {
                    cout << "going up to 0.5 < x 0.75 thresohld, scaling to 6 servers" << endl;
                    for (int i = num_servers; i < 6; i++)
                        servers.push_back(new WebServer(i));
                }
            }

            if (req_queue->currThreshold() < 0.5 && req_queue->currThreshold() >= 0.25)
            {
                int num_servers = servers.size();

                if (num_servers > 4)
                {
                    cout << "going down to x < 0.5 threshold, scaling to 4 servers" << endl;
                    for (int s = num_servers - 1; s > 3; s--)
                    {
                        while (!servers[s]->isReady()){}
                        servers.pop_back();
                    }
                }
                else if (num_servers < 4)
                {
                    cout << "going up to x < 0.5 thresohld, scaling to 4 servers" << endl;
                    for (int i = num_servers; i < 4; i++)
                        servers.push_back(new WebServer(i));
                }
            }
            if (req_queue->currThreshold() < 0.25)
            {
                int num_servers = servers.size();

                if (num_servers > 2)
                {
                    cout << "going down to x < 0.25 threshold, scaling to 2 servers" << endl;
                    for (int s = num_servers - 1; s > 1; s--)
                    {
                        while (!servers[s]->isReady()){}
                        servers.pop_back();
                    }
                }
                else if (num_servers < 2)
                {
                    cout << "going up to x < 0.25 thresohld, scaling to 2 servers" << endl;
                    for (int i = num_servers; i < 2; i++)
                        servers.push_back(new WebServer(i));
                }
            }
            handleNextRequest();

            cout << "CURR OCCUPANCY: " << req_queue->currThreshold() << endl;
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