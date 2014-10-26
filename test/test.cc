#include <stdio.h>
#include <time.h>
#include <string.h>
#include <string>
#include <iostream>
#include <assert.h>

#include "../json/json.h"
#include "../json/jsonstring.h"
#include "../json/jsonnumber.h"

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

        puts("Tests complete.");
    }
    catch (const char* exception) {
        printf("Test failed with exception:\n%s\n", exception);
    }
    stop = clock();
    printf("Execution took %f seconds.\n", (((float)(stop - start))/CLOCKS_PER_SEC));
}
