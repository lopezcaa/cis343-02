/**
 * Lab 5: GVZork
 * 
 * NPC.cpp
 * 
 * By: Alonso Lopez
 * 12-10-2024
 */

#include <stdexcept>

#include "NPC.h"

//constructor to initialize an NPC
NPC::NPC(std::string name, std::string description, std::vector<std::string> messages) {
    if(name.empty()) {
        throw std::invalid_argument("Name can't be blank.");
    }
    if(description.empty()) {
        throw std::invalid_argument("Description can't be blank.");
    }

    this->name = name;
    this->description = description;
    messageNum = 0;
    this->messages = messages;
}

//getter methods

//returns NPC name
std::string NPC::getName() const {
    return name;
}

//returns NPC description
std::string NPC::getDescription() const {
    return description;
}

//returns NPC message number index
int NPC::getMessageNum() const {
    return messageNum;
}

//returns the NPC's current message
std::string NPC::getCurrentMessage() {
    std::string currentMessage = messages[messageNum];
    messageNum = (messageNum + 1) % messages.size(); //% by the total message size prevent overflow
    return currentMessage;
}

//overloads the stream operator for NPC to return the name only
std::ostream& operator<<(std::ostream& os, const NPC& npc) {
    os << npc.name;
    
    return os;
}
