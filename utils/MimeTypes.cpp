#include "MimeTypes.h"

std::string MimeTypes::getType(const std::string& filePath)
{
    size_t dotPosition = filePath.find_last_of('.');

    // No extension found
    if (dotPosition == std::string::npos)
    {
        return "application/octet-stream";
    }

    std::string extension = filePath.substr(dotPosition);

    if (extension == ".html" || extension == ".htm")
    {
        return "text/html";
    }

    if (extension == ".css")
    {
        return "text/css";
    }

    if (extension == ".js")
    {
        return "application/javascript";
    }

    if (extension == ".json")
    {
        return "application/json";
    }

    if (extension == ".txt")
    {
        return "text/plain";
    }

    if (extension == ".png")
    {
        return "image/png";
    }

    if (extension == ".jpg" || extension == ".jpeg")
    {
        return "image/jpeg";
    }

    if (extension == ".gif")
    {
        return "image/gif";
    }

    if (extension == ".svg")
    {
        return "image/svg+xml";
    }

    // Unknown file type
    return "application/octet-stream";
}