/*
 * Author: Akash Melethil
 * Last Updated: Oct/24/2014
 */

#include "jsonstring.hpp"

#include <string.h>

JsonString::JsonString(const std::string& str) {
    const char* c_str = str.c_str();
    const char* first_quote = Json::find_next_char(c_str, '"');
    if (*first_quote == '\0') {
        // Assume that str is a regular string
        len_ = str.size();
        str_ = new char[len_ + 1];
        if (str_ == 0)
            throw("[Error] Unsuccessful memory allocation for JsonString");
        strcpy(str_, c_str);
        json_str_ = 0;
    }
    else {
        // Assume that str is a json string
        const char* second_quote = Json::find_next_char(first_quote + 1, '"');
        if (second_quote == '\0')
            throw("[Error] Invalid Json string; missing ending double quotes.");
        len_ = second_quote - first_quote - 1;
        json_str_ = new char[len_ + 3];
        if (json_str_ == 0)
            throw("[Error] Unsuccessful memory allocation for JsonString");
        strncpy(json_str_, first_quote, len_ + 2);
        *(json_str_ + len_ + 4) = '\0';
        str_ = 0;
    }
    byte_size_ = len_ + 2;
}

JsonString::JsonString(const JsonString& src) {
    copy(src);
}

const JsonString& JsonString::operator=(const JsonString& rhs) {
    copy(rhs);
    return *this;
}

JsonString::~JsonString() {
    destroy();
}

std::string JsonString::get_string() {
    if (str_ != 0) {
        std::string temp(str_);
        return temp;
    }
    else {
        str_ = new char[len_ + 1];
        strncpy(str_, json_str_ + 1, len_);
        *(str_ + len_) = '\0';
        std::string temp(str_);
        return temp;
    }
}

std::string JsonString::stringify() {
    if (json_str_ != 0) {
        std::string temp(json_str_);
        return temp;
    }
    else {
        json_str_ = new char[len_ + 3];
        strncpy(json_str_ + 1, str_, len_);
        *json_str_ = '"';
        *(json_str_ + len_ + 1) = '"';
        *(json_str_ + len_ + 2) = '\0';
        std::string temp(json_str_);
        return temp;
    }
}

void JsonString::copy(const JsonString& src) {
    destroy();
    len_ = src.len_;
    byte_size_ = len_ + 2;
    if (src.json_str_ != 0) {
        json_str_ = new char[len_ + 3];
        if (json_str_ == 0)
            throw("[Error] Unsuccessful memory allocation for JsonString");
        strcpy(json_str_, src.json_str_);
    }
    else
        json_str_ = 0;
    if (src.str_ != 0) {
        str_ = new char[len_ + 1];
        if (str_ == 0)
            throw("[Error] Unsuccessful memory allocation for JsonString");
        strcpy(str_, src.str_);
    }
    else
        str_ = 0;
}

void JsonString::destroy() {
    delete [] json_str_;
    json_str_ = NULL;
    delete [] str_;
    str_ = NULL;
}   
