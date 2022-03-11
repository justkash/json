#include <catch2/catch.hpp>

#include <json/jsonarray.hpp>
using namespace json;

SCENARIO("JSON array can be created successfully", "[array]") {
    WHEN("A JSON array is created using the string constructor") {

        JsonArray json_arr("[{\"key\":333},1,22.2,\"asd\"]");

        THEN("the integer can be retrieved") {
            CHECK(json_arr.get_number(1).get_int() == 1);
        }

        THEN("the double value can be retrieved") {
            CHECK(json_arr.get_number(2).get_double() == 22.2);
        }

        THEN("the string value can be retrieved") {
            CHECK(json_arr.get_string(3).get_string() == "asd");
        }
    }
}

SCENARIO("Values can be successfully retrieved from the JSON array", "[array]") {
    WHEN("A JSON array is created using the string constructor") {

        JsonArray json_arr("[\
            \"Akash\",\
            20,\
            false,\
            null,\
            [1, 2, 3],\
            {\"hello\":\"world\"}]");

        THEN("the string value can be retrieved") {
            CHECK(json_arr.get_string(0).get_string() == "Akash");
        }

        THEN("the string value can be retrieved") {
            CHECK(json_arr.get_number(1).get_int() == 20);
        }

        THEN("the string value can be retrieved") {
            CHECK(json_arr.get_boolean(2).get_bool() == false);
        }
        
        THEN("the string value can be retrieved") {
            CHECK(json_arr.get_null(3).stringify() == "null");
        }

        THEN("the string value can be retrieved") {
            CHECK(json_arr.get_array(4).get_number(1).get_int() == 2);
        }

        THEN("the string value can be retrieved") {
            CHECK(json_arr.get_object(5).get_string("hello").get_string() == "world");
        }
    }
}

SCENARIO("Values can be successfully set in the JSON array", "[array]") {
    WHEN("A JSON array is created using the string constructor and mutated") {

        JsonArray arr("[\"key\", 1]");

        arr.set(0, JsonString("hello"));
        arr.set(1, JsonNumber(1)); 
        THEN("the string and number values can be retrieved") {
            CHECK(arr.get_string(0).get_string() == "hello");
            CHECK(arr.get_number(1).get_int() == 1);
        }

        arr.set(0, JsonBoolean(true));
        arr.set(1, JsonNull());
        THEN("the boolean and null values can be retrieved") {
            CHECK(arr.get_boolean(0).get_bool() == true);
            CHECK(arr.get_null(1).stringify() == "null");
        }

        arr.set(0, JsonArray("[1, 2, 3]"));
        arr.set(1, JsonObject("{}"));
        THEN("the array and object values can be retrieved") {
            CHECK(arr.get_array(0).get_number(0).get_int() == 1);
            CHECK(arr.get_object(1).size() == 0);
        }

    }
}

SCENARIO("Values can be successfully pushed into the JSON array", "[array]") {
    WHEN("A JSON array is created using the string constructor and mutated") {

        JsonArray arr;
        arr.push_back(JsonString("hello"));
        arr.push_back(JsonNumber(1.4));
        arr.push_back(JsonBoolean(true));
        arr.push_back(JsonNull());
        arr.push_back(JsonArray("[1, 3]"));
        arr.push_back(JsonObject("{\"hello\":\"world\"}"));
        THEN("the correct values can be retrieved back") {
            CHECK(arr.get_string(0).get_string() == "hello");
            CHECK(arr.get_number(1).get_double() == 1.4);
            CHECK(arr.get_boolean(2).get_bool() == true);
            CHECK(arr.get_null(3).stringify() == "null");
            CHECK(arr.get_array(4).get_number(1).get_int() == 3);
            CHECK(arr.get_object(5).get_string("hello").get_string() == "world");
        }
    }
}

SCENARIO("Values can be successfully inserted into the JSON array", "[array]") {
    WHEN("A string is inserted into the JSON array") {
        JsonArray arr("[1, \"hello\"]");
        JsonString test1("hello");
        arr.insert(0, test1);
        THEN("the string value can be retrieved") {
            CHECK(arr.get_string(0).get_string() == "hello");
        }
    }

    WHEN("A number is inserted into the JSON array") {
        JsonArray arr2;
        JsonNumber test2(1.2);
        arr2.insert(0, test2);
        THEN("the number value can be retrieved") {
            CHECK(arr2.get_number(0).get_double() == 1.2);
        }
    }

    WHEN("A boolean is inserted into the JSON array") {
        JsonArray arr3("[1, 2, 3]");
        JsonBoolean test3(true);
        arr3.insert(3, test3);
        THEN("the string value can be retrieved") {
            CHECK(arr3.get_boolean(3).get_bool() == true);
        }
    }

    WHEN("An array is inserted into the JSON array") {
        JsonArray arr4("[]");
        arr4.insert(0, JsonArray("[1, 2, 3]"));
        THEN("the string value can be retrieved") {
            CHECK(arr4.get_array(0).get_number(2).get_int() == 3);
        }
    }
        
    WHEN("A null is inserted into the JSON array") {
        JsonArray arr5("[1,2, 3]");
        arr5.insert(1, JsonNull());
        THEN("the string value can be retrieved") {
            CHECK(arr5.get_null(1).stringify() == "null");
        }
    }

    WHEN("An object is inserted into the JSON array") {
        JsonArray arr6;
        arr6.insert(0, JsonObject());
        THEN("the string value can be retrieved") {
            CHECK(arr6.get_object(0).size() == 0);
        }
    }
}

SCENARIO("JSON arrays can be successfully resized", "[array]") {
    WHEN("values are added after a resize") {
        JsonArray arr("[]");
        arr.resize(5);
        JsonString temp("hello");
        arr.push_back(temp);
        THEN("the values can be correctly retrieved") {
            CHECK(arr.get_string(0).get_string() == "hello");
        }
    }

    WHEN("the array is resized to zero") {
        JsonArray arr2("[1, 2, 3]");
        arr2.resize(0);
        THEN("the array is emptied") {
            CHECK(arr2.size() == 0);
        }
    }

    WHEN("the array is resized below the current size") {
        JsonArray arr3("[\"hello\", 1, null]");
        arr3.resize(2);
        THEN("the unaffected values can be retrieved") {
            CHECK(arr3.size() == 2);
            CHECK(arr3.get_number(1).get_int() == 1);
        }
    }
}

SCENARIO("JSON arrays can have some elements removed", "[array]") {
    WHEN("values at specific indices are removed") {
        JsonArray arr("[1, 2, 3]");
        arr.remove(2);
        arr.remove(0);
        THEN("the remaining elements can be retrieved") {
            CHECK(arr.get_number(0).get_int() == 2);
        }
    }
}

SCENARIO("Empty JSON arrays can be checked", "[array]") {
    WHEN("the array is empty") {
        JsonArray arr("[]");

        THEN("the array is actually empty") {
            CHECK(arr.is_empty() == true);
        }
    }

    WHEN("the array contains values") {
        JsonArray arr2("[1, 2, 3]");
        THEN("") {
            CHECK(arr2.is_empty() == false);
        }
    }
}

SCENARIO("JSON arrays can be stringified successfully", "[stringify, array]") {
    WHEN("Stringify is called on an empty JSON array") {
        const auto empty_arr_str = "[]";
        JsonArray arr(empty_arr_str);

        THEN("a string representing an empty json array is returned") {
            CHECK(arr.stringify() == empty_arr_str);
        }
    }

    WHEN("Stringify is called on a JSON array") {
        const auto json_arr_str = "[1, null, \"hello\"]";
        JsonArray json_arr(json_arr_str);

        THEN("a string representing the array is returned") {
            CHECK(json_arr.stringify() == json_arr_str);
        }
    }

    WHEN("Stringify is called on a mutable JSON array") {
        JsonArray arr("[1, 2, 3]");
        JsonString str("hello");
        arr.push_back(str);

        THEN("a string representing the array is returned") {
            CHECK(arr.stringify() == "[1, 2, 3,\"hello\"]");
        }
    }
}
