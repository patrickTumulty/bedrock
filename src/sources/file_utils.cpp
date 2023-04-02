//
// Created by Patrick Tumulty on 5/15/22.
//

#include "file_utils.h"
#include <fstream>

/**
 * Write string to file
 *
 * @param fullpath path
 * @param str string to write to file
 */
void FileUtils::writeStringToFile(const std::string &fullpath, const std::string &str)
{
    std::ofstream outputFileStream(fullpath);
    outputFileStream << str;
    outputFileStream.close();
}

/**
 * Get platform independent file separator character
 *
 * @return file separator character
 */
char FileUtils::pathSeparator()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}
