/*
 * File: json.cpp
 *
 * Created By: Akash Melethil, Bryce Besler
 * Created: 2014.10.24
 *
 * Description:
 *  This is an abstract class created to take advantage of polymorphism.
 *
 * History:
 *  2014.10.24    Akash Melethil    Created
 *
 * Notes:
 *  - None
 */

#include <cctype>

#include <json/json.hpp>

namespace json {

    /// Exception Handling
    ///
    /// Exceptions are identified by an error code and a short description
    RuntimeException::RuntimeException(std::string&& description, ErrorCode error_code) noexcept :
        std::runtime_error(description),
        message(std::move(description)),
        error_code(error_code) {}

    const char* RuntimeException::what() const noexcept {
        return message.c_str();
    }

    Json::JsonType Json::find_type(const char* str) {
        const char* first_non_space_char = Json::find_next_non_space_char(str);
        switch(*first_non_space_char) {
            case '{':
                return JSONOBJECT;
                break;
            case '"':
                return JSONSTRING;
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0':
            case '-':
                return JSONNUMBER;
                break;
            case 't':
            case 'f':
                return JSONBOOLEAN;
                break;
            case '[':
                return JSONARRAY;
                break;
            case 'n':
                return JSONNULL;
                break;
            default:
                throw RuntimeException { "Invalid JSON string", ErrorCode::InvalidJsonString };
        }
    }

    const char* Json::find_next_char(const char* str, const char to_find) {
       const char* ptr = str;
       while (*ptr != to_find && *ptr != '\0')
           ++ptr;
       return ptr;
    }

    const char* Json::find_next_non_space_char(const char* str) {
        const char* ptr = str;
        while (isspace(*ptr) && *ptr != '\0')
            ++ptr;
        return ptr;
    }

    const char* Json::find_next_either_chars(const char* str, const char one, const char two) {
        const char* ptr = str;
        while (*ptr != one && *ptr != two && *ptr != '\0')
            ++ptr;
        return ptr;
    }

    bool Json::check_contains(const char* big_str, const char* small_str) {
        const char* small_ptr = small_str;
        const char* big_ptr = big_str;
        while (*small_ptr != '\0') {
            if (*small_ptr != *big_ptr) return false;
            ++small_ptr;
            ++big_ptr;
        }
        return true;
    }

    const char* Json::find_bracket_end(const char* str) {
        // Assume first char is '[' or '{'
        const char* ptr = str + 1;
        char end = *str + 2;
        while (*ptr != '\0') {
            if (*ptr == '{' || *ptr == '[') {
                ptr = find_bracket_end(ptr) + 1;
            }
            if (*ptr == end) {
                return ptr;
            }
            ++ptr;
        }
        return ptr;
    }

    Json::~Json() {}

} // json namespace
