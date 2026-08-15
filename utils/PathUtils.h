#ifndef PATHUTILS_H
#define PATHUTILS_H

#include <string>

class PathUtils
{
public:
    static bool isSafePath(const std::string& path);
};

#endif