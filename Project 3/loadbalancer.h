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

/**
 * @file loadbalancer.h
 * @brief Defines the LoadBalancer class which manages the load balancing of requests among multiple web servers.
 */

/**
 * @class LoadBalancer
 * @brief Manages the load balancing of requests among multiple web servers.
 */
class LoadBalancer {
    private:
        vector<WebServer*> servers; /**< Vector of WebServer pointers representing the available web servers. */
        RequestQueue* req_queue; /**< Pointer to the RequestQueue object representing the queue of incoming requests. */
        int MAX_SERVERS; /**< Maximum number of servers that can be added to the load balancer. */

    public:
        vector<thread> all_threads; /**< Vector of thread objects representing the threads handling the requests. */

        /**
         * @brief Handles the next request in the queue.
         */
        void handleNextRequest();

        /**
         * @brief Adds a request to the request queue.
         * @param req The request to be added.
         */
        void addRequest(Request req);

        /**
         * @brief Handles all the requests in the queue.
         */
        void handleAllRequests();

        /**
         * @brief Default constructor for the LoadBalancer class.
         */
        LoadBalancer(){};

        /**
         * @brief Parameterized constructor for the LoadBalancer class.
         * @param num_servers The number of servers to be added to the load balancer.
         */
        LoadBalancer(int num_servers);

        /**
         * @brief Destructor for the LoadBalancer class.
         */
        ~LoadBalancer();

        /**
         * @brief Gets the index of the next free server.
         * @return The index of the next free server.
         */
        int getNextFree();

        /**
         * @brief Polls all the servers to check if they are available.
         * @return The number of available servers.
         */
        int pollServers();
};

#endif