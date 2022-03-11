/*
 * File: jsonarray.hpp
 *
 * Created By: Akash Melethil, Bryce Besler
 * Created: 2014.10.26
 *
 * Description:
 *  This class represents a json array and is able to contain any Json type objects
 *
 * History:
 *  2014.10.26    Akash Melethil    Created
 *
 * Notes:
 *  - This is a mutable class
 */

#ifndef JSONARRAY_HPP
#define JSONARRAY_HPP

#include <string>

#include <json/json.hpp>
#include <json/jsonstring.hpp>
#include <json/jsonnumber.hpp>
#include <json/jsonboolean.hpp>
#include <json/jsonnull.hpp>
#include <json/jsonobject.hpp>

namespace json {

    class JsonObject;
    class JsonArray : public Json {
        public:
            JsonArray();
            JsonArray(const char*);
            JsonArray(const std::string&);
            JsonArray(const JsonArray&);
            const JsonArray& operator=(const JsonArray&);
            virtual ~JsonArray();

            JsonString& get_string(int);
            JsonNumber& get_number(int);
            JsonBoolean& get_boolean(int);
            JsonNull& get_null(int);
            JsonArray& get_array(int);
            JsonObject& get_object(int);
            void set(int, const JsonString&);
            void set(int, const JsonNumber&);
            void set(int, const JsonBoolean&);
            void set(int, const JsonNull&);
            void set(int, const JsonArray&);
            void set(int, const JsonObject&);
            void push_back(const JsonString&);
            void push_back(const JsonNumber&);
            void push_back(const JsonBoolean&);
            void push_back(const JsonNull&);
            void push_back(const JsonArray&);
            void push_back(const JsonObject&);
            void insert(int, const JsonString&);
            void insert(int, const JsonNumber&);
            void insert(int, const JsonBoolean&);
            void insert(int, const JsonNull&);
            void insert(int, const JsonArray&);
            void insert(int, const JsonObject&);
            void remove(int);
            void resize(int);
            size_t size();
            bool is_empty();
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

            void copy(const JsonArray&);
            void destroy();
            void init(const char*);
            void check_index_bounds(int, bool);
            void set(int, Json*);
            void push_back(Json*);
            void insert(int, Json*);
            void remove_arr(int);
            void remove_str(int);
            Json* get(int);
    };

}
#endif
