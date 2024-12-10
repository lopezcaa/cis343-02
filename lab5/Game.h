/**
 * Lab 5: GVZork
 * 
 * Game.h
 * 
 * By: Alonso Lopez
 * 12-10-2024
 */

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

        void setup_commands(); //sets up the commands that the player can use to call methods
        void show_help(std::vector<std::string> target); //prints out the list of commands that the player can use
        void talk(std::vector<std::string> target); //the selected NPC target will print out their current message
        void meet(std::vector<std::string> target); //the selected NPC taret will print out their description
        void take(std::vector<std::string> target); //removes the item from current location and adds it to player's inventory
        void give(std::vector<std::string> target); //removes the item from player's inventory and gives it to the elf
        void go(std::vector<std::string> target); //moves the player to the target location
        void show_items(std::vector<std::string> target); //prints out the player's current weight and items in inventory
        void look(std::vector<std::string> target); //prints out the current location name, NPCs, items, and neighboring locations
        void quit(std::vector<std::string> target); //sets the game loop to stop running (false) and deletes (frees up) allocated memory objects

        void create_world(); //creates the item, NPC, and location objects and sets the game up
        Location* random_location(); //will return a randomly selected location object pointer

        void drop_item(std::vector<std::string> target); //removes item from player's inventory and adds it to the current location object.
        void teleport_magic(std::vector<std::string> target); //changes the player's current location to the target location if the target location has been previously visited

    private:
        std::map<std::string, std::function<void(std::vector<std::string>)>> commands;
        std::vector<Item*> player_items;
        float player_weight;
        std::vector<Location*> game_locations;
        Location* player_location;
        int elf_calories;
        bool game_in_progress;

        bool has_player_moved = true; // bool to declare a location has been moved to. Used in Game.cpp to only run look() when movement is used.

};

#endif
