//
// Created by Patrick Tumulty on 6/2/22.
//

#include "time_utils.h"
#include <ctime>
#include <sstream>

/**
 * Get current month date string M-D-YYYY
 *
 * @return date string
 */
std::string TimeUtils::getDateString()
{
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    std::stringstream ss;
    ss << now->tm_mon << '-';
    ss << now->tm_mday << '-';
    ss << (now->tm_year + 1900);
    return ss.str();
}
