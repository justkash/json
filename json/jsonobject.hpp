/*
 * File: jsonobject.hpp
 *
 * Created By: Akash Melethil, Bryce Besler
 * Created: 2014.10.25
 *
 * Description:
 *  This class represents a json object type and is able to contain objects of Json
 *  type
 *
 * History:
 *  2014.10.25    Akash Melethil    Created
 *
 * Notes:
 *  - This is a mutable class
 */

#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include "json.hpp"

#include <string>

#include "jsonstring.hpp"
#include "jsonnumber.hpp"
#include "jsonboolean.hpp"
#include "jsonnull.hpp"
#include "jsonarray.hpp"

class JsonArray;
class JsonObject : public Json {
    public:
        JsonObject();
        JsonObject(const char*);
        JsonObject(const std::string&);
        JsonObject(const JsonObject&);
        const JsonObject& operator=(const JsonObject&);
        virtual ~JsonObject();

        JsonString& get_string(const std::string&);
        JsonNumber& get_number(const std::string&);
        JsonBoolean& get_boolean(const std::string&);
        JsonNull& get_null(const std::string&);
        JsonArray& get_array(const std::string&);
        JsonObject& get_object(const std::string&);
        void set(const std::string&, const JsonString&);
        void set(const std::string&, const JsonNumber&);
        void set(const std::string&, const JsonBoolean&);
        void set(const std::string&, const JsonNull&);
        void set(const std::string&, const JsonArray&);
        void set(const std::string&, const JsonObject&);
        bool has_key(const std::string&);
        void remove(const std::string&);
        bool is_empty();
        size_t size();
        virtual std::string stringify();

    private:
        struct KeyValuePointer {
            int key_start;
            size_t key_len;
            int val_start;
            size_t val_len;
        };

        Json** val_arr_;
        char** key_arr_;
        size_t size_;
        char* str_;
        size_t str_len_;
        size_t str_num_values_;
        KeyValuePointer* str_ptrs_;

        void copy(const JsonObject&);
        void destroy();
        void init(const char*);
        int get_key_index(const char*);
        Json* get(const char*);
        void set(const std::string&, Json*);
        void remove_str(int);
        void remove_arr(int);
};

#endif
