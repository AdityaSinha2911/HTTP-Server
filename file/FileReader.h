#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <optional>

// for checking file have content or not. 

class FileReader
{
public:
    std::optional<std::string> read(const std::string& filePath);
};

#endif