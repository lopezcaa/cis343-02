/**
 * Lab 5: GVZork
 * 
 * NPC.h
 * 
 * By: Alonso Lopez
 * 12-10-2024
 */

#ifndef __H_NPC__
#define __H_NPC__

#include <string>
#include <iostream>
#include <vector>

class NPC {
    public:
        //constructor
        NPC(std::string name, std::string description, std::vector<std::string> messages);

        //getters
        std::string getName() const; //returns NPC name
        std::string getDescription() const; //returns NPC description
        int getMessageNum() const; //returns NPC message index number
        std::string getCurrentMessage(); //returns NPC's current message

        //overloading the stream operator to show NPC's name only
        friend std::ostream& operator<<(std::ostream& os, const NPC& npc);

    private:
        std::string name;
        int messageNum;
        std::vector<std::string> messages;
        std::string description;
};

#endif
