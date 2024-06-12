#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <iostream>
#include <queue>
#include "request.h"
using namespace std; 

class RequestQueue {
    private:
        queue<Request> requests;
    
    public:
        void addRequest(Request req);
        Request getNextRequest();
        bool hasNext() { return requests.size() > 0; };
};

#endif 