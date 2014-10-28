/*
 * Author: Akash Melethil
 * Last Updated: Oct/24/2014
 */

#ifndef JSONSTRING_HPP
#define JSONSTRING_HPP

#include <string>
#include <stddef.h>

#include "json.hpp"

class JsonString : public Json {
    public:
        JsonString(const char*);
        JsonString(const std::string&);
        JsonString(const JsonString&);
        const JsonString& operator=(const JsonString&);
        virtual ~JsonString();

        std::string get_string();
        virtual std::string stringify();

    private:
        char* str_;
        char* json_str_;
        size_t len_;
        size_t byte_size_;

        void copy(const JsonString& src);
        void destroy();
        void init(const char*, size_t);
};

#endif
