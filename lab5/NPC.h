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
        std::string getName() const;
        std::string getDescription() const;
        int getMessageNum() const;
        std::string getCurrentMessage();

        //overloading the stream operator to show NPC's name only
        friend std::ostream& operator<<(std::ostream& os, const NPC& npc);

        //overloading the == operator to compare two NPC objects
        bool operator==(const NPC& other) const;

    private:
        std::string name;
        int messageNum;
        std::vector<std::string> messages;
        std::string description;
};

#endif
