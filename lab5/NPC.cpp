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
std::string NPC::getName() const {
    return name;
}

std::string NPC::getDescription() const {
    return description;
}

int NPC::getMessageNum() const {
    return messageNum;
}

std::string NPC::getCurrentMessage() {
    std::string currentMessage = messages[messageNum];
    messageNum = (messageNum + 1) % messages.size(); //% by the total message size prevent overflow
    return currentMessage;
}

std::ostream& operator<<(std::ostream& os, const NPC& npc) {
    os << npc.name;
    
    return os;
}
