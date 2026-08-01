#include "Router.h"

HttpResponse Router::route(const HttpRequest& request)
{
    HttpResponse response;

    if (request.path == "/")
    {
        response.statusCode = 200;
        response.statusMessage = "OK";

        response.headers["Content-Type"] = "text/html";

        response.body = "<h1>Home Page</h1>";
    }
    else if (request.path == "/about")
    {
        response.statusCode = 200;
        response.statusMessage = "OK";

        response.headers["Content-Type"] = "text/html";

        response.body ="<h1>About Page</h1>";
    }
    else if (request.path == "/contact")
    {
        response.statusCode = 200;
        response.statusMessage = "OK";

        response.headers["Content-Type"] = "text/html";

        response.body ="<h1>Contact Page</h1>";
    }
    else
    {
        response.statusCode = 404;
        response.statusMessage = "Not Found";

        response.headers["Content-Type"] = "text/html";

        response.body ="<h1>404 Not Found</h1>";
    }

    return response;
}