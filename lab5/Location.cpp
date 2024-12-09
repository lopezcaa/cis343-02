/**
 * Lab 5: GVZork
 * 
 * Location.cpp
 * 
 * By: Alonso Lopez
 * 12-09-2024
 */

#include <stdexcept>

#include "Location.h"

//constructor
Location::Location(std::string name, std::string description) {
    this->name = name;
    this->description = description;
    this->visited = false;
}

//getter methods

//returns location's name
std::string Location::getName() const {
    return name;
}

//returns location's description
std::string Location::getDescription() const {
    return description;
}

//returns location map of neighboring locations
std::map<std::string, Location*> Location::get_locations() const {
    return neighbors;
}

//returns vector of NPC pointers
std::vector<NPC*> Location::get_npcs() const {
    return NPCs;
}

//returns vector of item pointers
std::vector<Item*> Location::get_items() const {
    return items;
}

//returns bool if location was visited or not
bool Location::get_visited() {
    return visited;
}

//setter methods

//adds a location pointer to the neighboring location map
void Location::add_location(std::string direction, Location* location) {
    if(direction.empty()) {
        throw std::invalid_argument("Direction can't be blank.");
    }
    else if(neighbors.find(direction) != neighbors.end()) {
        throw std::invalid_argument("This direction already exists.");
    }

    neighbors[direction] = location;
}

//adds a NPC pointer to the vector of NPC pointers
void Location::add_npc(NPC* npc) {
    NPCs.push_back(npc);
}

//adds an item pointer to the vctor of item pointers
void Location::add_item(Item* item) {
    items.push_back(item);
}

//sets the value of the visited bool for the location
void Location::set_visited(bool visited) {
    this->visited = visited;
}

//removes an item from the vector of item pointers
void Location::remove_item(Item* item) {
    // Find the item in the vector using std::find
    auto it = std::find(items.begin(), items.end(), item);

    // If the item is found, erase it from the vector
    if (it != items.end()) {
        items.erase(it);  // Removes the item from the vector
    }
}

//overloading the stream operator for location
std::ostream& operator<<(std::ostream& os, const Location& location) {
    os << location.name << " - " << location.description << std::endl << std::endl;
    
    if(!location.NPCs.empty()) {
        os << "You see the following NPCs:" << std::endl;
        for(auto& npc : location.NPCs) {
            os << "\t- " << *npc << std::endl;
        }
    } else {
        os << "There are no NPCs here." << std::endl;
    }

    if(!location.items.empty()) {
        os << std::endl << "You see the following Items:" << std::endl;
        for(auto& item : location.items) {
            os << "\t- " << *item << std::endl;
        }
    } else {
        os << std::endl << "There are no items here." << std::endl;
    }

    os << std::endl << "You can go in the following Directions:" << std::endl;
    for(auto& neighbor : location.neighbors) {
        if(neighbor.second->get_visited()) {
            os << "\t- " << neighbor.first << " - " << neighbor.second->getName() << " (Visited)";
        } else {
            os << "\t- " << neighbor.first << " - Unknown";
        }
        os << std::endl;
    }

    return os;
}
