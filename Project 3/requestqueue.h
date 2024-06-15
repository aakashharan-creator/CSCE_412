/**
 * @file requestqueue.h
 * @brief Defines the RequestQueue class which represents a queue of requests.
 */

#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <iostream>
#include <queue>
#include "request.h"

using namespace std;

/**
 * @class RequestQueue
 * @brief Represents a queue of requests.
 */
class RequestQueue {
    private:
        queue<Request> requests; /**< The queue of requests */
        int MAX_LEN; /**< The maximum length of the queue */

    public:
        /**
         @brief Default constructor for RequestQueue.
         */
        RequestQueue(){};

        /**
        @brief Parameterized constructor for RequestQueue.
         * @param num_req The maximum number of requests allowed in the queue.
         */
        RequestQueue(int num_req) : MAX_LEN(num_req){};

        /**
        @brief Adds a request to the queue.
         * @param req The request to be added.
         * @return True if the request was added successfully, false otherwise.
         */
        bool addRequest(Request req);

        /**
        @brief Retrieves the next request from the queue.
         * @return The next request in the queue.
         */
        Request getNextRequest();

        /**
         * @brief Checks if there is a next request in the queue.
         * @return True if there is a next request, false otherwise.
         */
        bool hasNext() { return requests.size() > 0; };

        /**
         @brief Calculates the current threshold of the queue.
         * @return The current threshold as a float value.
         */
        float currThreshold() { return static_cast< float >(requests.size()) / static_cast< float >(MAX_LEN); };

        /**
        @brief Retrieves the size of the queue.
         * @return The size of the queue.
         */
        int size() { return requests.size(); };
};

#endif 