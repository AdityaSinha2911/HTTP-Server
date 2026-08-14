#include "FileReader.h"

#include <fstream>
#include <iterator>

std::optional<std::string>
FileReader::read(const std::string& filePath)
{
    std::ifstream file(
        filePath,
        std::ios::binary
    );

    if (!file.is_open())
    {
        return std::nullopt;
    }

    std::string content(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    return content;
}