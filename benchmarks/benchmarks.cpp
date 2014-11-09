#include <cstdio>
#include <ctime>
#include <cstring>
#include <string>
#include <iostream>
#include <cassert>
#include <cerrno>

// json
#include "../json/json.hpp"
#include "../json/jsonstring.hpp"
#include "../json/jsonnumber.hpp"
#include "../json/jsonboolean.hpp"
#include "../json/jsonnull.hpp"
#include "../json/jsonarray.hpp"
#include "../json/jsonobject.hpp"

// SuperEasyJson
#include "SuperEasyJSON/json.h"

std::string get_file_contents(const char *filename)
{
    std::FILE *fp = std::fopen(filename, "rb");
    if (fp)
    {
        std::string contents;
        std::fseek(fp, 0, SEEK_END);
        contents.resize(std::ftell(fp));
        std::rewind(fp);
        std::fread(&contents[0], 1, contents.size(), fp);
        std::fclose(fp);
        return(contents);
    }
    throw(errno);
}

void test_json_parse(std::string& str) {
    JsonObject game_state(str); 
    puts("PLAYER ONE TANKS:\n");
    printf("%s\n", game_state.get_array("players").get_object(0).get_array("tanks").get_object(0).get_string("id").get_string().c_str());
    printf("%s\n", game_state.get_array("players").get_object(0).get_array("tanks").get_object(1).get_string("id").get_string().c_str());
    puts("PLAYER TWO TANKS:\n");
    printf("%s\n", game_state.get_array("players").get_object(1).get_array("tanks").get_object(0).get_string("id").get_string().c_str());
    printf("%s\n", game_state.get_array("players").get_object(1).get_array("tanks").get_object(1).get_string("id").get_string().c_str());
    puts("COMM_TYPE:\n");
    printf("%s\n", game_state.get_string("comm_type").get_string().c_str());
    puts("TIME REMAINING:\n");
    printf("%d\n", game_state.get_number("timeRemaining").get_int());
    puts("TIME STAMP:\n");
    printf("%f\n", game_state.get_number("timestamp").get_double());
}

void test_SuperEasyJSON_parse(std::string& str) {
    json::Value game_state = json::Deserialize(str);
    puts("PLAYER ONE TANKS:\n");
    printf("%s\n", (((((game_state["players"])[(size_t)0])["tanks"])[(size_t)0])["id"]).ToString().c_str());
    printf("%s\n", (((((game_state["players"])[(size_t)0])["tanks"])[(size_t)1])["id"]).ToString().c_str());
    puts("PLAYER TWO TANKS:\n");
    printf("%s\n", (((((game_state["players"])[(size_t)1])["tanks"])[(size_t)0])["id"]).ToString().c_str());
    printf("%s\n", (((((game_state["players"])[(size_t)1])["tanks"])[(size_t)1])["id"]).ToString().c_str());
}

int main() {
    clock_t start, stop;
    start = clock();
    try {
        std::string str = get_file_contents("testdata/gamestateTwo.json");
        test_json_parse(str);
        //test_SuperEasyJSON_parse(str);
        puts("Tests successfully completed.");
    }
    catch (const char* exception) {
        printf("Test failed with exception:\n%s\n", exception);
    }
    stop = clock();
    printf("Execution took %f seconds.\n", (((float)(stop - start))/CLOCKS_PER_SEC));
}
