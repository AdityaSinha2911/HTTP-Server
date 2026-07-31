#include "HttpParser.h"
#include <sstream>

HttpRequest HttpParser::parse(const std::string& rawRequest)
{
    HttpRequest request;

    // Create a stream from the raw HTTP request
    std::istringstream requestStream(rawRequest);

    // Store the first line (Request Line)
    std::string requestLine;

    // Read the first line
    std::getline(requestStream, requestLine);

    // Remove '\r' if present
    if (!requestLine.empty() && requestLine.back() == '\r'){
        requestLine.pop_back();
    }

    // Create another stream for the request line
    std::istringstream lineStream(requestLine);

    // Extract Method, Path and Version
    lineStream >> request.method>> request.path>> request.version;

    return request;
}