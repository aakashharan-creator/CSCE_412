#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>

using namespace std;

class Request {
    private:
        string IpIn;
        string IpOut;
        int processTime;

    public:
        Request(string in, string out, int time) : IpIn(in), IpOut(out), processTime(time){};
        string getIpIn() { return IpIn; }
        string getIpOut() { return IpOut; }
        int getTime() { return processTime; }
};

#endif