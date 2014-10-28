/*
 * Author: Akash Melethil
 * Last Updated: Oct/25/2014
 */

#include "jsonnull.hpp"

void JsonNull::init(const char* c_str) {
    const char* ptr = Json::find_next_non_space_char(c_str);
    if (*ptr == 'n') {
        bool check = Json::check_contains(ptr, "null");
        if (!check)
            throw("[Error] Invalid json null string; null spelled incorrectly");
        byte_size_ = 4;
    }
    else {
        throw("[Error] Invalid json null");
    }
}

JsonNull::JsonNull(const std::string& str) {
    const char* c_str = str.c_str();
    init(c_str); 
}

JsonNull::JsonNull(const char* c_str) {
    init(c_str);
}

JsonNull::JsonNull() {
    byte_size_ = 4;
}

std::string JsonNull::stringify() {
    return "null";
}


