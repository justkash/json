/* Author: Akash Melethil
 * Last Updated: Oct/26/2014
 */

#include "jsonarray.hpp"

#include <cstring>
#include <cstdlib>
#include <typeinfo>

void JsonArray::init(const char* c_str) {
    const char* first_bracket = Json::find_next_char(c_str, '[');
    if (*first_bracket == '\0')
        throw("[Error] Invalid json array string; missing starting '['");
    // Find str length and number of values
    size_t num_values = 0; 
    const char* first_char = Json::find_next_non_space_char(first_bracket + 1);
    const char* ptr = first_char;
    size_t str_len = ptr - first_bracket + 1;
    ++num_values;
    while (*ptr != '\0') {
        if (*ptr == '{' || *ptr == '[') {
            const char* new_ptr = Json::find_bracket_end(ptr);
            str_len += new_ptr - ptr;
            ptr = new_ptr;
        }
        else if (*ptr == ',') {
            ++num_values;
        }
        else if (*ptr == ']') {
            break;
        }
        ++str_len;
        ++ptr;
    }
    if (*ptr == '\0')
        throw("[Error] Invalid json array string; missing closing ']'");
    str_ = (char*)malloc((str_len + 3)*sizeof(char));
    str_len_ = str_len + 2;
    if (str_ == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonArray");
    strncpy(str_, first_bracket, str_len + 2);
    *(str_ + str_len + 2) = '\0';
    str_value_ptrs_ = (ValuePointer*)malloc(num_values*sizeof(ValuePointer));
    if (str_value_ptrs_ == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonArray");
    str_num_values_ = num_values;
    // Finding values
    ptr = first_char;
    ValuePointer* val_ptr = str_value_ptrs_;
    const char* val_end = NULL;
    if (*ptr == '[' || *ptr == '{') {
        val_end = Json::find_bracket_end(first_char) + 1;
    }
    else {
        val_end = Json::find_next_either_chars(first_char, ',', ']');
    }
    val_ptr->start = ptr - first_bracket;
    val_ptr->len = val_end - ptr;
    ptr = val_end;
    ++val_ptr;
    while (*ptr != '\0') {
        if (*ptr == ',') {
            const char* next_char = Json::find_next_non_space_char(ptr + 1);
            if (*next_char == '[' || *next_char == '{') {
                val_end = Json::find_bracket_end(next_char);
                val_ptr->start = ptr - first_bracket + 1;
                val_ptr->len = val_end - ptr;
                ptr = val_end;
            }
            else {
                val_end = Json::find_next_either_chars(ptr + 1, ',', ']');
                val_ptr->start = ptr - first_bracket + 1;
                val_ptr->len = val_end - ptr - 1;
                ptr = val_end - 1;
            }
            ++val_ptr;
        }
        else if (*ptr == ']') {
            break;
        }
        ++ptr;
    }
    if (str_num_values_ == 1 && str_value_ptrs_->len == 0) {
        // Empty array
        free(str_);
        str_ = NULL;
        str_len_ = 0;
        free(str_value_ptrs_);
        str_value_ptrs_ = NULL;
        str_num_values_ = 0;
    }
    arr_ = NULL;
    size_ = 0;
}

JsonArray::JsonArray(const std::string& str) {
    init(str.c_str());
}

JsonArray::JsonArray(const char* c_str) {
    init(c_str);
}

JsonArray::JsonArray(const JsonArray& src):arr_(NULL), size_(0), str_(NULL), str_len_(0), str_num_values_(0), str_value_ptrs_(NULL) {
    copy(src);
}

JsonArray::JsonArray():arr_(NULL), size_(0), str_(NULL), str_len_(0), str_num_values_(0), str_value_ptrs_(NULL) {}

const JsonArray& JsonArray::operator=(const JsonArray& rhs) {
    copy(rhs);
    return *this;
}

JsonArray::~JsonArray() {
    destroy();
}

void JsonArray::copy(const JsonArray& src) {
    destroy();
    bool should_copy_str = false;
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
            else if (typeid(*new_ptr) == typeid(JsonObject))
                *ptr = new JsonObject(*((JsonObject*)new_ptr));
            else if (typeid(*new_ptr) == typeid(JsonArray))
                *ptr = new JsonArray(*((JsonArray*)new_ptr));
            else if (typeid(*new_ptr) == typeid(JsonNull))
                *ptr = new JsonNull(*((JsonNull*)new_ptr));
            else {
                *ptr = NULL;
                should_copy_str = true;
            }
            ++ptr;
            ++new_ptr;
        }
    }
    else {
        arr_ = NULL;
        size_ = 0;
        should_copy_str = true;
    }
    if (src.str_ != NULL && should_copy_str) {
        str_len_ = src.str_len_;
        str_num_values_ = src.str_num_values_;
        str_ = (char*)malloc((str_len_ + 1)*sizeof(char));
        if (str_ == NULL)
            throw("[Error] Unsuccessful memory allocation for JsonArray");
        strcpy(str_, src.str_);
        str_value_ptrs_ = (ValuePointer*)malloc(str_num_values_*sizeof(ValuePointer));
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
        str_value_ptrs_ = NULL;
    }
}

void JsonArray::destroy() {
    free(str_);
    str_ = NULL;
    free(str_value_ptrs_);
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

Json* JsonArray::get(int index) {
    if (index < 0)
        throw("[Error] Index out of JsonArray bounds");
    if (arr_ != NULL && *(arr_ + index) != NULL) {
        if (index < size_ || index == 0) {
            return *(arr_ + index);
        }
        else
            throw("[Error] Index out of JsonArray bounds");
    }
    else if (str_ != NULL){
        if (index < str_num_values_) {
            ValuePointer *val_ptr = str_value_ptrs_ + index;
            if (val_ptr->len == 0)
                throw("[Error] Invalid json string found in JsonArray");
            char temp[val_ptr->len + 1];
            strncpy(temp, str_ + val_ptr->start, val_ptr->len);
            temp[val_ptr->len] = '\0';
            Json *json_ptr = NULL;
            switch (Json::find_type(temp)) {
                case JSONOBJECT:
                    json_ptr = new JsonObject(temp);
                    break;
                case JSONSTRING:
                    json_ptr = new JsonString(temp);
                    break;
                case JSONNUMBER:
                    json_ptr = new JsonNumber(temp);
                    break;
                case JSONBOOLEAN:
                    json_ptr = new JsonBoolean(temp);
                    break;
                case JSONARRAY:
                    json_ptr = new JsonArray(temp);
                    break;
                default:
                    json_ptr = new JsonNull();
            }
            if (arr_ == NULL) {
                arr_  = (Json**)calloc(str_num_values_, sizeof(Json*));
                if (arr_ == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonArray");
                size_ = str_num_values_;
            }
            *(arr_ + index) = json_ptr;
            return json_ptr;
        }
        else 
            throw("[Error] Index out of JsonArray bounds");
    }
    else
        throw("[Error] Index out of JsonArray bounds");
}

JsonString& JsonArray::get_string(int index) {
    return *((JsonString*)get(index));
}

JsonNumber& JsonArray::get_number(int index) {
    return *((JsonNumber*)get(index));
}

JsonBoolean& JsonArray::get_boolean(int index) {
    return *((JsonBoolean*)get(index));
}

JsonNull& JsonArray::get_null(int index) {
    return *((JsonNull*)get(index));
}

JsonArray& JsonArray::get_array(int index) {
    return *((JsonArray*)get(index));
}

JsonObject& JsonArray::get_object(int index) {
    return *((JsonObject*)get(index));
}

void JsonArray::check_index_bounds(int index, bool is_insert) {
    if (index < 0)
        throw("[Error] Index out of JsonArray bounds 1");
    if (arr_ != NULL) {
        if (index > size_)
            throw("[Error] Index out of JsonArray bounds 2");
        else if (!is_insert && index == size_)
            throw("[Error] Index out of JsonArray bounds 3");
    }
    else {
        if (str_ != NULL) {
            if (index > str_num_values_)
                throw("[Error] Index out of JsonArray bounds 4");
            else if (!is_insert && index == str_num_values_)
                throw("[Error] Index out of JsonArray bounds 5");
        }
        else {
            if (!is_insert)
                throw("[Error] Index out of JsonArray bounds 6");
            else if (index != 0)
                throw("[Error] Index out of JsonArray bounds 6");
        }
    }
}

void JsonArray::set(int index, Json* json) {
    if (arr_ == NULL) {
         arr_ = (Json**)calloc(str_num_values_, sizeof(Json*));
         if (arr_ == NULL)
            throw("[Error] Unsuccessful memory allocation for JsonArray");
         size_ = str_num_values_;
    }
    delete *(arr_ + index);
    *(arr_ + index) = json;
}

void JsonArray::set(int index, const JsonString& json) {
    check_index_bounds(index, false);
    Json* new_json = new JsonString(json);
    if (new_json == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonString");
    set(index, new_json);
}

void JsonArray::set(int index, const JsonNumber& json) {
    check_index_bounds(index, false);
    Json* new_json = new JsonNumber(json);
    if (new_json == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonNumber");
    set(index, new_json);
}

void JsonArray::set(int index, const JsonBoolean& json) {
    check_index_bounds(index, false);
    Json* new_json = new JsonBoolean(json);
    if (new_json == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonBoolean");
    set(index, new_json);
}

void JsonArray::set(int index, const JsonNull& json) {
    check_index_bounds(index, false);
    Json* new_json = new JsonNull(json);
    if (new_json == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonNull");
    set(index, new_json);
}

void JsonArray::set(int index, const JsonArray& json) {
    check_index_bounds(index, false);
    Json* new_json = new JsonArray(json);
    if (new_json == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonArray");
    set(index, new_json);
}

void JsonArray::set(int index, const JsonObject& json) {
    check_index_bounds(index, false);
    Json* new_json = new JsonObject(json);
    if (new_json == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonObject");
    set(index, new_json);
}

void JsonArray::push_back(Json* json) {
    if (arr_ == NULL) {
        if (str_ == NULL) {
            arr_ = (Json**)malloc(sizeof(Json*));
            if (arr_ == NULL)
                throw("[Error] Unsuccessful memory allocation for JsonArray");
            *arr_ = json;
            size_ = 1;
        }
        else {
            arr_ = (Json**)calloc(str_num_values_ + 1, sizeof(Json*));
            if (arr_ == NULL)
                throw("[Error] Unsuccessful memory allocation for JsonArray");
            *(arr_ + str_num_values_) = json;
            size_ = str_num_values_ + 1;
        }
    }
    else {
        Json** ptr;
        Json** end;
        if (str_ == NULL) {
            ptr = arr_;
            end = ptr + size_;
        }
        else {
            ptr = arr_ + str_num_values_;
            end = ptr + size_;
        }
        while (ptr != end) {
            if (*ptr == NULL)
                break;
            ++ptr;
        }
        if (ptr == end) {
            Json** new_arr = (Json**)realloc(arr_, (size_ + 1)*sizeof(Json*));
            if (new_arr == NULL)
                throw("[Error] Unsuccessful memory reallocation for JsonArray");
            arr_ = new_arr;
            *(arr_ + size_) = json;
            ++size_;
        }
        else {
            *ptr = json; 
        }
    }
}

void JsonArray::push_back(const JsonString& json) {
    Json* new_json = new JsonString(json);
    push_back(new_json);
}

void JsonArray::push_back(const JsonNumber& json) {
    Json* new_json = new JsonNumber(json);
    push_back(new_json);
}

void JsonArray::push_back(const JsonBoolean& json) {
    Json* new_json = new JsonBoolean(json);
    push_back(new_json);
}

void JsonArray::push_back(const JsonNull& json) {
    Json* new_json = new JsonNull(json);
    push_back(new_json);
}

void JsonArray::push_back(const JsonArray& json) {
    Json* new_json = new JsonArray(json);
    push_back(new_json);
}

void JsonArray::push_back(const JsonObject& json) {
    Json* new_json = new JsonObject(json);
    push_back(new_json);
}

void JsonArray::insert(int index, Json* json) {
    if (arr_ == NULL) {
        if (str_ == NULL) {
            if (index == 0) {
                arr_ = (Json**)malloc(sizeof(Json*));
                if (arr_ == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonArray");
                *arr_ = json;
                size_ = 1;
            }
            else
                throw("[Error] Invalid index for JsonArray");
        }
        else {
            if (index == 0) {
                ValuePointer* new_str_value_ptrs = (ValuePointer*)malloc((str_num_values_ + 1)*sizeof(ValuePointer));
                if (new_str_value_ptrs == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonArray");
                memcpy(new_str_value_ptrs + 1, str_value_ptrs_, str_num_values_*sizeof(ValuePointer));
                free(str_value_ptrs_);
                str_value_ptrs_ = new_str_value_ptrs;
                ++str_num_values_;

                arr_ = (Json**)calloc(str_num_values_, sizeof(Json*));
                if (arr_ == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonArray");
                *arr_ = json;
                size_ = str_num_values_;
            }
            else if (index == str_num_values_) {
                push_back(json);
            }
            else {
                ValuePointer* new_str_value_ptrs = (ValuePointer*)malloc((str_num_values_ + 1)*sizeof(ValuePointer));
                if (new_str_value_ptrs == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonArray");
                memcpy(new_str_value_ptrs, str_value_ptrs_, sizeof(ValuePointer)*index);
                if (index != str_num_values_ - 1)
                    memcpy(new_str_value_ptrs + index + 1, str_value_ptrs_ + index, (str_num_values_ - index)*sizeof(ValuePointer));
                free(str_value_ptrs_);
                str_value_ptrs_ = new_str_value_ptrs;
                ++str_num_values_;

                arr_ = (Json**)calloc(str_num_values_, sizeof(Json*));
                if (arr_ == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonArray");
                *(arr_ + index) = json;
                size_ = str_num_values_;
            }
        }
    }
    else {
        if (str_ == NULL) {
            if (index == 0) {
                Json** new_arr = (Json**)malloc((size_ + 1)*sizeof(Json*));
                if (new_arr == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonArray");
                *new_arr = json;
                memcpy(new_arr + 1, arr_, size_*sizeof(Json*));
                free(arr_);
                arr_ = new_arr;
                ++size_;
            }
            else if (index == size_) {
                push_back(json); 
            }
            else {
                Json** new_arr = (Json**)malloc((size_ + 1)*sizeof(Json*));
                if (new_arr == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonArray");
                memcpy(new_arr, arr_, index*sizeof(Json*));
                memcpy(new_arr + index + 1, arr_ + index, (size_ - index)*sizeof(Json*));
                *(new_arr + index) = json;
                free(arr_);
                arr_ = new_arr;
                ++size_;
            }
        }
        else {
            if (index >= str_num_values_) {
                if (index == size_) {
                    push_back(json);
                }
                else {
                    Json** new_arr = (Json**)malloc((size_ + 1)*sizeof(Json*));
                    if (new_arr == NULL)
                        throw("[Error] Unsuccessful memory allocation for JsonArray");
                    memcpy(new_arr, arr_, index*sizeof(Json*));
                    memcpy(new_arr + index + 1, arr_ + index, (size_ - index)*sizeof(Json*));
                    *(new_arr + index) = json;
                    free(arr_);
                    arr_ = new_arr;
                    ++size_;
                }
            }
            else {
                if (index == 0) {
                    ValuePointer* new_str_value_ptrs = (ValuePointer*)malloc((str_num_values_ + 1)*sizeof(ValuePointer));
                    if (new_str_value_ptrs == NULL)
                        throw("[Error] Unsuccessful memory allocation for JsonArray");
                    memcpy(new_str_value_ptrs + 1, str_value_ptrs_, str_num_values_*sizeof(ValuePointer));
                    free(str_value_ptrs_);
                    str_value_ptrs_ = new_str_value_ptrs;
                    ++str_num_values_;

                    Json** new_arr = (Json**)malloc((size_ + 1)*sizeof(Json*));
                    if (new_arr == NULL)
                        throw("[Error] Unsuccessful memory allocation for JsonArray");
                    *new_arr = json;
                    memcpy(new_arr + 1, arr_, size_*sizeof(Json*));
                    free(arr_);
                    arr_ = new_arr;
                    ++size_;
                }
                else {
                    ValuePointer* new_str_value_ptrs = (ValuePointer*)malloc((str_num_values_ + 1)*sizeof(ValuePointer));
                    if (new_str_value_ptrs == NULL)
                        throw("[Error] Unsuccessful memory allocation for JsonArray");
                    memcpy(new_str_value_ptrs, str_value_ptrs_, sizeof(ValuePointer)*index);
                    if (index != str_num_values_ - 1)
                        memcpy(new_str_value_ptrs + index + 1, str_value_ptrs_ + index, (str_num_values_ - index)*sizeof(ValuePointer));
                    free(str_value_ptrs_);
                    str_value_ptrs_ = new_str_value_ptrs;
                    ++str_num_values_;

                    Json** new_arr = (Json**)malloc((size_ + 1)*sizeof(Json*));
                    if (new_arr == NULL)
                        throw("[Error] Unsuccessful memory allocation for JsonArray");
                    memcpy(new_arr, arr_, index*sizeof(Json*));
                    memcpy(new_arr + index + 1, arr_ + index, (size_ - index)*sizeof(Json*));
                    *(new_arr + index) = json;
                    free(arr_);
                    arr_ = new_arr;
                    ++size_;
                }
            } 
        }
    }
}

void JsonArray::insert(int index, const JsonString& json) {
    check_index_bounds(index, true);
    Json* new_json = new JsonString(json);
    if (new_json == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonString");
    insert(index, new_json);
}

void JsonArray::insert(int index, const JsonNumber& json) {
    check_index_bounds(index, true);
    Json* new_json = new JsonNumber(json);
    if (new_json == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonString");
    insert(index, new_json);
}

void JsonArray::insert(int index, const JsonBoolean& json) {
    check_index_bounds(index, true);
    Json* new_json = new JsonBoolean(json);
    if (new_json == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonString");
    insert(index, new_json);
}

void JsonArray::insert(int index, const JsonNull& json) {
    check_index_bounds(index, true);
    Json* new_json = new JsonNull(json);
    if (new_json == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonString");
    insert(index, new_json);
}

void JsonArray::insert(int index, const JsonArray& json) {
    check_index_bounds(index, true);
    Json* new_json = new JsonArray(json);
    if (new_json == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonString");
    insert(index, new_json);
}

void JsonArray::insert(int index, const JsonObject& json) {
    check_index_bounds(index, true);
    Json* new_json = new JsonObject(json);
    if (new_json == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonString");
    insert(index, new_json);
}

size_t JsonArray::size() {
    if (arr_ == NULL) {
        if (str_ == NULL)
            return 0;
        else
            return str_num_values_;
    }
    else
        return size_;
}

bool JsonArray::is_empty() {
    if (size_ == 0 && str_num_values_ == 0)
        return true;
    return false;
}

void JsonArray::resize(int new_size) {
    if (new_size == 0) {
        destroy();
    }
    else if (arr_ == NULL) {
        if (str_ == NULL) {
            Json** new_arr = (Json**)calloc(new_size, sizeof(Json*));
            if (new_arr == NULL)
                throw("[Error] Unsuccessful memory allocation for JsonArray");
            size_ = new_size;
            free(arr_);
            arr_ = new_arr;
        }
        else {
            if (new_size < str_num_values_) {
                str_num_values_ = new_size;
            }
            else {
                Json** new_arr = (Json**)calloc(new_size, sizeof(Json*));
                if (new_arr == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonArray");
                size_ = new_size;
                free(arr_);
                arr_ = new_arr;
            }
        }
    }
    else {
        if (str_ == NULL) {
            if (new_size < size_) {
                Json** ptr = arr_ + new_size;
                Json** end = arr_ + size_;
                while (ptr != end) {
                    delete *ptr;
                    ++ptr;
                }
                Json** new_arr = (Json**)calloc(new_size, sizeof(Json*));
                if (new_arr == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonArray");
                memcpy(new_arr, arr_, new_size*sizeof(Json*));
                free(arr_);
                arr_ = new_arr;
                size_ = new_size;
            }
            else {
                Json** new_arr = (Json**)calloc(new_size, sizeof(Json*));
                if (new_arr == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonArray");
                memcpy(new_arr, arr_, size_*sizeof(Json*));
                free(arr_);
                arr_ = new_arr;
                size_ = new_size;
            }
        }
        else {
            if (new_size < size_) {
                Json** ptr = arr_ + new_size;
                Json** end = arr_ + size_;
                while (ptr != end) {
                    delete *ptr;
                    ++ptr;
                }
                Json** new_arr = (Json**)calloc(new_size, sizeof(Json*));
                if (new_arr == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonArray");
                memcpy(new_arr, arr_, new_size*sizeof(Json*));
                free(arr_);
                arr_ = new_arr;
                size_ = new_size;
                if (new_size < str_num_values_)
                    str_num_values_ = new_size;
            }
            else {
                Json** new_arr = (Json**)calloc(new_size, sizeof(Json*));
                if (new_arr == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonArray");
                memcpy(new_arr, arr_, size_*sizeof(Json*));
                free(arr_);
                arr_ = new_arr;
                size_ = new_size;
            }
        }
    }
}

void JsonArray::remove_arr(int index) {
    Json** new_arr = (Json**)malloc((size_ - 1)*sizeof(Json*));
    if (new_arr == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonArray");
    if (index == 0) {
        delete *arr_;
        memcpy(new_arr, arr_ + 1, (size_ - 1)*sizeof(Json*));
    }
    else if (index == size_ - 1) {
        delete *(arr_ + index);
        memcpy(new_arr, arr_, (size_ - 1)*sizeof(Json*));
    }
    else {
        delete *(arr_ + index);
        memcpy(new_arr, arr_, index*sizeof(Json*));
        memcpy(new_arr + index, arr_ + index + 1, (size_ - index)*sizeof(Json*));
    }
    --size_;
    free(arr_);
    arr_ = new_arr;
}

void JsonArray::remove_str(int index) {
    ValuePointer* new_str_value_ptrs = (ValuePointer*)malloc((str_num_values_ - 1)*sizeof(ValuePointer));
    if (new_str_value_ptrs == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonArray");
    if (index == 0) {
        memcpy(new_str_value_ptrs, str_value_ptrs_ + 1, (str_num_values_ - 1)*sizeof(ValuePointer));
    }
    else if (index == str_num_values_ - 1) {
        memcpy(new_str_value_ptrs, str_value_ptrs_, (str_num_values_ - 1)*sizeof(ValuePointer));
    }
    else {
        memcpy(new_str_value_ptrs, str_value_ptrs_, index*sizeof(ValuePointer));
        memcpy(new_str_value_ptrs + index, str_value_ptrs_ + index + 1, (str_num_values_ - index)*sizeof(ValuePointer));
    }
    --str_num_values_;
    free(str_value_ptrs_);
    str_value_ptrs_ = new_str_value_ptrs;
}

void JsonArray::remove(int index) {
    check_index_bounds(index, false);
    if (arr_ == NULL) {
        // str_ not null case only
        remove_str(index);
    }
    else {
        if (str_ == NULL) {
            remove_arr(index);
        }
        else {
            if (index < str_num_values_) {
                remove_str(index);
            }
            remove_arr(index);
        }
    }
}

std::string JsonArray::stringify() {
    if (arr_ == NULL) {
        if (str_ == NULL) {
            return "[]";    
        }
        else {
            return std::string(str_);
        }
    }
    else {
        if (str_ == NULL) {
            std::string str = "[";
            Json** ptr = arr_;
            Json** end = arr_ + size_;
            Json** last = arr_ + size_ - 1;
            while (ptr != end) {
                if (*ptr != NULL)
                    str += (*ptr)->stringify();
                if (ptr != last)
                    str += ",";
                ++ptr;
            }
            str += "]";
            return str;
        }
        else {
            std::string str = "[";
            Json** ptr = arr_;
            Json** end = arr_ + size_;
            Json** last = arr_ + size_ - 1;
            ValuePointer* val_ptr = str_value_ptrs_;
            ValuePointer* val_end = val_ptr + str_num_values_;
            while (val_ptr != val_end) {
                if (*ptr != NULL)
                    str += (*ptr)->stringify();
                else {
                    if (val_ptr->len > 0) {
                        char temp[val_ptr->len + 1];
                        strncpy(temp, str_ + val_ptr->start, val_ptr->len);
                        temp[val_ptr->len] = '\0';
                        str += std::string(temp);
                    }
                }
                if (ptr != last)
                    str += ",";
                ++ptr;
                ++val_ptr;
            }
            while (ptr != end) {
                if (*ptr != NULL)
                    str += (*ptr)->stringify();
                if (ptr != last)
                    str += ",";
                ++ptr;
            }
            str += "]";
            return str;
        }
    }
}
