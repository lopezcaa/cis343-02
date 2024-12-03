#ifndef NPC_H
#define NPC_H

#include <string>
#include <iostream>
#include <vector>

class NPC {
    public:
        //constructor
        NPC(std::string name, std::string description, std::vector<std::string> messages);

        //getters
        std::string getName();
        std::string getDescription();
        int getMessageNum();
        std::string getCurrentMessage();

        //setters
        void setName(std::string name);
        void setDescription(std::string description);
        void setMessageNum(int messageNum);
        void setCurrentMessage(std::string message);

        //overloading the stream operator to show NPC's name only
        friend std::ostream& operator<<(std::ostream& os, const NPC& npc) {
            os << npc.name;
            return os;
        }

    private:
        std::string name;
        int messageNum;
        std::vector<std::string> messages;
        std::string description;
};

#endif
