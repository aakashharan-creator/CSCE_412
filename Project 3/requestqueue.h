#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <iostream>
#include <queue>
#include "request.h"
using namespace std; 

class RequestQueue {
    private:
        queue<Request> requests;
        int MAX_LEN;

    public:
        RequestQueue(){};
        RequestQueue(int num_req) : MAX_LEN(num_req){};
        bool addRequest(Request req);
        Request getNextRequest();
        bool hasNext() { return requests.size() > 0; };
        float currThreshold() { return static_cast< float >(requests.size()) / static_cast< float >(MAX_LEN); };
};

#endif 