/*
 * Author: Akash Melethil
 * Last Updated: Oct/25/2014
 */

#include "jsonnull.hpp"

JsonNull::JsonNull(const std::string& str) {
    const char* c_str = str.c_str();
    const char* ptr = Json::find_next_non_space_char(c_str);
    if (*ptr == 'n') {
        bool check = Json::check_contains(ptr, "null");
        if (!check)
            throw("[Error] Invalid json null; null incorrectly");
        byte_size_ = 4;
    }
    else {
        throw("[Error] Invalid json null");
    }
}

JsonNull::JsonNull() {
    byte_size_ = 4;
}

std::string JsonNull::stringify() {
    return "null";
}


