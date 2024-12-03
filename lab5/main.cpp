#include <iostream>
#include <string>

#include "Item.h"
#include "NPC.h"


int main(int argc, char** argv) {
    Item rn("Rusty Nail", 0, 1, "A rusty nail (I hope you've had a tetanus shot)");
    std::cout << rn << std::endl;

    std::cout << "Please give a description to the item: ";

    std::string holdDescription;
    std::cin >> holdDescription;

    std::cout << "You entered: " << holdDescription << std::endl;
    rn.setDescription(holdDescription);
    
    std::cout << rn << std::endl;

    std::vector<std::string> npc1Messages = {
        "Hello",
        "World"
    };
    NPC npc1("Robert", "A person", npc1Messages);

    std::cout << npc1 << std::endl;
    std::cout << "NPC1 desc: " << npc1.getDescription() << " | messageNUM: " << npc1.getMessageNum() << " | message: " << npc1.getCurrentMessage() << std::endl;
    std::cout << "NPC1 desc: " << npc1.getDescription() << " | messageNUM: " << npc1.getMessageNum() << " | message: " << npc1.getCurrentMessage() << std::endl;
    std::cout << "NPC1 desc: " << npc1.getDescription() << " | messageNUM: " << npc1.getMessageNum() << " | message: " << npc1.getCurrentMessage() << std::endl;
    
    return 0;
}
