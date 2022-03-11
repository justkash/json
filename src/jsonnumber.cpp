/*
 * File: jsonnumber.cpp
 *
 * Created By: Akash Melethil, Bryce Besler
 * Created: 2014.10.25
 *
 * Description:
 *  This class represents a json number type.
 *
 * History:
 *  2014.10.25    Akash Melethil    Created
 *
 * Notes:
 *  - This is an immutable class
 *  - This class is able to check whether a parsed string contained a floating point
 *    number or an integer (is_int())
 */

#include <cstdlib>
#include <cctype>

#include <json/jsonnumber.hpp>

namespace json {

    void JsonNumber::init(const char* c_str) {
        char* end_ptr;
        double_val_ = strtod(c_str, &end_ptr);
        const char* ptr = c_str + 1;
        is_int_ = true;
        while (*ptr != '\0') {
            if (*ptr == '.') {
                is_int_ = false;
                break;
            }
            ++ptr;
        }
        byte_size_ = get_int_digit_count();
        decimal_count_ = 0;

        if (!is_int_) {
            int ctr = 0;
            ++ptr;
            while (*ptr != '\0') {
                if (isdigit(*ptr)) 
                    ++ctr;
                ++ptr;
            }
            decimal_count_ = ctr; 
            byte_size_ += (decimal_count_ + 1);    
        }
    }

    JsonNumber::JsonNumber(const std::string& str) {
        const char* c_str = str.c_str();
        init(c_str);
    }

    JsonNumber::JsonNumber(const char* c_str) {
        init(c_str);
    }

    JsonNumber::JsonNumber(double num) {
        is_int_ = false;
        double_val_ = num;
        decimal_count_ = get_decimal_digit_count();
        int int_digit_count = get_int_digit_count();
        byte_size_ = int_digit_count + decimal_count_ + 1;
    }

    JsonNumber::JsonNumber(int num) {
        is_int_ = true;
        double_val_ = (double)num;
        decimal_count_ = 0;
        byte_size_ = get_int_digit_count();
    }

    double JsonNumber::get_double() const {
        return double_val_;
    }

    int JsonNumber::get_int() const {
        return (int)double_val_;
    }

    bool JsonNumber::is_int() const {
        return is_int_;
    }

    std::string JsonNumber::stringify() {
        char temp[byte_size_ + 1];
        if (is_int_) {
            sprintf(temp, "%d", (int)double_val_);
        }
        else {
            sprintf(temp, "%.*f", decimal_count_, double_val_);
        }
        return std::string(temp);
    }

    int JsonNumber::get_int_digit_count() {
        int val = (int)double_val_;
        int digits = 0;
        if (val < 1)
            ++digits;
        while (val) {
            val *= 0.1;
            ++digits;
        }
        return digits;
    }

    int JsonNumber::get_decimal_digit_count() {
        double val = double_val_;                                                        
        int int_part = 0;
        int ctr = 0;
        do {
            ++ctr;
            int_part = (int)(val + 0.5);
            val -= int_part;
            val *= 10;
        } while (val > 0);
        return ctr - 1;
    }

} // json namespace
