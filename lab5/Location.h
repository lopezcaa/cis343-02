/**
 * Location.h
 * By: Alonso Lopez
 */

#ifndef __H_LOCATION__
#define __H_LOCATION__

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "Item.h"
#include "NPC.h"

class Location {
    public:
        //constructor
        Location(std::string name, std::string description);

        //getters
        std::string getName() const; //returns location's name
        std::string getDescription() const; //returns location's description
        std::map<std::string, Location*> get_locations() const; //returns location's map of location pointers
        std::vector<NPC*> get_npcs() const; //returns location's vector of NPC pointers
        std::vector<Item*> get_items() const; //returns locations's vector of item pointers
        bool get_visited(); //returns the status of a location if the player visited or not

        //setters
        void add_location(std::string direction, Location* location); //sets a location pointer to the private location pointer map
        void add_npc(NPC* npc); //adds an NPC pointer to the private NPC pointer vector
        void add_item(Item* item); //adds an item pointer to the private item pointer vector
        void set_visited(bool visited); //changes the private visited bool

        void remove_item(Item* item); //removes an item pointer from the private item pointer vector

        //overloading the stream operator for location
        friend std::ostream& operator<<(std::ostream& os, const Location& location);

    private:
        std::string name;
        std::string description;
        bool visited;
        std::map<std::string, Location*> neighbors;
        std::vector<NPC*> NPCs;
        std::vector<Item*> items;
};

#endif
