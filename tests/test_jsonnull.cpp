#include <catch2/catch.hpp>

#include <json/jsonnull.hpp>
using namespace json;

SCENARIO("JSON nulls can be created successfully", "[null]") {
    WHEN("A JSON null is created using the string constructor") {

        const auto str = "null";
        JsonNull json_null { str };

        THEN("the JSON null contains the correct data") {
            CHECK(json_null.stringify() == str);
        }
    }

    WHEN("A JSON null is created using the empty constructor") {

        JsonNull json_null;

        THEN("the JSON null contains the correct data") {
            CHECK(json_null.stringify() == "null");
        }
    }
}
