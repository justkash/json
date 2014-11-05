/*
 * File: jsonnull.hpp
 *
 * Created By: Akash Melethil, Bryce Besler
 * Created: 2014.10.25
 *
 * Description:
 *  This class represents a json null type.
 *
 * History:
 *  2014.10.25    Akash Melethil    Created
 *
 * Notes:
 *  - This is an immutable class
 *  - This class was created largely for completion and has few use cases
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
