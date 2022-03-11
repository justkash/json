/*
 * File: jsonboolean.cpp
 *
 * Created By: Akash Melethil, Bryce Besler
 * Created: 2014.10.25
 *
 * Description:
 *  This class represents a json boolean.
 *
 * History:
 *  2014.10.25    Akash Melethil    Created
 *
 * Notes:
 *  - This is an immutable class
 */

#include <json/jsonboolean.hpp>

namespace json {

    void JsonBoolean::init(const char* c_str) {
        const char* ptr = Json::find_next_non_space_char(c_str);
        if (*ptr == 't') {
            bool check = Json::check_contains(ptr, "true");
            if (!check)
                throw("[Error] Invalid json boolean; true spelled incorrectly");
            is_true_ = true;
        }
        else if (*ptr == 'f') {
            bool check = Json::check_contains(ptr, "false");
            if (!check)
                throw("[Error] Invalid json boolean; false spelled incorrectly");
            is_true_ = false;
        }
        else {
            throw("[Error] Invalid json boolean; true/false not found");
        }
    }

    JsonBoolean::JsonBoolean(const std::string& str) {
        const char* c_str = str.c_str();
        init(c_str);
    }

    JsonBoolean::JsonBoolean(const char* c_str) {
        init(c_str);
    }

    JsonBoolean::JsonBoolean(bool val) {
        if (val) {
            is_true_ = true;
        }
        else {
            is_true_ = false;
        }
    }

    bool JsonBoolean::get_bool() const {
        return is_true_;
    }

    std::string JsonBoolean::stringify() {
        if (is_true_)
            return "true";
        else
            return "false";
    }

} // json namespace
