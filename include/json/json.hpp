/*
 * File: json.hpp
 *
 * Created By: Akash Melethil, Bryce Besler
 * Created: 2014.10.24
 *
 * Description:
 *  This is an abstract class created to take advantage of polymorphism
 *
 * History:
 *  2014.10.24    Akash Melethil    Created
 *
 * Notes:
 *  - None
 */

#ifndef JSON_HPP
#define JSON_HPP

#include <string>

namespace json {

    enum class ErrorCode {
        InvalidJsonString = -1,
        ErrorWhileAllocatingMemory = -2,

    };

    class RuntimeException : public std::runtime_error {
        public:
            explicit RuntimeException(std::string&& description, ErrorCode error_code) noexcept;
            const char* what () const noexcept override;

        private:
            std::string message;
            ErrorCode error_code;
    };

    class Json {
        public:
        virtual std::string stringify() = 0;
        virtual ~Json() = 0;
       
        protected:
        enum JsonType {
            JSONSTRING,
            JSONNUMBER,
            JSONBOOLEAN,
            JSONNULL,
            JSONARRAY,
            JSONOBJECT
        };

        static JsonType find_type(const char*);
        static const char* find_next_char(const char*, const char);
        static const char* find_next_non_space_char(const char*);
        static const char* find_next_either_chars(const char*, const char, const char);
        static bool check_contains(const char*, const char*);
        static const char* find_bracket_end(const char*);
        
    };

}

#endif
