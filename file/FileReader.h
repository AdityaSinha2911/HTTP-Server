#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>

class FileReader
{
public:
    std::string read(const std::string& filePath);
};

#endif