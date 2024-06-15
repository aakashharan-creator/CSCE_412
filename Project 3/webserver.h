/**
 * @file webserver.h
 * @brief This file contains the declaration of the WebServer class.
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"
#include <iostream>

using namespace std;

/**
 * @class WebServer
 * @brief Represents a web server that handles incoming requests.
 */
class WebServer {
    private:
        bool ready; /**< Flag indicating if the server is ready to handle requests. */

    public:
        /**
         * @brief Checks if the server is ready to handle requests.
         * @return True if the server is ready, false otherwise.
         */
        bool isReady() { return ready; };

        /**
         * @brief Handles the incoming request.
         * @param req The request to be handled.
         */
        void handleRequest(Request req);

        /**
         * @brief Constructs a new WebServer object.
         * @param id The identifier of the server.
         */
        WebServer(int id) : ready(true) {};
};

#endif