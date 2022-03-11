#include <iostream>
#include <catch2/catch.hpp>

#include <json/jsonobject.hpp>
using namespace json;

SCENARIO("JSON object can be created successfully", "[object]") {
    WHEN("a json object is created using the string constructor") {

        JsonObject obj("{\"key\":\"value\"}");

        THEN("the key value pair can be retrieved") {
            CHECK(obj.get_string("key").get_string() == "value");
        }
    }
}

SCENARIO("Values can be retrieved from a JSON object given the key", "[object]") {
    WHEN("a JSON object is given with key value pairs") {
        JsonObject obj("{\
            \"name\" : \"Akash\",\
            \"age\" : 20,\
            \"is_tall\" : false,\
            \"car\" : null,\
            \"numbers\" : [1, 2, 3],\
            \"object\" : {\"hello\":\"world\"}}");

        THEN("the key value pairs can be retrieved") {
            CHECK(obj.get_string("name").get_string() == "Akash");
            CHECK(obj.get_number("age").get_int() == 20);
            CHECK(obj.get_boolean("is_tall").get_bool() == false);
            CHECK(obj.get_null("car").stringify() == "null");
            CHECK(obj.get_array("numbers").get_number(0).get_int() == 1);
            CHECK(obj.get_object("object").get_string("hello").get_string() == "world");
        }
    }
}

SCENARIO("Values can set for a JSON object given the key", "[object]") {
    WHEN("key value pairs are set on a JSON object") {
        JsonObject obj;
        obj.set("my_key", JsonString("hello"));
        obj.set("number_key", JsonNumber(3.14));
        obj.set("mm_kay", JsonBoolean(true));
        obj.set("they", JsonNull());
        obj.set("took", JsonArray("[4, 5]"));
        obj.set("a_jbs", JsonObject());

        THEN("the key value pairs can be retrieved") {
            CHECK(obj.get_string("my_key").get_string() == "hello");
            CHECK(obj.get_number("number_key").get_double() == 3.14);
            CHECK(obj.get_boolean("mm_kay").get_bool() == true);
            CHECK(obj.get_null("they").stringify() == "null");
            CHECK(obj.get_array("took").get_number(0).get_int() == 4);
            CHECK(obj.get_object("a_jbs").size() == 0);
        }
    }
}

SCENARIO("Existence of keys can be checked in a JSON object", "[object]") {
    GIVEN("an empty JSON object") {
        JsonObject obj;

        WHEN("the object is checked for a given key") {
            const auto has_key = obj.has_key("hello");

            THEN("a false is returned") {

                CHECK(has_key == false);
            }

        }

        WHEN("a new value is set for a given key") {
            obj.set("hello", JsonString("world"));

            THEN("the key exists in the JSON object") {
                CHECK(obj.has_key("hello") == true);
            }
        }
    }

    GIVEN("a JSON object with a key value pair") {
        JsonObject obj("{\"key\":342}");

        WHEN("the object is checked for the given key") {
            const auto has_key = obj.has_key("key");

            THEN("a true is returned") {

                CHECK(has_key == true);
            }
        }
    }
}

SCENARIO("JSON objects can be checked for empty", "[object]") {
    GIVEN("an empty JSON object") {
        JsonObject obj;

        WHEN("the object is checked for empty") {
            const auto is_empty = obj.is_empty(); 

            THEN("a true is returned") {
                CHECK(is_empty == true);
            }
        }

        WHEN("a new value is set for a given key") {
            obj.set("wer", JsonString("her"));

            THEN("a false is returned") {
                CHECK(obj.is_empty() == false);
            }
        }
    }
}

SCENARIO("key value pairs can be removed from JSON objects", "[object]") {
    GIVEN("a JSON object with one key value pair") {
        JsonObject obj("{\"key\": 123}");

        WHEN("a key is removed") {
            obj.remove("key");

            THEN("the object has a size of zero") {
                CHECK(obj.size() == 0);
            }
        }

        WHEN("a new key value pair is added and then removed") {
            obj.set("not", JsonNumber(3.12));
            obj.remove("not");

            THEN("the key no longer exists in the object") {
                obj.remove("not");
                CHECK(obj.has_key("not") == false);
            }
        }
    }
}

SCENARIO("JSON objects can be stringified successfully", "[stringify, object]") {
    GIVEN("an empty JSON object") {
        const auto str = "{}";
        JsonObject obj(str);

        WHEN("stringify is called on the object") {
            const auto stringified_str = obj.stringify();

            THEN("a string representation is returned") {
                CHECK(stringified_str == str);
            }
        }
    }
    
    GIVEN("an object with key value pairs") {
        const auto str = "{\"nu\":1, \"na\":null, \"asd\":\"hello\"}";
        JsonObject obj(str);

        WHEN("stringify is called on the object") {
            const auto stringified_str = obj.stringify();

            THEN("a string representation is returned") {
                CHECK(stringified_str == str);
            }
        }
    }
    
    GIVEN("an object with key value pairs with a new added key") {
        const auto str = "{\"key\": \"value\"}";
        JsonObject obj(str);
        obj.set("num", JsonNumber(23));

        WHEN("stringify is called on the object") {
            const auto expected_str = "{\"key\": \"value\",\"num\":23}";
            const auto stringified_str = obj.stringify();

            THEN("a string representation is returned") {
                CHECK(stringified_str == expected_str);
            }
        }
    }
}
