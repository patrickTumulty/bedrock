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
