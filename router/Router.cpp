#include "Router.h"
#include "../file/FileReader.h"
#include "../utils/MimeTypes.h"
#include <optional>
#include "../utils/PathUtils.h"

HttpResponse Router::route(const HttpRequest& request)
{
    HttpResponse response;

    FileReader reader;


    // Security check
    if (!PathUtils::isSafePath(request.path))
    {
        response.statusCode = 403;
        response.statusMessage = "Forbidden";

        response.headers["Content-Type"] = "text/html";

        response.body =
            "<html>"
            "<head><title>403 Forbidden</title></head>"
            "<body>"
            "<h1>403 Forbidden</h1>"
            "<p>Access to this path is forbidden.</p>"
            "</body>"
            "</html>";

        return response;
    }
    
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