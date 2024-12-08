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
        std::string getName() const;
        std::string getDescription() const;
        std::map<std::string, Location*> get_locations() const;
        std::vector<NPC*> get_npcs() const;
        std::vector<Item*> get_items() const;
        bool get_visited();

        //setters
        void add_location(std::string direction, Location* location);
        void add_npc(NPC* npc);
        void add_item(Item* item);
        void set_visited(bool visited);

        void remove_item(Item* item);

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
