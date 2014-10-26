/*
 * Author: Akash Melethil
 * Last Updated: Oct/25/2014
 */

#include "jsonboolean.h"

JsonBoolean::JsonBoolean(const std::string& str) {
    const char* c_str = str.c_str();
    const char* ptr = Json::find_next_non_space_char(c_str);
    if (*ptr == 't') {
        bool check = Json::check_contains(ptr, "true");
        if (!check)
            throw("[Error] Invalid json boolean; true spelled incorrectly");
        is_true_ = true;
        byte_size_ = 4;
    }
    else if (*ptr == 'f') {
        bool check = Json::check_contains(ptr, "false");
        if (!check)
            throw("[Error] Invalid json boolean; false spelled incorrectly");
        is_true_ = false;
        byte_size_ = 5;
    }
    else {
        throw("[Error] Invalid json boolean; true/false not found");
    }
}

JsonBoolean::JsonBoolean(const char* str) {
    const char* ptr = Json::find_next_non_space_char(str);
    if (*ptr == 't') {
        bool check = Json::check_contains(ptr, "true");
        if (!check)
            throw("[Error] Invalid json boolean; true spelled incorrectly");
        is_true_ = true;
        byte_size_ = 4;
    }
    else if (*ptr == 'f') {
        bool check = Json::check_contains(ptr, "false");
        if (!check)
            throw("[Error] Invalid json boolean; false spelled incorrectly");
        is_true_ = false;
        byte_size_ = 5;
    }
    else {
        throw("[Error] Invalid json boolean; true/false not found");
    }
}

JsonBoolean::JsonBoolean(bool val) {
    if (val) {
        is_true_ = true;
        byte_size_ = 4;
    }
    else {
        is_true_ = false;
        byte_size_ = 5;
    }
}

bool JsonBoolean::get_bool() {
    return is_true_;
}

std::string JsonBoolean::stringify() {
    if (is_true_)
        return "true";
    else
        return "false";
}
