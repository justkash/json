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
 *  - This is an immutable clas.
 *  - This class is smart enough to recognize if the string passed into its
 *    constructor is a json string or a normal string. It does this by looking
 *    for double quotes, if none are found, then it assumes that it is a
 *    regular string and that the user is using the class to create a json
 *    string rather than to parse it.
 */

#ifndef JSONSTRING_HPP
#define JSONSTRING_HPP

#include <string>
#include <cstddef>

#include <json/json.hpp>

namespace json {

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

}

#endif
