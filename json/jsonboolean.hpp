/*
 * Author: Akash Melethil
 * Last Updated: Oct/25/2014
 */

#ifndef JSONBOOLEAN_HPP
#define JSONBOOLEAN_HPP

#include <string>
#include <stddef.h>

#include "json.hpp"

class JsonBoolean : public Json {
    public:
        JsonBoolean(const std::string&);
        JsonBoolean(bool);
        JsonBoolean(const char*);

        bool get_bool();
        virtual std::string stringify();

    private:
        bool is_true_;
        size_t byte_size_;

        void init(const char*);
};

#endif
