//
// Created by Patrick Tumulty on 5/15/22.
//

#include "FileUtils.h"
#include <fstream>

/**
 * Write string to file
 *
 * @param filename filename
 * @param str string to write to file
 */
void FileUtils::writeStringToFile(const std::string &filename, const std::string &str)
{
    std::ofstream outputFileStream(filename);
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
