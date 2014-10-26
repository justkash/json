/*
 * Author: Akash Melehtil
 * Last Updated: Oct/24/2014
 */

#include "json.h"

#include <ctype.h>

const char* Json::find_next_char(const char* str, const char to_find) {
   const char* ptr = str;
   while (*ptr != to_find && *ptr != '\0') ++ptr;
   return ptr;
}

const char* Json::find_next_non_space_char(const char* str) {
    const char* ptr = str;
    while (isspace(*ptr) && *ptr != '\0') ++ptr;
    return ptr;
}
