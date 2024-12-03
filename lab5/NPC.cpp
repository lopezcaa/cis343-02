#include "NPC.h"
#include <stdexcept>


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
std::string NPC::getName() {
    return name;
}
std::string NPC::getDescription() {
    return description;
}
int NPC::getMessageNum() {
    return messageNum;
}
std::string NPC::getCurrentMessage() {
    std::string currentMessage = messages[messageNum];
    messageNum = (messageNum + 1) % messages.size(); //% by the total message size prevent overflow
    return currentMessage;
}

//setter methods
void NPC::setName(std::string name) {
    this->name = name;
}
void NPC::setDescription(std::string description) {
    this->description = description;
}
void NPC::setMessageNum(int messageNum) {
    this->messageNum = messageNum;
}
void NPC::setCurrentMessage(std::string message) {
    this->messages[messageNum] = message;
}
