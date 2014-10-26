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

bool Json::check_contains(const char* big_str, const char* small_str) {
    const char* small_ptr = small_str;
    const char* big_ptr = big_str;
    while (*small_ptr != '\0') {
        if (*small_ptr != *big_ptr) return false;
        ++small_ptr;
        ++big_ptr;
    }
    return true;
}
