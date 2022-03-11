#include <cstring>

#include <catch2/catch.hpp>

#include <json/jsonstring.hpp>
using namespace json;

SCENARIO("JSON strings can be created successfully", "[string]") {
    WHEN("A JSON string is created using the std::string constructor") {

        const std::string str { "Hello world." };
        JsonString json_str(str);

        THEN("the JSON string contains the correct data") {
            CHECK(json_str.get_string() == str);
        }
    }

    WHEN("A JSON string is created using the char* constructor") {

        const char* c_str = "Hello world.";
        JsonString json_str(c_str);

        THEN("the JSON string contains the correct data") {
            CHECK(strcmp(json_str.get_string().c_str(), c_str) == 0);
        }
    }

    WHEN("A JSON string is created using the copy constructor") {

        const std::string str { "Hello world." };
        JsonString json_str(str);
        JsonString json_str_cpy(json_str);

        THEN("the JSON string contains the correct data") {
            CHECK(json_str_cpy.get_string() == str);
        }
    }

    WHEN("A JSON string is created using the assignment operator") {

        const std::string str { "Hello world." };
        JsonString json_str(str);
        JsonString json_str_cpy = json_str;

        THEN("the JSON string contains the correct data") {
            CHECK(json_str_cpy.get_string() == str);
        }
    }

}

SCENARIO("JSON strings can be stringified successfully", "[string]") {
    WHEN("A stringify is called on a JSON string") {

        const std::string str { "Hello world." };
        JsonString json_str(str);
        const auto stringified_json_str = json_str.stringify();

        THEN("the correct string with double-quotes is returned") {
            const std::string expected_str =  "\"" + str + "\"";
            CHECK(stringified_json_str == expected_str);
        }
    }
}
