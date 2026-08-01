#ifndef RESPONSEBUILDER_H
#define RESPONSEBUILDER_H

#include <string>
#include "../models/HttpResponse.h"

class ResponseBuilder
{
public:
    std::string build(const HttpResponse& response);
};

#endif