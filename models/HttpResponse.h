#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>
#include <unordered_map>

struct HttpResponse
{
    int statusCode;

    std::string statusMessage;

    std::unordered_map<std::string, std::string> headers;

    std::string body;
};

#endif