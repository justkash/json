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
    printf("comm_type = %s\n", game_state.get_string("comm_type").get_string().c_str());
    printf("timeRemaining = %d\n", game_state.get_number("timeRemaining").get_int());
    printf("timestamp = %f\n", game_state.get_number("timestamp").get_double());
    JsonObject map = game_state.get_object("map");
    printf("map.size.width = %d\n", map.get_array("size").get_number(0).get_int());
    printf("map.size.height = %d\n", map.get_array("size").get_number(1).get_int());
    JsonArray terrains = map.get_array("terrain");
    for (int i = 0; i < terrains.size(); ++i) {
        printf("map.terrain[%d].type = %s\n",i ,terrains.get_object(i).get_string("type").get_string().c_str());
        JsonObject bounding_box = terrains.get_object(i).get_object("boundingBox");
        JsonArray corner = bounding_box.get_array("corner");
        JsonArray size = bounding_box.get_array("size");
        printf("map.terrain[%d].boundingBox.corner.x = %d\n",i ,corner.get_number(0).get_int());
        printf("map.terrain[%d].boundingBox.corner.y = %d\n",i ,corner.get_number(1).get_int());
        printf("map.terrain[%d].boundingBox.size.width = %d\n",i ,size.get_number(0).get_int());
        printf("map.terrain[%d].boundingBox.size.height = %d\n",i ,size.get_number(1).get_int());
    }
    JsonArray players = game_state.get_array("players");
    for (int i = 0; i < players.size(); ++i) {
        printf("players[%d].score = %d\n", i, players.get_object(i).get_number("score").get_int());    
        printf("players[%d].name = %s\n", i, players.get_object(i).get_string("name").get_string().c_str());    
        JsonArray tanks = players.get_object(i).get_array("tanks");
        for (int j = 0; j < tanks.size(); ++j) {
            printf("players[%d].tanks[%d].id = %s\n", i, j, tanks.get_object(j).get_string("id").get_string().c_str());
            printf("players[%d].tanks[%d].health = %f\n", i, j, tanks.get_object(j).get_number("health").get_double());
            printf("players[%d].tanks[%d].hitRadius = %f\n", i, j, tanks.get_object(j).get_number("hitRadius").get_double());
            printf("players[%d].tanks[%d].collisionRadius = %f\n", i, j, tanks.get_object(j).get_number("collisionRadius").get_double());
            printf("players[%d].tanks[%d].type = %s\n", i, j, tanks.get_object(j).get_string("type").get_string().c_str());
            printf("players[%d].tanks[%d].alive = %s\n", i, j, tanks.get_object(j).get_boolean("alive").get_bool() == true? "true":"false");
            printf("players[%d].tanks[%d].position.x = %d\n", i, j, tanks.get_object(j).get_array("position").get_number(0).get_int());
            printf("players[%d].tanks[%d].position.y = %d\n", i, j, tanks.get_object(j).get_array("position").get_number(1).get_int());
            printf("players[%d].tanks[%d].tracks = %f\n", i, j, tanks.get_object(j).get_number("tracks").get_double());
            printf("players[%d].tanks[%d].turret = %f\n", i, j, tanks.get_object(j).get_number("turret").get_double());
            printf("players[%d].tanks[%d].speed = %d\n", i, j, tanks.get_object(j).get_number("speed").get_int());
            JsonArray projectiles = tanks.get_object(i).get_array("projectiles");
            for (int k = 0; k < projectiles.size(); ++k) {
                printf("players[%d].tanks[%d].projectiles[%d].id = %d\n", i, j, k, projectiles.get_object(k).get_number("id").get_int());
                printf("players[%d].tanks[%d].projectiles[%d].position.x = %d\n", i, j, k, projectiles.get_object(k).get_array("position").get_number(0).get_int());
                printf("players[%d].tanks[%d].projectiles[%d].position.y = %d\n", i, j, k, projectiles.get_object(k).get_array("position").get_number(1).get_int());
                printf("players[%d].tanks[%d].projectiles[%d].direction = %f\n", i, j, k, projectiles.get_object(k).get_number("dircetion").get_double());
                printf("players[%d].tanks[%d].projectiles[%d].speed = %d\n", i, j, k, projectiles.get_object(k).get_number("speed").get_int());
                printf("players[%d].tanks[%d].projectiles[%d].damage = %d\n", i, j, k, projectiles.get_object(k).get_number("damage").get_int());
            }
        }
    }
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
