#include "requestqueue.h"

/**
 * @brief Adds a request to the request queue.
 * 
 * This function adds a request to the request queue if the queue is not full.
 * If the queue is already full, the function returns false.
 * 
 * @param req The request to be added to the queue.
 * @return True if the request was added successfully, false otherwise.
 */
bool RequestQueue::addRequest(Request req) {
    if (requests.size() == MAX_LEN)
        return false;
  
    requests.push(req);
    return true;
}

/**
 * @brief Retrieves the next request from the request queue.
 * 
 * This function returns the next request in the queue and removes it from the queue.
 * If the queue is empty, an exception of type std::out_of_range is thrown.
 * 
 * @return The next request in the queue.
 * @throws std::out_of_range If the queue is empty.
 */
Request RequestQueue::getNextRequest() {
    if (requests.size() == 0)
        throw std::out_of_range("No requests to be processed");

    Request next_request = requests.front();
    requests.pop();

    return next_request;
}