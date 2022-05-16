//
// Created by Patrick Tumulty on 5/15/22.
//

#ifndef RHC_FILEUTILS_H
#define RHC_FILEUTILS_H

#include <string>

class FileUtils
{
public:
    static void writeStringToFile(const std::string& filename, const std::string& str);

};


#endif //RHC_FILEUTILS_H
