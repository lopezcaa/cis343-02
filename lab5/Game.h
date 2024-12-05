#ifndef __H_GAME__
#define __H_GAME__

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <cstdlib>

#include "Item.h"
#include "NPC.h"
#include "Location.h"

class Game {
    public:
        //constructor
        Game();

        //game loop
        void play();

        void setup_commands();

        void show_help(std::vector<std::string> target);
        void talk(std::vector<std::string> target);
        void meet(std::vector<std::string> target);
        void take(std::vector<std::string> target);
        void give(std::vector<std::string> target);
        void go(std::vector<std::string> target);
        void show_items(std::vector<std::string> target);
        void look(std::vector<std::string> target);
        void quit(std::vector<std::string> target);

    private:
        std::map<std::string, std::function<void(std::vector<std::string>)>> commands;
        std::vector<Item> player_items;
        int player_weight;
        std::vector<Location> locations;
        Location* player_location;
        int elf_calories;
        bool game_in_progress;

        void create_world();
        Location* random_location();

};

#endif
