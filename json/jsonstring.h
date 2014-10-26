/*
 * Author: Akash Melethil
 * Last Updated: Oct/24/2014
 */

#ifndef JSONSTRING_H
#define JSONSTRING_H

#include <string>
#include <stddef.h>

#include "json.h"

class JsonString : public Json {
    public:
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

        void copy(const JsonString& src);
        void destroy();
};

#endif
