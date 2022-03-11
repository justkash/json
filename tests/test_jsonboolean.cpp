#include <catch2/catch.hpp>

#include <json/jsonboolean.hpp>
using namespace json;

SCENARIO("JSON booleans can be created successfully", "[boolean]") {
    WHEN("A JSON boolean is created using the string constructor for true values") {

        const auto bool_str = "true";
        const JsonBoolean json_bool { bool_str };

        THEN("the JSON boolean contains the correct data") {
            CHECK(json_bool.get_bool() == true);
        }
    }

    WHEN("A JSON boolean is created using the string constructor for false values") {

        const auto bool_str = "false";
        const JsonBoolean json_bool { bool_str };

        THEN("the JSON boolean contains the correct data") {
            CHECK(json_bool.get_bool() == false);
        }
    }

    WHEN("A JSON boolean is created using the bool constructor for true values") {

        const auto bool_val = true;
        const JsonBoolean json_bool { bool_val };

        THEN("the JSON boolean contains the correct data") {
            CHECK(json_bool.get_bool() == bool_val);
        }
    }

    WHEN("A JSON boolean is created using the bool constructor for false values") {

        const auto bool_val = false;
        const JsonBoolean json_bool { bool_val };

        THEN("the JSON boolean contains the correct data") {
            CHECK(json_bool.get_bool() == bool_val);
        }
    }

}

SCENARIO("JSON booleans can be stringified successfully", "[stringify, boolean]") {
    WHEN("Stringify is called on a JSON boolean representing a true") {

        const auto bool_str = "true";
        JsonBoolean json_bool { bool_str };
        const auto stringified_json_str = json_bool.stringify();

        THEN("the correct string with double-quotes is returned") {
            CHECK(stringified_json_str == bool_str);
        }
    }

    WHEN("Stringify is called on a JSON boolean representing a false") {

        const auto bool_str = "false";
        JsonBoolean json_bool { bool_str };
        const auto stringified_json_str = json_bool.stringify();

        THEN("the correct string with double-quotes is returned") {
            CHECK(stringified_json_str == bool_str);
        }
    }
}
