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
        JsonNull(const std::string&);
        JsonNull();

        virtual std::string stringify();

    private:
        size_t byte_size_;
};

#endif
