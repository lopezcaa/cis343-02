#ifndef __H_LOCATION__
#define __H_LOCATION__

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "Item.h"
#include "NPC.h"

class Location {
    public:
        //constructor
        Location(std::string name, std::string description);

        //getters
        std::string getName();
        std::string getDescription();
        bool get_visited();
        std::map<std::string, Location*> get_locations();
        std::vector<NPC> get_npcs();
        std::vector<Item> get_items();

        //setters
        void setName(std::string name);
        void setDescription(std::string description);
        void set_visited(bool visited);
        void add_location(std::string direction, Location* location);
        void add_npc(NPC npc);
        void add_item(Item item);

        void remove_item(Item& item);

        //overloading the stream operator for location
        friend std::ostream& operator<<(std::ostream& os, const Location& location);

    private:
        std::string name;
        std::string description;
        bool visited;
        std::map<std::string, Location*> neighbors;
        std::vector<NPC> NPCs;
        std::vector<Item> items;
};

#endif
