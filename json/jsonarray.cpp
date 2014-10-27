/* Author: Akash Melethil
 * Last Updated: Oct/26/2014
 */

#include "jsonarray.hpp"

#include "string.h"
#include "stdlib.h"
#include <typeinfo>

JsonArray::JsonArray(const std::string& str) {
    const char* c_str = str.c_str();
    const char* first_bracket = Json::find_next_char(c_str, '[');
    if (*first_bracket == '\0')
        throw("[Error] Invalid json array string; missing starting '['");
    // Find str length and number of values
    size_t str_len = 0;
    size_t num_values = 0; 
    int level_ctr = 0;
    const char* ptr = first_bracket + 1;
    while (*ptr != '\0') {
        if (*ptr == '[')
            ++level_ctr;
        else if (*ptr == ']') {
            if (level_ctr == 0) {
                ++num_values;
                break;
            }
            --level_ctr;
        }
        else if (*ptr == ',' && level_ctr == 0) {
            ++num_values;
        }
        ++str_len;
        ++ptr;
    }
    if (*ptr == '\0')
        throw("[Error] Invalid json array string; missing closing ']'");
    str_ = new char[str_len + 3];
    str_len_ = str_len + 2;
    if (str_ == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonArray");
    strncpy(str_, first_bracket, str_len + 2);
    *(str_ + str_len + 2) = '\0';
    str_value_ptrs_ = new ValuePointer[num_values];
    if (str_value_ptrs_ == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonArray");
    str_num_values_ = num_values;
    // Finding values
    ptr = first_bracket + 1;
    const char* ptr_two = ptr;
    level_ctr = 0;
    ValuePointer* val_ptr = str_value_ptrs_;
    while(*ptr_two != '\0') {
        if(level_ctr == 0 && (*ptr_two == ',' || *ptr_two == ']')) {
            val_ptr->start = ptr - first_bracket;
            val_ptr->len = ptr_two - ptr;
            ++val_ptr;
            ptr = ptr_two + 1;
        }
        if(*ptr_two == '[') 
            ++level_ctr;
        else if(*ptr_two == ']') {
            if (level_ctr == 0)
                break;
            --level_ctr;
        }
        ++ptr_two;
    }
    arr_ = NULL;
    size_ = 0;
    byte_size_ = 0;
}

JsonArray::JsonArray(const JsonArray& src) {
    copy(src);
}

const JsonArray& JsonArray::operator=(const JsonArray& rhs) {
    copy(rhs);
    return *this;
}

JsonArray::~JsonArray() {
    destroy();
}

void JsonArray::copy(const JsonArray& src) {
    destroy();
    bool src_has_null = false;
    if (src.arr_ != NULL) {
        size_ = src.size_;
        arr_ = (Json**)malloc(size_*sizeof(Json*));
        if (arr_ == NULL)
            throw("[Error] Unsuccessful memory allocation for JsonArray");
        Json** ptr = arr_;
        Json** new_ptr = src.arr_;
        Json** end = arr_ + size_;
        while (ptr != end) {
            if (typeid(*new_ptr) == typeid(JsonString))
                *ptr = new JsonString(*((JsonString*)new_ptr));
            else if (typeid(*new_ptr) == typeid(JsonNumber))
                *ptr = new JsonNumber(*((JsonNumber*)new_ptr));
            else if (typeid(*new_ptr) == typeid(JsonBoolean))
                *ptr = new JsonBoolean(*((JsonBoolean*)new_ptr));
            //else if (typeid(*new_ptr) == typeid(JsonObject))
            //    *ptr = new JsonObject(*((JsonObject*)new_ptr));
            else if (typeid(*new_ptr) == typeid(JsonArray))
                *ptr = new JsonArray(*((JsonArray*)new_ptr));
            else if (typeid(*new_ptr) == typeid(JsonNull))
                *ptr = new JsonNull(*((JsonNull*)new_ptr));
            else {
                *ptr = NULL;
                src_has_null = true;
            }
            ++ptr;
            ++new_ptr;
        }
    }
    else {
        arr_ = NULL;
        size_ = 0;
    }
    if (src.str_ != NULL && src_has_null) {
        str_len_ = src.str_len_;
        str_num_values_ = src.str_num_values_;
        str_ = new char[str_len_ + 1];
        strcpy(str_, src.str_);
        str_value_ptrs_ = new ValuePointer[str_num_values_];
        ValuePointer *ptr = str_value_ptrs_;
        ValuePointer *new_ptr = src.str_value_ptrs_;
        ValuePointer *end = ptr + str_num_values_;
        while (ptr != end) {
            ptr->start = new_ptr->start;
            ptr->len = new_ptr->len;
            ++ptr;
            ++new_ptr;
        }
    }
    else {
        str_ = NULL;
        str_len_ = 0;
        str_num_values_ = 0;
    }
}

void JsonArray::destroy() {
    delete [] str_;
    str_ = NULL;
    delete [] str_value_ptrs_;
    str_value_ptrs_ = NULL;
    // Deleting arr_
    Json** ptr = arr_;
    Json** end = ptr + size_;
    while (ptr != end) {
        delete *ptr;
        *ptr = NULL;
        ++ptr;
    }
    free(arr_);
    arr_ = NULL;
}

JsonString& JsonArray::operator[](int index) {
    if (index < 0)
        throw("[Error] Index out of bounds in JsonArray");
    if (arr_ != NULL && *(arr_ + index) != NULL) {
        if (index < size_) {
            Json* ptr = *(arr_ + index);
            if (typeid(*ptr) != typeid(JsonString))
                throw("[Error] Object at index is not of type JsonString");
            return *((JsonString*)ptr);
        }
        else
            throw("[Error] Index out of bounds in JsonArray");
    }
    else if (str_ != NULL){
        if (index < str_num_values_) {
            ValuePointer *val_ptr = str_value_ptrs_ + index;
            if (val_ptr->len == 0)
                throw("[Error] Invalid JsonString");
            char temp[val_ptr->len + 1];
            strncpy(temp, str_ + val_ptr->start, val_ptr->len);
            temp[val_ptr->len] = '\0';
            JsonString *json_ptr = new JsonString(std::string(temp));
            if (arr_ == NULL) {
                arr_  = (Json**)calloc(str_num_values_, sizeof(Json*));
                if (arr_ == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonArray");
                size_ = str_num_values_;
            }
            *(arr_ + index) = json_ptr;
            return *((JsonString*)*(arr_ + index));
        }
        else 
            throw("[Error] Index out of bounds in JsonArray");
    }
    else
        throw("[Error] Index out of bounds in JsonArray");
}

std::string JsonArray::stringify() {
    return "";
}
