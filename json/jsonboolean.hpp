/*
 * Author: Akash Melethil
 * Last Updated: Oct/25/2014
 */

#ifndef JSONBOOLEAN_H
#define JSONBOOLEAN_H

#include <string>
#include <stddef.h>

#include "json.h"

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
};

#endif