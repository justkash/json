/*
 * Author: Akash Melethil
 * Last Updated: Oct/25/2014
 */

#ifndef JSONNULL_HPP
#define JSONNULL_HPP

#include "json.hpp"

#include <string>

class JsonNull : public Json {
    public:
        JsonNull();
        JsonNull(const char*);
        JsonNull(const std::string&);

        virtual std::string stringify();

    private:

        void init(const char*);
};

#endif
