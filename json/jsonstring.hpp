/*
 * File: jsonstring.hpp
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
 *  - This is an immutable class
 */

#ifndef JSONSTRING_HPP
#define JSONSTRING_HPP

#include <string>
#include <cstddef>

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

        void copy(const JsonString& src);
        void destroy();
        void init(const char*, size_t);
};

#endif
