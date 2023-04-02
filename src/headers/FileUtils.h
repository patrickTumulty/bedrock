//
// Created by Patrick Tumulty on 5/15/22.
//

#ifndef RHC_FILEUTILS_H
#define RHC_FILEUTILS_H

#include <string>

namespace FileUtils
{
    void writeStringToFile(const std::string& fullpath, const std::string& str);
    static char pathSeparator();
};


#endif //RHC_FILEUTILS_H
