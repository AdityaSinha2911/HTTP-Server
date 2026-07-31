#include "HttpParser.h"
#include <sstream>

HttpRequest HttpParser::parse(const std::string& rawRequest)
{
    HttpRequest request;

    // Create a stream from the raw HTTP request
    std::istringstream requestStream(rawRequest);

    // Store the first line (Request Line)
    std::string line;

    // Read the first line
    std::getline(requestStream, line);

    // Remove '\r' if present
    if (!line.empty() && line.back() == '\r'){
        line.pop_back();
    }

    // Create another stream for the request line
    std::istringstream lineStream(line);

    // Extract Method, Path and Version
    lineStream >> request.method>> request.path>> request.version;


    // Parse Headers
    
    while (std::getline(requestStream, line))
    {
        // Remove '\r'
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        // Blank line = End of Headers
        if (line.empty())
        {
            break;
        }

        // Find ':'
        size_t colonPos = line.find(':');

        if (colonPos == std::string::npos)
        {
            continue;
        }

        std::string key = line.substr(0, colonPos);

        std::string value = line.substr(colonPos + 2);

        request.headers[key] = value;
    }

    return request;
}