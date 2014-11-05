/*
 * File: jsonnumber.hpp
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

#ifndef JSONNUMBER_HPP
#define JSONNUMBER_HPP

#include <string>
#include <cstddef>

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
