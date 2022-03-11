/*
 * File: jsonnull.cpp
 *
 * Created By: Akash Melethil, Bryce Besler
 * Created: 2014.10.25
 *
 * Description:
 *  This class represents a json null type.
 *
 * History:
 *  2014.10.25    Akash Melethil    Created
 *
 * Notes:
 *  - This is an immutable class
 *  - This class was created largely for completion and has few use cases
 */

#include <json/jsonnull.hpp>

namespace json {

    JsonNull::JsonNull() {}

    void JsonNull::init(const char* c_str) {
        const char* ptr = Json::find_next_non_space_char(c_str);
        if (*ptr == 'n') {
            bool check = Json::check_contains(ptr, "null");
            if (!check)
                throw("[Error] Invalid json null string; null spelled incorrectly");
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

    std::string JsonNull::stringify() {
        return "null";
    }

} // json namespace
