#include "FileReader.h"

#include <fstream>
#include <iterator>

std::string FileReader::read(const std::string& filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        return "";
    }

    std::string content(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    file.close();

    return content;
}