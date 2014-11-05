#include <cstdio>
#include <ctime>
#include <cstring>
#include <string>
#include <iostream>
#include <cassert>

#include "../json/json.hpp"
#include "../json/jsonstring.hpp"
#include "../json/jsonnumber.hpp"
#include "../json/jsonboolean.hpp"
#include "../json/jsonnull.hpp"
#include "../json/jsonarray.hpp"
#include "../json/jsonobject.hpp"

using namespace std;

// JsonString
void test_copy_JsonString() {
    JsonString test("\"Hello world.\"");
    JsonString test2(test);
    assert(test2.get_string() == "Hello world.");
}

void test_assignment_JsonString() {
    JsonString temp1("\"Hello world.\"");
    JsonString temp2 = temp1;
    assert(temp2.get_string() == "Hello world.");
}

void test_constructor_JsonString() {
    JsonString temp1("Hello world.");
    assert(temp1.get_string() == "Hello world.");
}

void test_stringify_JsonString() {
    JsonString temp1("Hello world.");
    assert(temp1.stringify() == "\"Hello world.\"");
}

// JsonNumber
void test_string_constructor_double_JsonNumber() {
    JsonNumber temp("42.23");
    assert(temp.get_double() == 42.23);
}

void test_string_constructor_int_JsonNumber() {
    JsonNumber temp("42");
    assert(temp.get_int() == 42);
}

void test_int_constructor_JsonNumber() {
    JsonNumber temp(42);
    assert(temp.get_int() == 42);
}

void test_double_constructor_JsonNumber() {
    JsonNumber temp(42.23);
    assert(temp.get_double() == 42.23);
}

void test_get_positive_int_JsonNumber() {
    JsonNumber temp("42");
    assert(temp.get_int() == 42);
}

void test_get_negative_int_JsonNumber() {
    JsonNumber temp("-42");
    assert(temp.get_int() == -42);
}

void test_get_positive_double_JsonNumber() {
    JsonNumber temp("42.234");
    assert(temp.get_double() == 42.234);
}

void test_get_negative_double_JsonNumber() {
    JsonNumber temp("-42.234");
    assert(temp.get_double() == -42.234);
}

void test_stringify_int_JsonNumber() {
    JsonNumber temp("42");
    assert(temp.stringify() == "42");
}

void test_stringify_double_JsonNumber() {
    JsonNumber temp("42.234");
    assert(temp.stringify() == "42.234");
}

void test_is_int_JsonNumber() {
    JsonNumber temp("42");
    assert(temp.is_int() == true);
}

void test_copy_JsonNumber() {
    JsonNumber temp("42");
    JsonNumber temp2(temp);
    assert(temp2.get_int() == 42);
}

void test_assignment_JsonNumber() {
    JsonNumber temp("42");
    JsonNumber temp2 = temp;
    assert(temp2.get_int() == 42);
}

// JsonBoolean
void test_string_constructor_true_JsonBoolean() {
    JsonBoolean temp("true");
    assert(temp.get_bool() == true);
}

void test_string_constructor_false_JsonBoolean() {
    string a = "false";
    JsonBoolean temp(a);
    assert(temp.get_bool() == false);
}

void test_bool_constructor_true_JsonBoolean() {
    JsonBoolean temp(true);
    assert(temp.get_bool() == true);
}

void test_bool_constructor_false_JsonBoolean() {
    JsonBoolean temp(false);
    assert(temp.get_bool() == false);
}

void test_stringify_true_JsonBoolean() {
    JsonBoolean temp("true");
    assert(temp.stringify() == "true");
}

void test_stringify_false_JsonBoolean() {
    JsonBoolean temp("false");
    assert(temp.stringify() == "false");
}

// JsonNull
void test_string_constructor_JsonNull() {
    JsonNull temp("null");
    assert(temp.stringify() == "null");
}

void test_empty_constructor_JsonNull() {
    JsonNull temp;
    assert(temp.stringify() == "null");
}

// JsonArray
void test_string_constructor_JsonArray() {
    JsonArray temp("[{\"key\":333},1,22.2,\"asd\"]");
    assert(temp.get_string(3).get_string() == "asd");
}

void test_get_JsonArray() {
    JsonArray arr("[\
        \"Akash\",\
        20,\
        false,\
        null,\
        [1, 2, 3],\
        {\"hello\":\"world\"}]");
    assert(arr.get_string(0).get_string() == "Akash");
    assert(arr.get_number(1).get_int() == 20);
    assert(arr.get_boolean(2).get_bool() == false);
    assert(arr.get_null(3).stringify() == "null");
    assert(arr.get_array(4).get_number(1).get_int() == 2);
    assert(arr.get_object(5).get_string("hello").get_string() == "world");
}

void test_set_JsonArray() {
    JsonArray arr("[\"key\", 1]");
    arr.set(0, JsonString("hello"));
    arr.set(1, JsonNumber(1)); 
    assert(arr.get_string(0).get_string() == "hello");
    assert(arr.get_number(1).get_int() == 1);
    arr.set(0, JsonBoolean(true));
    arr.set(1, JsonNull());
    assert(arr.get_boolean(0).get_bool() == true);
    assert(arr.get_null(1).stringify() == "null");
    arr.set(0, JsonArray("[1, 2, 3]"));
    arr.set(1, JsonObject("{}"));
    assert(arr.get_array(0).get_number(0).get_int() == 1);
    assert(arr.get_object(1).size() == 0);
}

void test_push_back_JsonArray() {
    JsonArray arr;
    arr.push_back(JsonString("hello"));
    arr.push_back(JsonNumber(1.4));
    arr.push_back(JsonBoolean(true));
    arr.push_back(JsonNull());
    arr.push_back(JsonArray("[1, 3]"));
    arr.push_back(JsonObject("{\"hello\":\"world\"}"));
    assert(arr.get_string(0).get_string() == "hello");
    assert(arr.get_number(1).get_double() == 1.4);
    assert(arr.get_boolean(2).get_bool() == true);
    assert(arr.get_null(3).stringify() == "null");
    assert(arr.get_array(4).get_number(1).get_int() == 3);
    assert(arr.get_object(5).get_string("hello").get_string() == "world");
}

void test_insert_JsonArray() {
    JsonArray arr("[1, \"hello\"]");
    JsonString test1("hello");
    arr.insert(0, test1);
    assert(arr.get_string(0).get_string() == "hello");

    JsonArray arr2;
    JsonNumber test2(1.2);
    arr2.insert(0, test2);
    assert(arr2.get_number(0).get_double() == 1.2);

    JsonArray arr3("[1, 2, 3]");
    JsonBoolean test3(true);
    arr3.insert(3, test3);
    assert(arr3.get_boolean(3).get_bool() == true);

    JsonArray arr4("[]");
    arr4.insert(0, JsonArray("[1, 2, 3]"));
    assert(arr4.get_array(0).get_number(2).get_int() == 3);
    
    JsonArray arr5("[1,2, 3]");
    arr5.insert(1, JsonNull());
    assert(arr5.get_null(1).stringify() == "null");

    JsonArray arr6;
    arr6.insert(0, JsonObject());
    assert(arr6.get_object(0).size() == 0);
}

void test_resize_JsonArray() {
    JsonArray arr("[]");
    arr.resize(5);
    JsonString temp("hello");
    arr.push_back(temp);
    assert(arr.get_string(0).get_string() == "hello");
    JsonArray arr2("[1, 2, 3]");
    arr2.resize(0);
    assert(arr2.size() == 0);
    JsonArray arr3("[\"hello\", 1, null]");
    arr3.resize(2);
    assert(arr3.size() == 2 && arr3.get_number(1).get_int() == 1);
}

void test_remove_JsonArray() {
    JsonArray arr("[1, 2, 3]");
    arr.remove(2);
    arr.remove(0);
    assert(arr.get_number(0).get_int() == 2);
}

void test_empty_JsonArray() {
    JsonArray arr("[]");
    assert(arr.is_empty() == true);
    JsonArray arr2("[1, 2, 3]");
    assert(arr2.is_empty() == false);
}

void test_stringify_JsonArray() {
    JsonArray arr("[]");
    assert(arr.stringify() == "[]");
    JsonArray arr2("[1, null, \"hello\"]");
    assert(arr2.stringify() == "[1, null, \"hello\"]");
    JsonArray arr3("[1, 2, 3]");
    JsonString str("hello");
    arr3.push_back(str);
    assert(arr3.stringify() == "[1, 2, 3,\"hello\"]");
}

// JsonObject
void test_string_constructor_JsonObject() {
    JsonObject obj("{\"key\":\"value\"}");
    assert(obj.get_string("key").get_string() == "value");
}

void test_get_JsonObject() {
    JsonObject obj("{\
        \"name\" : \"Akash\",\
        \"age\" : 20,\
        \"is_tall\" : false,\
        \"car\" : null,\
        \"numbers\" : [1, 2, 3],\
        \"object\" : {\"hello\":\"world\"}}");
    assert(obj.get_string("name").get_string() == "Akash");
    assert(obj.get_number("age").get_int() == 20);
    assert(obj.get_boolean("is_tall").get_bool() == false);
    assert(obj.get_null("car").stringify() == "null");
    assert(obj.get_array("numbers").get_number(0).get_int() == 1);
    assert(obj.get_object("object").get_string("hello").get_string() == "world");
}

void test_set_JsonObject() {
    JsonObject obj;
    obj.set("my_key", JsonString("hello"));
    obj.set("number_key", JsonNumber(3.14));
    obj.set("mm_kay", JsonBoolean(true));
    obj.set("they", JsonNull());
    obj.set("took", JsonArray("[1, \"hello\"]"));
    obj.set("took", JsonArray("[4, 5]"));
    obj.set("a_jbs", JsonObject());
    assert(obj.get_string("my_key").get_string() == "hello");
    assert(obj.get_number("number_key").get_double() == 3.14);
    assert(obj.get_boolean("mm_kay").get_bool() == true);
    assert(obj.get_null("they").stringify() == "null");
    assert(obj.get_array("took").get_number(0).get_int() == 4);
    assert(obj.get_object("a_jbs").size() == 0);
}

void test_has_key_JsonObject() {
    JsonObject obj;
    assert(obj.has_key("hello") == false);
    obj.set("hello", JsonString("world"));
    assert(obj.has_key("hello") == true);

    JsonObject obj2("{\"key\":342}");
    assert(obj2.has_key("key") == true);
}

void test_is_empty_JsonObject() {
    JsonObject obj;
    assert(obj.is_empty() == true);
    obj.set("wer", JsonString("her"));
    assert(obj.is_empty() == false);
}

void test_remove_JsonObject() {
    JsonObject obj("{\"key\": 123}");
    obj.remove("key");
    assert(obj.size() == 0);
    obj.set("not", JsonNumber(3.12));
    obj.remove("not");
    assert(obj.has_key("not") == false);
}

void test_stringify_JsonObject() {
    JsonObject obj("{}");
    assert(obj.stringify() == "{}");
    JsonObject obj2("{\"nu\":1, \"na\":null, \"asd\":\"hello\"}");
    assert(obj2.stringify() == "{\"nu\":1, \"na\":null, \"asd\":\"hello\"}");
    JsonObject obj3("{\"key\": \"value\"}");
    obj3.set("num", JsonNumber(23));
    assert(obj3.stringify() == "{\"key\": \"value\",\"num\":23}");
}

int main() {
    clock_t start, stop;
    start = clock();
    try {
        // JsonString
        test_copy_JsonString();
        test_assignment_JsonString();
        test_constructor_JsonString();
        test_stringify_JsonString();
        
        // JsonNumber
        test_string_constructor_double_JsonNumber();
        test_string_constructor_int_JsonNumber();
        test_int_constructor_JsonNumber();
        test_double_constructor_JsonNumber();
        test_get_positive_int_JsonNumber();
        test_get_negative_int_JsonNumber();
        test_get_positive_double_JsonNumber();
        test_get_negative_double_JsonNumber();
        test_stringify_int_JsonNumber();
        test_stringify_double_JsonNumber();
        test_is_int_JsonNumber();
        test_copy_JsonNumber();
        test_assignment_JsonNumber();
        
        // JsonBoolean
        test_string_constructor_true_JsonBoolean();
        test_string_constructor_false_JsonBoolean();
        test_bool_constructor_true_JsonBoolean();
        test_bool_constructor_false_JsonBoolean();
        test_stringify_true_JsonBoolean();
        test_stringify_false_JsonBoolean();

        // JsonNull
        test_string_constructor_JsonNull();
        test_empty_constructor_JsonNull();

        // JsonArray
        test_string_constructor_JsonArray();
        test_get_JsonArray();
        test_set_JsonArray();
        test_push_back_JsonArray();
        test_insert_JsonArray();
        test_resize_JsonArray();
        test_remove_JsonArray();
        test_empty_JsonArray();
        test_stringify_JsonArray();

        // JsonObject
        test_string_constructor_JsonObject();
        test_get_JsonObject();
        test_set_JsonObject();
        test_has_key_JsonObject();
        test_is_empty_JsonObject();
        test_remove_JsonObject();
        test_stringify_JsonObject();

        puts("Tests successfully completed.");
    }
    catch (const char* exception) {
        printf("Test failed with exception:\n%s\n", exception);
    }
    stop = clock();
    printf("Execution took %f seconds.\n", (((float)(stop - start))/CLOCKS_PER_SEC));
}
