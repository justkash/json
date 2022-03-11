#include <cstring>

#include <catch2/catch.hpp>

#include <json/jsonnumber.hpp>
using namespace json;

SCENARIO("JSON numbers can be created successfully", "[number]") {
    WHEN("A JSON number is created using the int constructor for positive values") {

        const auto num = 42;
        const JsonNumber json_num { num };

        THEN("the JSON number contains the correct data") {
            CHECK(json_num.get_int() == num);
        }
    }

    WHEN("A JSON number is created using the int constructor for negative values") {

        const auto num = -42;
        const JsonNumber json_num { num };

        THEN("the JSON number contains the correct data") {
            CHECK(json_num.get_int() == num);
        }
    }

    WHEN("A JSON number is created using the double constructor for positive values") {

        const auto num = 42.23;
        const JsonNumber json_num { num };

        THEN("the JSON number contains the correct data") {
            CHECK(json_num.get_double() == num);
        }
    }

    WHEN("A JSON number is created using the double constructor for negative values") {

        const auto num = -42.23;
        const JsonNumber json_num { num };

        THEN("the JSON number contains the correct data") {
            CHECK(json_num.get_double() == num);
        }
    }

    WHEN("A JSON number is created using the string constructor for double values") {

        const auto num = 42.23;
        const auto num_str = std::to_string(num);
        const JsonNumber json_num { num_str };

        THEN("the JSON number contains the correct data") {
            CHECK(json_num.get_double() == num);
        }
    }

    WHEN("A JSON number is created using the string constructor for int values") {

        const auto num = 42;
        const auto num_str = std::to_string(num);
        const JsonNumber json_num { num_str };

        THEN("the JSON number contains the correct data") {
            CHECK(json_num.get_double() == num);
        }
    }

    WHEN("A JSON number is created using the copy constructor") {

        const auto num = 42;
        const JsonNumber json_num { num };
        const JsonNumber json_num_copy { json_num };

        THEN("the JSON number contains the correct data") {
            CHECK(json_num_copy.get_int() == num);
        }
    }

    WHEN("A JSON number is created using the assignment operator") {

        const auto num = 42;
        const JsonNumber json_num { num };
        const JsonNumber json_num_copy = json_num;

        THEN("the JSON number contains the correct data") {
            CHECK(json_num_copy.get_int() == num);
        }
    }
}

SCENARIO("JSON numbers can be stringified successfully", "[stringify, number]") {
    WHEN("A stringify is called on a JSON number representing an integer") {

        const auto num = 42;
        JsonNumber json_num { num };
        const auto stringified_json_str = json_num.stringify();

        THEN("the correct string with double-quotes is returned") {
            CHECK(json_num.is_int() == true);
            const std::string expected_str =  std::to_string(num);
            CHECK(stringified_json_str == expected_str);
        }
    }

    WHEN("A stringify is called on a JSON number representing a floating-point value") {

        const std::string num_str = "42.234";
        JsonNumber json_num { num_str };
        const auto stringified_json_str = json_num.stringify();

        THEN("the correct string with double-quotes is returned") {
            CHECK(stringified_json_str == num_str);
        }
    }
}
