/*
 * File: jsonboolean.hpp
 *
 * Created By: Akash Melethil, Bryce Besler
 * Created: 2014.10.25
 *
 * Description:
 *  This class represents a json boolean.
 *
 * History:
 *  2014.10.25    Akash Melethil    Created
 *
 * Notes:
 *  - This is an immutable class
 */

#ifndef JSONBOOLEAN_HPP
#define JSONBOOLEAN_HPP

#include <string>
#include <cstddef>

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

        void init(const char*);
};

#endif
