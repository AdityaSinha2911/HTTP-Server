#include "Router.h"
#include "../file/FileReader.h"
#include "../utils/MimeTypes.h"
#include <optional>

HttpResponse Router::route(const HttpRequest& request)
{
    HttpResponse response;

    FileReader reader;

    std::string filePath;

    if (request.path == "/")
    {
        filePath = "public/index.html";
    }
    else
    {
        filePath = "public" + request.path;
    }

    std::optional<std::string> content =
        reader.read(filePath);

    // File not found
    if (!content)
    {
        response.statusCode = 404;
        response.statusMessage = "Not Found";

        response.headers["Content-Type"] = "text/html";
        
        // 404 error handling
        response.body =
            "<html>"
            "<head><title>404 Not Found</title></head>"
            "<body>"
            "<h1>404 Not Found</h1>"
            "<p>The requested resource was not found.</p>"
            "</body>"
            "</html>";

        return response;
    }

    // File found
    response.statusCode = 200;
    response.statusMessage = "OK";

    response.headers["Content-Type"] =
        MimeTypes::getType(filePath);

    response.body = *content;

    return response;
}