#include "Router.h"
#include "../file/FileReader.h"

HttpResponse Router::route(const HttpRequest& request)
{
    HttpResponse response;

    FileReader reader;

    // Decide which file should be served
    std::string filePath;

    if (request.path == "/")
    {
        filePath = "public/index.html";
    }
    else
    {
        filePath = "public" + request.path;
    }

    // Read requested file
    std::string content = reader.read(filePath);

    // File could not be read
    if (content.empty())
    {
        response.statusCode = 404;
        response.statusMessage = "Not Found";
        response.headers["Content-Type"] = "text/html";

        response.body = "<h1>404 Not Found</h1>";

        return response;
    }

    // File successfully read
    response.statusCode = 200;
    response.statusMessage = "OK";
    response.headers["Content-Type"] = "text/html";

    response.body = content;

    return response;
}