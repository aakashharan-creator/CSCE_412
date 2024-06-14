#include "requestqueue.h"

bool RequestQueue::addRequest(Request req) {
    if (requests.size() == MAX_LEN)
        return false;
  
    requests.push(req);
    return true;
}

Request RequestQueue::getNextRequest() {
    if (requests.size() == 0)
        throw std::out_of_range("No requests to be processed");

    Request next_request = requests.front();
    requests.pop();

    return next_request;
}