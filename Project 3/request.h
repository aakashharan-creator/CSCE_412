/**
 * @file request.h
 * @brief Defines the Request class which represents a Request
 */


#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>

using namespace std;

/**
 * @brief The Request class represents a request with input IP, output IP, and processing time.
 */
class Request {
    private:
        string IpIn; /**< The input IP address */
        string IpOut; /**< The output IP address */
        int processTime; /**< The processing time in seconds */

    public:
        /**
         * @brief Constructs a new Request object.
         * 
         * @param in The input IP address
         * @param out The output IP address
         * @param time The processing time in milliseconds
         */
        Request(string in, string out, int time) : IpIn(in), IpOut(out), processTime(time){};

        /**
         * @brief Gets the input IP address.
         * 
         * @return The input IP address
         */
        string getIpIn() { return IpIn; }

        /**
         * @brief Gets the output IP address.
         * 
         * @return The output IP address
         */
        string getIpOut() { return IpOut; }

        /**
         * @brief Gets the processing time in milliseconds.
         * 
         * @return The processing time in milliseconds
         */
        int getTime() { return processTime; }
};

#endif