#include "ResponseBuilder.h"

std::string ResponseBuilder::build(const HttpResponse& response)
{
    std::string httpResponse;

    // Status Line
    httpResponse += "HTTP/1.1 ";
    httpResponse += std::to_string(response.statusCode);
    httpResponse += " ";
    httpResponse += response.statusMessage;
    httpResponse += "\r\n";

    // Headers
    for (const auto& header : response.headers)
    {
        httpResponse += header.first;
        httpResponse += ": ";
        httpResponse += header.second;
        httpResponse += "\r\n";
    }

    // Content-Length
    httpResponse += "Content-Length: ";
    httpResponse += std::to_string(response.body.length());
    httpResponse += "\r\n";

    // Blank line
    httpResponse += "\r\n";

    // Body
    httpResponse += response.body;

    return httpResponse;
}