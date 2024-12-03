#include <stdexcept>

#include "Location.h"
#include "NPC.h"
#include "Item.h"

//constructor
Location::Location(std::string name, std::string description, bool visited, std::vector<NPC> NPCs, std::vector<Item> items) {
    this->name = name;
    this->description = description;
    this->visited = visited;
    this->NPCs = NPCs;
    this->items = items;
}

//getter methods
std::string Location::getName() {
    return name;
}
std::string Location::getDescription() {
    return description;
}
bool Location::getVisited() {
    return visited;
}
std::map<std::string, Location*> Location::getNeighbors() {
    return neighbors;
}
std::vector<NPC> Location::getNPCs() {
    return NPCs;
}
std::vector<Item> Location::getItems() {
    return items;
}

//setter methods
void Location::setVisited(bool visited) {
    this->visited = visited;
}

void Location::addLocation(std::string direction, Location* location) {
    if(direction.empty()) {
        throw std::invalid_argument("Direction can't be blank.");
    }
    else if(neighbors.find(direction) != neighbors.end()) {
        throw std::invalid_argument("This direction already exists.");
    }

    neighbors[direction] = location;
}
void Location::addNPC(NPC npc) {
    NPCs.push_back(npc);
}
void Location::addItem(Item item) {
    items.push_back(item);
}
