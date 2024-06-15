
/**
 * @brief Handles a request by putting the server in a non-ready state for a specified amount of time.
 * 
 * This function is responsible for handling a request by putting the server in a non-ready state for a specified amount of time.
 * It sets the `ready` flag to `false`, sleeps for the specified amount of time, and then sets the `ready` flag back to `true`.
 * 
 * @param req The request object containing the time to sleep.
 */
#include "webserver.h"
#include <chrono>
#include <unistd.h>

void WebServer::handleRequest(Request req) {
    ready = false;
    sleep(req.getTime());
    ready = true;
}