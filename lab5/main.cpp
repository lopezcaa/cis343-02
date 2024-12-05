#include <iostream>
#include <string>

#include "Item.h"
#include "NPC.h"
#include "Location.h"
#include "Game.h"


int main(int argc, char** argv) {
    /**Item rn("Rusty Nail", 0, 1, "A rusty nail (I hope you've had a tetanus shot)");
    std::cout << rn << std::endl;

    std::cout << "Please give a description to the item: ";

    std::string holdDescription;
    std::cin >> holdDescription;

    std::cout << "You entered: " << holdDescription << std::endl;
    rn.setDescription(holdDescription);
    
    std::cout << rn << std::endl;
    **/

    /*std::vector<std::string> npc1Messages = {
        "Hello",
        "World"
    };*/

    /**
    NPC npc1("Robert", "A person", {"Hello", "World", "TESTING"});
    NPC npc2("Brandy", "A knight", {"Hello", "World", "TESTING"});

    std::cout << npc1 << std::endl;
    std::cout << "NPC1 desc: " << npc1.getDescription() << " | messageNUM: " << npc1.getMessageNum() << " | message: " << npc1.getCurrentMessage() << std::endl;
    std::cout << "NPC1 desc: " << npc1.getDescription() << " | messageNUM: " << npc1.getMessageNum() << " | message: " << npc1.getCurrentMessage() << std::endl;
    std::cout << "NPC1 desc: " << npc1.getDescription() << " | messageNUM: " << npc1.getMessageNum() << " | message: " << npc1.getCurrentMessage() << std::endl << std::endl;

    Location place("Pandnos Hall", "Lots of science labs are in this building.");
    Location forest("Forest", "Forest view outside mansion.");
    Location woods("Woods", "Woods outside mansion.");

    //place.addNPC(npc1);
    //place.addNPC(npc2);
    place.add_item(rn);

    place.add_location("north", &forest);
    place.set_visited(true);
    forest.add_location("south", &place);
    forest.add_location("west", &woods);

    std::cout << place << std::endl;
    std::cout << forest << std::endl;
    std::cout << place << std::endl;
    **/

    std::cout << "T1" << std::endl;
    Game game;
    std::cout << "T2" << std::endl;
    game.play();
    
    return 0;
}
