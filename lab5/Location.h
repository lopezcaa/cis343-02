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
        Location(std::string name, std::string description, bool visited); //bool visited, std::vector<NPC> NPCs, std::vector<Item> items);

        //getters
        std::string getName();
        std::string getDescription();
        bool getVisited();
        std::map<std::string, Location*> getNeighbors();
        std::vector<NPC> getNPCs();
        std::vector<Item> getItems();

        //setters
        void setVisited(bool visited);

        void addLocation(std::string direction, Location* location);
        void addNPC(NPC npc);
        void addItem(Item item);

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
