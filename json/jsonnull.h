/*
 * Author: Akash Melethil
 * Last Updated: Oct/25/2014
 */

#ifndef JSONNULL_H
#define JSONNULL_H

#include "json.h"

#include <string>

class JsonNull : Json {
    public:
        JsonNull(const std::string&);
        JsonNull();

        virtual std::string stringify();

    private:
        size_t byte_size_;
};

#endif
