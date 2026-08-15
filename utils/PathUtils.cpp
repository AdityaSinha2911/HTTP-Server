#include "PathUtils.h"

bool PathUtils::isSafePath(const std::string& path)
{
    // Reject parent-directory traversal
    if (path.find("..") != std::string::npos)
    {
        return false;
    }

    return true;
}