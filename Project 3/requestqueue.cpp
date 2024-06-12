#include "requestqueue.h"

void RequestQueue::addRequest(Request req) {
    requests.push(req);
}

Request RequestQueue::getNextRequest() {
    if (requests.size() == 0)
        throw std::out_of_range("No requests to be processed");
        
    Request next_request = requests.front();
    requests.pop();

    return next_request;
}