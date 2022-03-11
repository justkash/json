/*
 * File: jsonstring.cpp
 *
 * Created By: Akash Melethil, Bryce Besler
 * Created: 2014.10.24
 *
 * Description:
 *  This class represents a json string type.
 *
 * History:
 *  2014.10.24    Akash Melethil    Created
 *
 * Notes:
 *  - This is an immutable clas.
 *  - This class is smart enough to recognize if the string passed into its
 *    constructor is a json string or a normal string. It does this by looking
 *    for double quotes, if none are found, then it assumes that it is a
 *    regular string and that the user is using the class to create a json
 *    string rather than to parse it.
 */

#include <cstring>

#include <json/jsonstring.hpp>

namespace json {

    void JsonString::init(const char* c_str, size_t size) {
        const char* first_quote = Json::find_next_char(c_str, '"');
        if (*first_quote == '\0') {
            // Assume that str is a regular string
            len_ = size;
            str_ = new char[len_ + 1];
            if (str_ == NULL)
                throw RuntimeException {
                    "Unsuccessful memory allocation for JsonString", 
                    ErrorCode::ErrorWhileAllocatingMemory };
            strcpy(str_, c_str);
            json_str_ = NULL;
        }
        else {
            // Assume that str is a json string
            const char* second_quote = Json::find_next_char(first_quote + 1, '"');
            if (*second_quote == '\0')
                throw RuntimeException {
                    "Invalid Json string; missing ending double quotes", 
                    ErrorCode::InvalidJsonString };
            len_ = second_quote - first_quote - 1;
            json_str_ = new char[len_ + 3];
            if (json_str_ == 0)
                throw RuntimeException {
                    "Unsuccessful memory allocation for JsonString", 
                    ErrorCode::ErrorWhileAllocatingMemory };
            strncpy(json_str_, first_quote, len_ + 2);
            *(json_str_ + len_ + 2) = '\0';
            str_ = NULL;
        }
    }

    JsonString::JsonString(const std::string& str) {
        const char* c_str = str.c_str();
        init(c_str, str.size());
    }

    JsonString::JsonString(const char* c_str) {
        init(c_str, strlen(c_str));
    }

    JsonString::JsonString(const JsonString& src) {
        str_ = NULL;
        json_str_ = NULL;
        len_ = 0;
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
        if (src.json_str_ != 0) {
            json_str_ = new char[len_ + 3];
            if (json_str_ == 0)
                throw RuntimeException {
                    "Unsuccessful memory allocation for JsonString", 
                    ErrorCode::ErrorWhileAllocatingMemory };
            strcpy(json_str_, src.json_str_);
        }
        else
            json_str_ = 0;
        if (src.str_ != 0) {
            str_ = new char[len_ + 1];
            if (str_ == 0)
                throw RuntimeException {
                    "Unsuccessful memory allocation for JsonString", 
                    ErrorCode::ErrorWhileAllocatingMemory };
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

} // json namespace
