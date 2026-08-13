#ifndef MIMETYPES_H
#define MIMETYPES_H

#include <string>

class MimeTypes
{
public:
    static std::string getType(const std::string& filePath);
};

#endif