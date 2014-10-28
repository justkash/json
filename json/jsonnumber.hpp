/*
 * Author: Akash Melethil
 * Last Updated: Oct/25/2014
 */

#ifndef JSONNUMBER_HPP
#define JSONNUMBER_HPP

#include <string>
#include <stddef.h>

#include "json.hpp"

class JsonNumber : public Json {
    public:
        JsonNumber(const char*);
        JsonNumber(const std::string&);
        JsonNumber(double num);
        JsonNumber(int num);

        double get_double();
        int get_int();
        bool is_int();
        virtual std::string stringify();

    private:
        bool is_int_;
        double double_val_;
        size_t byte_size_;
        int decimal_count_;

        int get_int_digit_count();
        int get_decimal_digit_count();
        void init(const char*);
};

#endif
