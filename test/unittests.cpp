#include <stdio.h>
#include <time.h>
#include <string.h>
#include <string>
#include <iostream>
#include <assert.h>

#include "../json/json.hpp"
#include "../json/jsonstring.hpp"
#include "../json/jsonnumber.hpp"
#include "../json/jsonboolean.hpp"
#include "../json/jsonnull.hpp"
#include "../json/jsonarray.hpp"

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
    JsonArray temp("[{asd},1,12.3,\"asd\"]");
    assert(dynamic_cast<JsonString&>(temp.get(3)).get_string() == "asd");
}

void test_get_JsonString_JsonArray() {
    JsonArray temp("[{asd},1,12.3,\"asd\"]");
    assert(dynamic_cast<JsonString&>(temp.get(3)).get_string() == "asd");
}

void test_get_JsonNumber_JsonArray() {
    JsonArray temp("[{asd},1,12.3,\"asd\"]");
    assert(dynamic_cast<JsonNumber&>(temp.get(1)).get_int() == 1);
}

void test_get_JsonBoolean_JsonArray() {
    JsonArray temp("[{asd},1,12.3,\"asd\", true]");
    assert(dynamic_cast<JsonBoolean&>(temp.get(4)).get_bool() == true);
}

void test_get_JsonArray_JsonArray() {
    JsonArray temp("[{asd},1,12.3,\"asd\", [1, 2, 3]]");
    JsonArray arr = dynamic_cast<JsonArray&>(temp.get(4));
    assert(dynamic_cast<JsonNumber&>(arr.get(0)).get_int() == 1);
}

void test_get_JsonNull_JsonArray() {
    JsonArray temp("[{asd},1,12.3,\"asd\", null]");
    assert(dynamic_cast<JsonNull&>(temp.get(4)).stringify() == "null");
}
/*
void test_get_JsonObject_JsonArray() {
    JsonArray temp("[{\"key\": \"value\"},1,12.3,\"asd\"]");

}*/

void test_set_JsonString_JsonArray() {
    JsonArray temp("[{asd},1,12.3,\"asd\"]");
    JsonString test("asdf");
    temp.set(0, test);
    assert(dynamic_cast<JsonString&>(temp.get(0)).get_string() == "asdf");
}

void test_set_JsonNumber_JsonArray() {
    JsonArray temp("[{asd},1,12.3,\"asd\"]");
    JsonNumber test(1);
    temp.set(0, test);
    assert(dynamic_cast<JsonNumber&>(temp.get(0)).get_int() == 1);
}

void test_set_JsonBoolean_JsonArray() {
    JsonArray temp("[{asd},1,12.3,\"asd\", true]");
    JsonBoolean test(true);
    temp.set(1, test);
    assert(dynamic_cast<JsonBoolean&>(temp.get(1)).get_bool() == true);
}

void test_set_JsonArray_JsonArray() {
    JsonArray temp("[{asd},1,12.3,\"asd\", [1, 2, 3]]");
    JsonArray test("[1, 2, 3]");
    temp.set(2, test);
    JsonArray arr = dynamic_cast<JsonArray&>(temp.get(2));
    assert(dynamic_cast<JsonNumber&>(arr.get(0)).get_int() == 1);
}

void test_set_JsonNull_JsonArray() {
    JsonArray temp("[{asd},1,12.3,\"asd\", null]");
    JsonNull test;
    temp.set(0, test);
    assert(dynamic_cast<JsonNull&>(temp.get(0)).stringify() == "null");
}
/*
void test_set_JsonObject_JsonArray() {
    JsonArray temp("[{asd},1,12.3,\"asd\"]");
}*/

void test_push_back_JsonString_JsonArray() {
    JsonArray arr("[]");
    JsonString test("hello");
    arr.push_back(test);
    assert(dynamic_cast<JsonString&>(arr.get(0)).get_string() == "hello");
}

void test_push_back_JsonNumber_JsonArray() {
    JsonArray arr("[1, \"hello\"]");
    JsonNumber test(2);
    arr.push_back(test);
    assert(dynamic_cast<JsonNumber&>(arr.get(2)).get_int() == 2);
}

void test_push_back_JsonBoolean_JsonArray() {
    JsonArray arr("[1, \"hello\"]");
    JsonBoolean test(false);
    arr.push_back(test);
    assert(dynamic_cast<JsonBoolean&>(arr.get(2)).get_bool() == false);
}

void test_push_back_JsonArray_JsonArray() {
    JsonArray arr("[1, \"hello\"]");
    JsonArray test("[1, 2]");
    arr.push_back(test);
    JsonArray test2 = dynamic_cast<JsonArray&>(arr.get(2));
    assert(dynamic_cast<JsonNumber&>(test2.get(1)).get_int() == 2);
}

void test_push_back_JsonNull_JsonArray() {
    JsonArray arr("[1, \"hello\"]");
    JsonNull test;
    arr.push_back(test);
    assert(dynamic_cast<JsonNull&>(arr.get(2)).stringify() == "null");
}

/*void test_push_back_JsonObject_JsonArray() {

}*/
void test_insert_JsonString_JsonArray() {
    JsonArray arr("[1, \"hello\"]");
    JsonString test("hello");
    arr.insert(0, test);
    assert(dynamic_cast<JsonString&>(arr.get(0)).get_string() == "hello");
}

void test_insert_JsonNumber_JsonArray() {
    JsonArray arr;
    JsonNumber test(1.2);
    arr.insert(0, test);
    assert(dynamic_cast<JsonNumber&>(arr.get(0)).get_double() == 1.2);
}

void test_insert_JsonBoolean_JsonArray() {
    JsonArray arr("[1, 2, 3]");
    JsonBoolean test(true);
    arr.insert(3, test);
    assert(dynamic_cast<JsonBoolean&>(arr.get(3)).get_bool() == true);
}

void test_insert_JsonArray_JsonArray() {
    JsonArray arr("[]");
    JsonArray test("[1, 2, 3]");
    arr.insert(0, test);
    JsonArray arr2 = dynamic_cast<JsonArray&>(arr.get(0));
    assert(dynamic_cast<JsonNumber&>(arr2.get(2)).get_int() == 3);
}

void test_insert_JsonNull_JsonArray() {
    JsonArray arr("[1, 2, 3]");
    JsonNull test;
    arr.insert(1, test);
    assert(dynamic_cast<JsonNull&>(arr.get(1)).stringify() == "null");
}

//void test_insert_JsonObject_JsonArray() {}

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
        test_get_JsonString_JsonArray();
        test_get_JsonNumber_JsonArray();
        test_get_JsonBoolean_JsonArray();
        test_get_JsonArray_JsonArray();
        test_get_JsonNull_JsonArray();
        //test_get_JsonObject_JsonArray();
        test_set_JsonString_JsonArray();
        test_set_JsonNumber_JsonArray();
        test_set_JsonBoolean_JsonArray();
        test_set_JsonArray_JsonArray();
        test_set_JsonNull_JsonArray();
        //test_set_JsonObject_JsonArray();
        test_push_back_JsonString_JsonArray();
        test_push_back_JsonNumber_JsonArray();
        test_push_back_JsonBoolean_JsonArray();
        test_push_back_JsonArray_JsonArray();
        test_push_back_JsonNull_JsonArray();
        //test_push_back_JsonObject_JsonArray();
        test_insert_JsonString_JsonArray();
        test_insert_JsonNumber_JsonArray();
        test_insert_JsonBoolean_JsonArray();
        test_insert_JsonArray_JsonArray();
        test_insert_JsonNull_JsonArray();
        //test_insert_JsonObject_JsonArray();

        puts("Tests successfully completed.");
    }
    catch (const char* exception) {
        printf("Test failed with exception:\n%s\n", exception);
    }
    stop = clock();
    printf("Execution took %f seconds.\n", (((float)(stop - start))/CLOCKS_PER_SEC));
}
