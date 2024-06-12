#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"
#include <iostream>

using namespace std;

class WebServer {
    private:
        bool ready;
        int serverId;

    public:
        bool isReady() { return ready; };
        void handleRequest(Request req);
        WebServer(int id) : serverId(id), ready(true) {};
};

#endif