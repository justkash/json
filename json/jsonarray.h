/*
 * Author: Akash Melethil
 * Last Updated: Oct/26/2014
 */

#ifndef JSONARRAY_H
#define JSONARRAY_H

#include "json.h"

#include <string>

#include "jsonstring.h"
#include "jsonnumber.h"
#include "jsonboolean.h"
#include "jsonnull.h"
//#include "jsonobject.h"

class JsonArray : public Json {
    public:
        //JsonArray();
        JsonArray(const std::string&);
        JsonArray(const JsonArray&);
        const JsonArray& operator=(const JsonArray&);
        virtual ~JsonArray();
        /*
        JsonString& operator[](int);
        JsonNumber& operator[](int);
        JsonBoolean& operator[](int);
        JsonNull& operator[](int);
        JsonArray& operator[](int);
        //JsonObject& operator[](int);
        void push_back(const JsonString&);
        void push_back(const JsonNumber&);
        void push_back(const JsonBoolean&);
        void push_back(const JsonNull&);
        void push_back(const JsonArray&);
        //void push_back(const JsonObject&);
        void insert(int, const JsonString&);
        void insert(int, const JsonNumber&);
        void insert(int, const JsonBoolean&);
        void insert(int, const JsonNull&);
        void insert(int, const JsonArray&);
        //void insert(int, const JsonObject&);
        void remove(int);
        size_t size();
        void resize(int);*/
        virtual std::string stringify();

    private:
        struct ValuePointer {
            int start;
            size_t len;
        };
        

        Json** arr_;
        size_t size_;
        char* str_;
        size_t str_len_;
        size_t str_num_values_;
        ValuePointer* str_value_ptrs_;
        size_t byte_size_;

        void copy(const JsonArray&);
        void destroy();
};

#endif
