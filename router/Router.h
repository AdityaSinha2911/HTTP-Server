#ifndef ROUTER_H
#define ROUTER_H

#include "../models/HttpRequest.h"
#include "../models/HttpResponse.h"

class Router
{
public:
    HttpResponse route(const HttpRequest& request);
};

#endif