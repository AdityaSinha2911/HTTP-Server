#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include <string>
#include "../models/HttpRequest.h"

class HttpParser
{
public:
    HttpRequest parse(const std::string& rawRequest);
};

#endif