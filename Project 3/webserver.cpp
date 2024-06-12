#include "webserver.h"
#include <chrono>
#include <unistd.h>

void WebServer::handleRequest(Request req) {
    ready = false;
    sleep(req.getTime());
    ready = true;
}