#include "jsonobject.hpp"

#include <cstring>
#include <cstdlib>
#include <typeinfo>

JsonObject::JsonObject():val_arr_(NULL), key_arr_(NULL), size_(0), str_(NULL), str_len_(0), str_num_values_(0), str_ptrs_(NULL) {}

JsonObject::JsonObject(const char* c_str) {
    init(c_str);
}

JsonObject::JsonObject(const std::string& str) {
    init(str.c_str());
}

JsonObject::JsonObject(const JsonObject& src):val_arr_(NULL), key_arr_(NULL), size_(0), str_(NULL), str_len_(0), str_num_values_(0), str_ptrs_(NULL) {
    copy(src);
}

const JsonObject& JsonObject::operator=(const JsonObject& rhs) {
    copy(rhs);
    return *this;
}

JsonObject::~JsonObject() {
    destroy();
}

void JsonObject::copy(const JsonObject& src) {
    destroy();
    if (src.val_arr_ == NULL) {
        if (src.str_ != NULL) {
            // Copy str_
            str_len_ = src.str_len_;
            str_ = (char*)malloc((str_len_ + 1)*sizeof(char));
            if (str_ == NULL)
                throw("[Error] Unsuccessful memory allocation for JsonObject");
            strcpy(str_, src.str_);

            // Copy str_ptrs_
            str_num_values_ = src.str_num_values_;
            str_ptrs_ = (KeyValuePointer*)malloc(str_num_values_*sizeof(KeyValuePointer));
            if (str_ptrs_ == NULL)
                throw("[Error] Unsuccessful memory allocation for JsonObject");
            memcpy(str_ptrs_, src.str_ptrs_, str_num_values_*sizeof(KeyValuePointer));
            val_arr_ = NULL;
            key_arr_ = NULL;
            size_ = 0;
        }
        else {
            val_arr_ = NULL;
            key_arr_ = NULL;
            size_ = 0;
            str_ = NULL;
            str_len_ = 0;
            str_num_values_ = 0;
            str_ptrs_ = NULL;
        }
    }
    else {
        // Copy val_arr_ and key_arr_
        bool should_copy_str = false;
        size_ = src.size_;
        val_arr_ = (Json**)malloc(size_*sizeof(Json*));
        if (val_arr_ == NULL)
            throw("[Error] Unsuccessful memory allocation for JsonObject");
        key_arr_ = (char**)malloc(size_*sizeof(char*));
        if (key_arr_ == NULL)
            throw("[Error] Unsuccessful memory allocation for JsonObject");
        Json** ptr = val_arr_;
        Json** new_ptr = src.val_arr_;
        Json** end = val_arr_ + size_;
        char** key_ptr = key_arr_;
        char** new_key_ptr = src.key_arr_;
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
                should_copy_str = true;
            }
            
            if (*new_key_ptr == NULL) {
                *key_ptr = NULL;
            }
            else {
                *key_ptr = (char*)malloc((strlen(*new_key_ptr) + 1)*sizeof(char)); 
                if (*key_ptr == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonObject");
                strcpy(*key_ptr, *new_key_ptr);
            }

            ++ptr;
            ++new_ptr;
            ++key_ptr;
            ++new_key_ptr;
        }

        // Copy str_ and str_ptrs_
        if (src.str_ != NULL && should_copy_str) {
            str_len_ = src.str_len_;
            str_num_values_ = src.str_num_values_;
            str_ = (char*)malloc((str_len_ + 1)*sizeof(char));
            strcpy(str_, src.str_);
            str_ptrs_ = (KeyValuePointer*)malloc(str_num_values_*sizeof(KeyValuePointer));
            KeyValuePointer *ptr = str_ptrs_;
            KeyValuePointer *new_ptr = src.str_ptrs_;
            KeyValuePointer *end = ptr + str_num_values_;
            while (ptr != end) {
                ptr->key_start = new_ptr->key_start;
                ptr->key_len = new_ptr->key_len;
                ptr->val_start = new_ptr->val_start;
                ptr->val_len = new_ptr->val_len;
                ++ptr;
                ++new_ptr;
            }
        }
        else {
            str_ = NULL;
            str_len_ = 0;
            str_num_values_ = 0;
            str_ptrs_ = NULL;
        }
    }
}

void JsonObject::destroy() {
    // Delete val_arr_
    Json** val_ptr = val_arr_;
    Json** val_end = val_arr_ + size_;
    while (val_ptr != val_end) {
        delete *val_ptr;
        *val_ptr = NULL;
        ++val_ptr;
    }
    free(val_arr_);
    val_arr_ = NULL;

    // Delete key_arr_
    char** key_ptr = key_arr_;
    char** key_end = key_arr_ + size_;
    while (key_ptr != key_end) {
        free(*key_ptr);
        *key_ptr = NULL;
        ++key_ptr;
    }
    free(key_arr_);
    key_arr_ = NULL;

    // Delete str_
    free(str_);
    str_ = NULL;
    
    // Delete str_ptrs_
    free(str_ptrs_);
    str_ptrs_ = NULL;
}

void JsonObject::init(const char* c_str) {
    const char* first_bracket = Json::find_next_char(c_str, '{');
    if (*first_bracket == '\0')
        throw("[Error] Invalid json object string; missing starting '{'");
    // Find str length and number of values
    size_t str_len = 0;
    size_t num_values = 0; 
    const char* ptr = first_bracket + 1;
    while (*ptr != '\0') {
        if (*ptr == '{' || *ptr == '[') {
            const char* new_ptr = Json::find_bracket_end(ptr);
            str_len += new_ptr - ptr;
            ptr = new_ptr;
        }
        else if (*ptr == ',') {
            ++num_values;
        }
        else if (*ptr == '}') {
            ++num_values;
            break;
        }
        ++str_len;
        ++ptr;
    }
    if (*ptr == '\0')
        throw("[Error] Invalid json object string; missing closing '}'");
    str_ = new char[str_len + 3];
    str_len_ = str_len + 2;
    if (str_ == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonObject");
    strncpy(str_, first_bracket, str_len + 2);
    *(str_ + str_len + 2) = '\0';
    str_ptrs_ =(KeyValuePointer*)calloc(num_values, sizeof(KeyValuePointer));
    if (str_ptrs_ == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonObject");
    str_num_values_ = num_values;
    // Finding values
    ptr = first_bracket + 1;
    KeyValuePointer* keyval_ptr = str_ptrs_;
    while(*ptr != '\0') {
        if (*ptr == '"') {
            const char* key_end = Json::find_next_char(ptr + 1, '"');
            keyval_ptr->key_start = ptr - first_bracket + 1;
            keyval_ptr->key_len = key_end - ptr - 1;
            ptr = key_end;
        }
        else if (*ptr == ':') {
            const char* next_char = Json::find_next_non_space_char(ptr + 1);
            const char* val_end = 0;
            if (*next_char == '[' || *next_char == '{') {
                val_end = Json::find_bracket_end(next_char) + 1;
            }
            else {
                val_end = Json::find_next_either_chars(next_char, ',', '}');
            }
            keyval_ptr->val_start = ptr - first_bracket + 1;
            keyval_ptr->val_len = val_end - ptr - 1;
            ptr = val_end;
            ++keyval_ptr;
        }
        else if (*ptr == '}') {
            break;
        }
        ++ptr;
    }
    if (str_num_values_ == 1 && (str_ptrs_->key_len == 0 || str_ptrs_->val_len == 0)) {
        // Empty object
        free(str_);
        str_ = NULL;
        str_len_ = 0;
        free(str_ptrs_);
        str_ptrs_ = NULL;
        str_num_values_ = 0;
    }
    val_arr_ = NULL;
    key_arr_ = NULL;
    size_ = 0;
}

Json* JsonObject::get(const char* str) {
    int index = get_key_index(str);
    if (index < 0)
        throw("[Error] Key not found in JsonObject");
    if (val_arr_ != NULL && *(val_arr_ + index) != NULL)
        return *(val_arr_ + index);
    else {
        KeyValuePointer* ptr = str_ptrs_ + index;
        char* key_temp = (char*)malloc((ptr->key_len + 1)*sizeof(char));
        if (key_temp == NULL)
            throw("[Error] Unsuccessful memory allocation for JsonObject");
        strncpy(key_temp, str_ + ptr->key_start, ptr->key_len);
        key_temp[ptr->key_len] = '\0';
        if (key_arr_ == NULL) {
            key_arr_  = (char**)calloc(str_num_values_, sizeof(char*));
            if (key_arr_ == NULL)
                throw("[Error] Unsuccessful memory allocation for JsonObject");
            size_ = str_num_values_;
        }
        *(key_arr_ + index) = key_temp;
        char temp[ptr->val_len + 1];
        strncpy(temp, str_ + ptr->val_start, ptr->val_len);
        temp[ptr->val_len] = '\0';
        Json* json_ptr = NULL;
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
        if (val_arr_ == NULL) {
            val_arr_  = (Json**)calloc(str_num_values_, sizeof(Json*));
            if (val_arr_ == NULL)
                throw("[Error] Unsuccessful memory allocation for JsonObject");
            size_ = str_num_values_;
        }
        *(val_arr_ + index) = json_ptr;
        return json_ptr;
    }
}

int JsonObject::get_key_index(const char* key_str) {
    if (key_arr_ == NULL) {
        if (str_ == NULL)
            return -1;
        else {
            // Check str_
            for (int i = 0; i < str_num_values_; ++i) {
                if (Json::check_contains(str_ + str_ptrs_[i].key_start, key_str))
                    return i;
            }
        }
    }
    else {
        if (str_ == NULL) {
            // Check key_arr_
            char** ptr = key_arr_;
            char** end = key_arr_ + size_;
            int i = 0;
            while (ptr != end) {
                if (*ptr != NULL && strcmp(*ptr, key_str) == 0)
                    return i;
                ++ptr;
                ++i;
            }
        }
        else {
            // Check str_ and key_arr_
            for (int i = 0; i < str_num_values_; ++i) {
                if (Json::check_contains(str_ + str_ptrs_[i].key_start, key_str))
                    return i;
            }
            char** ptr = key_arr_ + str_num_values_;
            char** end = key_arr_ + size_;
            int i = 0;
            while (ptr != end) {
                if (*ptr != NULL && strcmp(*ptr, key_str) == 0)
                    return i;
                ++ptr;
                ++i;
            }
        }
    }
    return -1;
}

JsonString& JsonObject::get_string(const std::string& str) {
    return *((JsonString*)get(str.c_str()));
}

JsonNumber& JsonObject::get_number(const std::string& str) {
    return *((JsonNumber*)get(str.c_str()));
}

JsonBoolean& JsonObject::get_boolean(const std::string& str) {
    return *((JsonBoolean*)get(str.c_str()));
}

JsonNull& JsonObject::get_null(const std::string& str) {
    return *((JsonNull*)get(str.c_str()));
}

JsonArray& JsonObject::get_array(const std::string& str) {
    return *((JsonArray*)get(str.c_str()));
}

JsonObject& JsonObject::get_object(const std::string& str) {
    return *((JsonObject*)get(str.c_str()));
}

void JsonObject::set(const std::string& key, Json* json) {
    int index = get_key_index(key.c_str());
    if (index < 0) {
        if (val_arr_ == NULL) {
            if (str_ == NULL) {
                // Add one
                val_arr_ = (Json**)malloc(sizeof(Json*));
                if (val_arr_ == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonObject");
                key_arr_ = (char**)malloc(sizeof(char*));
                if (key_arr_ == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonObject");
                *val_arr_ = json;
                *key_arr_ = (char*)malloc((key.size() + 1)*sizeof(char));
                if (*key_arr_ == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonObject");
                strcpy(*key_arr_, key.c_str());
                size_ = 1;
            }
            else {
                // Create of length 
                val_arr_ = (Json**)calloc((str_num_values_ + 1), sizeof(Json*));
                if (val_arr_ == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonObject");
                key_arr_ = (char**)calloc((str_num_values_ + 1), sizeof(char*));
                if (key_arr_ == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonObject");
                *(val_arr_ + str_num_values_) = json;
                *(key_arr_ + str_num_values_) = (char*)malloc((key.size() + 1)* sizeof(char));
                if (*(key_arr_ + str_num_values_) == NULL)
                    throw("[Error] Unsuccessful memory allocation for JsonObject");
                strcpy(*(key_arr_ + str_num_values_), key.c_str());
                size_ = str_num_values_ + 1;
            }
        }
        else {
            // Add to end
            char** new_key_arr = (char**)realloc(key_arr_, (size_ + 1)*sizeof(char*));
            if (new_key_arr == NULL)
                throw("[Error] Unsuccessful memory reallocation for JsonObject");
            key_arr_ = new_key_arr;
            *(key_arr_ + size_) = (char*)malloc((key.size() + 1)*sizeof(char));
            if (*(key_arr_ + size_) == NULL)
                throw("[Error] Unsuccessful memory reallocation for JsonObject");
            strcpy(*(key_arr_ + size_), key.c_str());
            Json** new_arr = (Json**)realloc(val_arr_, (size_ + 1)*sizeof(Json*));
            if (new_arr == NULL)
                throw("[Error] Unsuccessful memory reallocation for JsonObject");
            val_arr_ = new_arr;
            *(val_arr_ + size_) = json;
            ++size_;
        }
    }
    else {
        // Replace 
        if (val_arr_ == NULL) {
            val_arr_ = (Json**)calloc(str_num_values_, sizeof(Json*));
            if (val_arr_ == NULL)
                throw("[Error] Unsuccessful memory allocation for JsonObject");
            *(val_arr_ + index) = json;
            size_ = str_num_values_;
            key_arr_ = (char**)calloc(str_num_values_, sizeof(char*));
            if (key_arr_ == NULL)
                throw("[Error] Unsuccessful memory allocation for JsonObject");
            *(key_arr_ + index) = (char*)malloc((key.size() + 1)*sizeof(char));
            if (*(key_arr_ + index) == NULL)
                throw("[Error] Unsuccessful memory allocation for JsonObject");
            strcpy(*(key_arr_ + index), key.c_str());
        }
        else {
            delete *(val_arr_ + index);
            *(val_arr_ + index) = json;
        }
    }
}

void JsonObject::set(const std::string& key, const JsonString& src) {
    Json* json = new JsonString(src);
    set(key, json);
}

void JsonObject::set(const std::string& key, const JsonNumber& src) {
    Json* json = new JsonNumber(src);
    set(key, json);
}

void JsonObject::set(const std::string& key, const JsonBoolean& src) {
    Json* json = new JsonBoolean(src);
    set(key, json);
}

void JsonObject::set(const std::string& key, const JsonNull& src) {
    Json* json = new JsonNull(src);
    set(key, json);
}

void JsonObject::set(const std::string& key, const JsonArray& src) {
    Json* json = new JsonArray(src);
    set(key, json);
}

void JsonObject::set(const std::string& key, const JsonObject& src) {
    Json* json = new JsonObject(src);
    set(key, json);
}

bool JsonObject::has_key(const std::string& key) {
    int index = get_key_index(key.c_str());
    if (index < 0)
        return false;
    return true;
}

bool JsonObject::is_empty() {
    if (val_arr_ == NULL) {
        if (str_ == NULL)
            return true;
        return false;
    }
    else {
        return false;
    }
}

size_t JsonObject::size() {
    if (val_arr_ == NULL) {
        if (str_ == NULL)
            return 0;
        else
            return str_num_values_;
    }
    else {
        return size_;
    }
}

void JsonObject::remove_str(int index) {
    KeyValuePointer* new_str_ptrs = (KeyValuePointer*)malloc((str_num_values_ - 1)*sizeof(KeyValuePointer));
    if (new_str_ptrs == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonObject");
    if (index == 0) {
        memcpy(new_str_ptrs, str_ptrs_ + 1, (str_num_values_ - 1)*sizeof(KeyValuePointer));
    }
    else if (index == size_ - 1) {
        memcpy(new_str_ptrs, str_ptrs_, (str_num_values_ - 1)*sizeof(KeyValuePointer));
    }
    else {
        memcpy(new_str_ptrs, str_ptrs_, index*sizeof(KeyValuePointer));
        memcpy(new_str_ptrs + index, str_ptrs_ + index + 1, (str_num_values_ - index)*sizeof(KeyValuePointer));
    }
    free(str_ptrs_);
    str_ptrs_ = new_str_ptrs;
    --str_num_values_;
}

void JsonObject::remove_arr(int index) {
    Json** new_val_arr = (Json**)malloc((size_ - 1)*sizeof(Json*));
    if (new_val_arr == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonObject");
    char** new_key_arr = (char**)malloc((size_ - 1)*sizeof(char*));
    if (new_key_arr == NULL)
        throw("[Error] Unsuccessful memory allocation for JsonObject");
    if (index == 0) {
        memcpy(new_val_arr, val_arr_ + 1, (size_ - 1)*sizeof(Json*));
        memcpy(new_key_arr, key_arr_ + 1, (size_ - 1)*sizeof(char*));
    }
    else if (index == size_ - 1) {
        memcpy(new_val_arr, val_arr_, (size_ - 1)*sizeof(Json*));
        memcpy(new_key_arr, key_arr_, (size_ - 1)*sizeof(char*));
    }
    else {
        memcpy(new_val_arr, val_arr_, index*sizeof(Json*));
        memcpy(new_key_arr, key_arr_, index*sizeof(char*));
        memcpy(new_val_arr + index, val_arr_ + index + 1, (size_ - index)*sizeof(Json*));
        memcpy(new_key_arr + index, key_arr_ + index + 1, (size_ - index)*sizeof(char*));
    }
    free(val_arr_);
    val_arr_ = new_val_arr;
    free(key_arr_);
    key_arr_ = new_key_arr;
    --size_;
}

void JsonObject::remove(const std::string& key) {
    int index = get_key_index(key.c_str());
    if (index < 0)
        throw("[Error] Key not found in JsonObject");
    else {
        if (val_arr_ == NULL) {
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
}

std::string JsonObject::stringify() {
    if (val_arr_ == NULL) {
        if (str_ == NULL) {
            return "{}";
        }
        else {
            return std::string(str_);
        }
    }
    else {
        if (str_ == NULL) {
            std::string str = "{";
            Json** val_ptr = val_arr_;
            Json** end = val_arr_ + size_;
            Json** last = val_arr_ + size_ - 1;
            char** key_ptr = key_arr_;
            while (val_ptr != end) {
                if (*val_ptr != NULL) {
                    str += "\"";
                    str += std::string(*key_ptr);
                    str += "\":";
                    str += (*val_ptr)->stringify();
                }
                if (val_ptr != last)
                    str += ",";
                ++val_ptr;
                ++key_ptr;
            }
            str += "}";
            return str;
        }
        else {
            std::string str = "{";
            Json** val_ptr = val_arr_;
            Json** end = val_arr_ + size_;
            Json** last = val_arr_ + size_ - 1;
            char** key_ptr = key_arr_;
            KeyValuePointer* str_ptr = str_ptrs_;
            KeyValuePointer* str_end = str_ptr + str_num_values_;
            while (str_ptr != str_end) {
                if (*val_ptr != NULL) {
                    str += "\"";
                    str += std::string(*key_ptr);
                    str += "\":";
                    str += (*val_ptr)->stringify();
                }
                else {
                    if (str_ptr->val_len > 0) {
                        char temp_key[str_ptr->key_len + 1];
                        strncpy(temp_key, str_ + str_ptr->key_start, str_ptr->key_len);
                        temp_key[str_ptr->key_len] = '\0';
                        str += "\"";
                        str += std::string(temp_key);
                        str += "\":";
                        char temp_val[str_ptr->val_len + 1];
                        strncpy(temp_val, str_ + str_ptr->val_start, str_ptr->val_len);
                        temp_val[str_ptr->val_len] = '\0';
                        str += std::string(temp_val);
                    }
                }
                if (val_ptr != last)
                    str += ",";
                ++val_ptr;
                ++key_ptr;
                ++str_ptr;
            }
            while (val_ptr != end) {
                if (*val_ptr != NULL) {
                    str += "\"";
                    str += std::string(*key_ptr);
                    str += "\":";
                    str += (*val_ptr)->stringify();
                }
                if (val_ptr != last)
                    str += ",";
                ++val_ptr;
                ++key_ptr;
            }
            str += "}";
            return str;
        }
    }
}
