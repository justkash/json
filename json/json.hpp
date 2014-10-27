/*
 * Author: Akash Melehtil
 * Last Updated: Oct/24/2014
 */

#ifndef JSON_HPP
#define JSON_HPP

#include <string>

class Json {
    public:
    static Json* parse(const std::string&);

    virtual std::string stringify() = 0;
    virtual ~Json() = 0;
   
    protected:
    static const char* find_next_char(const char*, const char);
    static const char* find_next_non_space_char(const char*);
    static const char* find_next_either_chars(const char*, const char, const char);
    static bool check_contains(const char*, const char*);
};

#endif
