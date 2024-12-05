#include <stdexcept>

#include "Game.h"

//constructor
Game::Game() {
    this->player_weight = 0;
    this->elf_calories = 0;
    this->game_in_progress = true;

    create_world();
    setup_commands();
    player_location = &locations[0];
}

//game loop
void Game::play() {
    std::string userInput;
    bool validInput = false;

    std::cout << "--- GVZork ---" << std::endl;

    //Main loop
    while(game_in_progress) {
        look({});
        //std::cout << player_location->getName() << std::endl;
        //show_items({});
        //show_help({});
        quit({});
        //break;
    }
}

void Game::setup_commands() {
    commands["help"] = std::bind(&Game::show_help, this, std::placeholders::_1);
    commands["show help"] = std::bind(&Game::show_help, this, std::placeholders::_1);
    commands["talk"] = std::bind(&Game::talk, this, std::placeholders::_1);
    commands["give"] = std::bind(&Game::give, this, std::placeholders::_1);
    commands["take"] = std::bind(&Game::take, this, std::placeholders::_1);
    commands["go"] = std::bind(&Game::go, this, std::placeholders::_1);
    commands["look"] = std::bind(&Game::look, this, std::placeholders::_1);
    commands["quit"] = std::bind(&Game::quit, this, std::placeholders::_1);
    commands["items"] = std::bind(&Game::show_items, this, std::placeholders::_1);
    commands["meet"] = std::bind(&Game::meet, this, std::placeholders::_1);
}

void Game::show_help(std::vector<std::string> target) {
    std::cout << "Game Commands:" << std::endl;
    std::cout << "help - Shows this help message" << std::endl;
    std::cout << "talk <NPC name> - Talk to an NPC" << std::endl;
    std::cout << "give <item> - Give an item to the elf" << std::endl;
    std::cout << "take <item> - Take an item" << std::endl;
    std::cout << "go <direction> - Move to a new location" << std::endl;
    std::cout << "look - Look around the current location" << std::endl;
    std::cout << "quit - End the game" << std::endl;
    std::cout << "items - Show the items in your inventory" << std::endl << std::endl;
    
    // Print current time
    time_t now = time(0);
    char* dt = ctime(&now);
    std::cout << "Current time: " << dt << std::endl;
}

void Game::talk(std::vector<std::string> target) {
    if(target.empty()) {
        std::cout << "Please type the name of the person that you would like to talk to.";
    }

    std::string npcName = target[0];
    
    bool npcPresent = false;
    for(auto& npc : player_location->get_npcs()) {
        if(npc.getName() == npcName) {
            std::cout << npc.getCurrentMessage() << std::endl;
            npcPresent = true;
            break;
        }
    }

    if(!npcPresent) {
        std::cout << "[" << npcName << "] is not present here." << std::endl;
    }
}

void Game::meet(std::vector<std::string> target) {
    if(target.empty()) {
        std::cout << "Please type the name of the person that you would like to meet.";
    }

    std::string npcName = target[0];

    bool npcPresent = false;
    for(auto& npc : player_location->get_npcs()) {
        if(npc.getName() == npcName) {
            std::cout << npc.getDescription() << std::endl;
            npcPresent = true;
            break;
        }
    }

    if(!npcPresent) {
        std::cout << npcName << "is not here to meet." << std::endl;
    }
}

void Game::take(std::vector<std::string> target) {
    if(target.empty()) {
        std::cout << "Please type the name of the item that you want to take." << std::endl;
    }

    std::string itemName = target[0];

    Item* itemToTake = nullptr;
    for(auto& item : player_location->get_items()) {
        if(item.getName() == itemName) {
            itemToTake = &item;
            break;
        }
    }

    if(itemToTake == nullptr) {
        std::cout << "No item named [" << itemName << "] exists here." << std::endl;
        return;
    }

    player_items.push_back(*itemToTake);
    player_weight += itemToTake->getWeight();

    player_location->remove_item(*itemToTake);

    std::cout << "You have taken [" << itemName << "]." << std::endl;
    if(player_weight > 30.0) {
        std::cout << "You have gone over your max carrying weight limit!" << std::endl;
    }
}

void Game::give(std::vector<std::string> target) {
    if(target.empty()) {
        std::cout << "Please type the name of the item that you want to give." << std::endl;
    }

    // Check if the target item is in the player's inventory
    Item* itemToGive = nullptr;
    for(auto& item : player_items) {
        if(item.getName() == target[0]) {
            itemToGive = &item;
            break;
        }
    }

    // If item isn't found, print an error message
    if(!itemToGive) {
        std::cout << "You don't have that item to give." << std::endl;
        return;
    }

    // Remove item from the player's inventory and reduce their carried weight
    player_weight -= itemToGive->getWeight();
    player_items.erase(std::remove(player_items.begin(), player_items.end(), *itemToGive), player_items.end());
    
    // Add item to the current location's items list
    player_location->add_item(*itemToGive);

    // Check if the location is the woods and handle the item accordingly
    if(player_location->getName() == "Woods") {
        if(itemToGive->getCalories() > 0) {
            elf_calories -= itemToGive->getCalories();
            std::cout << "You gave the elf [" << itemToGive->getName() << "] (" << itemToGive->getCalories() << " calories)." << std::endl;
            if(elf_calories <= 0) {
                std::cout << "The elf has eaten enough calories. The campus has been saved!" << std::endl;
                game_in_progress = false;
            }
        } else {
            std::cout << "You gave the elf an inedible item! The elf didn't like that!" << std::endl;
            player_location = random_location();
            std::cout << "The elf has teleported you as punishment to a random location!" << std::endl;
        }
    } else {
        std::cout << "The elf is not at this location. You can't give the item to the elf here." << std::endl;
    }
}

void Game::go(std::vector<std::string> target) {
    if(target.empty()) {
        std::cout << "Please type the name of the location that you want to travel to." << std::endl;
    }

    if(player_weight > 30.0) {
        std::cout << "You have gone over your max carrying weight limit! You can't travel without dropping the weight first!" << std::endl;
        return;
    }

    std::string direction = target[0];
    
    auto neighbors = player_location->get_locations();

    if(neighbors.find(direction) != neighbors.end()) {
        //The direction exists, so move to new location
        Location* newLocation = neighbors[direction];

        // Mark the current location as visited
        player_location->set_visited(true);

        // Update the current location to the new location
        player_location = newLocation;
        std::cout << "You have moved to " << player_location->getName() << "." << std::endl;
    } else {
        // The direction doesn't exist in the neighbors map
        std::cout << "You can't go that way. There's no path in that direction." << std::endl;
    }
}

void Game::show_items(std::vector<std::string> target) {
    std::cout << "You're current carrying weight: " << player_weight << "lbs" << std::endl;

    if(player_items.empty()) {
        std::cout << "You have no items." << std::endl;
    } else {
        std::cout << "Your items:" << std::endl;
        for(auto& item : player_items) {
            std::cout << "\t- " << item << std::endl;
        }
    }
}

void Game::look(std::vector<std::string> target) {
    std::cout << "You're currently at [" << player_location->getName() << " (" << player_location->getDescription() << ")]" << std::endl << std::endl;

    if(player_location->get_items().empty()) {
        std::cout << "There are no items here." << std::endl;
    } else {
        std::cout << "You see the following items:" << std::endl;
        for(auto& item : player_location->get_items()) {
            std::cout << "\t- " <<  item << std::endl;
        }
    }

    if(player_location->get_npcs().empty()) {
        std::cout << "You are alone." << std::endl;
    } else {
        std::cout << "You see the following people:" << std::endl;
        for(auto& npc : player_location->get_npcs()) {
            std::cout << "\t- " << npc << std::endl;
        }
    }

    std::cout << "You can go in the following directions:" << std::endl;
    auto neighbors = player_location->get_locations();
    for(auto& neighbor : neighbors) {
        std::cout << "\t- " << neighbor.first << " - " << neighbor.second->getName();
        if(neighbor.second->get_visited()) {
            std::cout << " (Visited)";
        }
        std::cout << std::endl;
    }
}

void Game::quit(std::vector<std::string> target) {
    std::cout << std::endl << "Ending the game! Goodbye!" << std::endl;
    game_in_progress = false;
}

void Game::create_world() {
    //Creating the locations
    Location* padnos = new Location("Padnos Hall", "Lots of science labs are in this building");
    Location* mack = new Location("Mackinac Hall", "This building has multiple sections");
    Location* kirkhof = new Location("Kirkhof", "You can buy food in this building");
    Location* michigan = new Location("Lake Michigan Hall", "This building has lots of rooms");
    Location* library = new Location("Library", "This building stores lots of books");
    Location* ontario = new Location("Lake Ontario Hall", "There is a parking lot next to this building");
    Location* huron = new Location("Lake Huron Hall", "There are many rooms in this building");
    Location* woods = new Location("Woods", "This is where the elf lives");

    //Adding neighbors to locations
    mack->add_location("south", padnos);
    padnos->add_location("north", mack);
    padnos->add_location("south", kirkhof);
    padnos->add_location("east", library);
    kirkhof->add_location("north", padnos);
    kirkhof->add_location("south", michigan);
    kirkhof->add_location("east", huron);
    michigan->add_location("north", kirkhof);
    library->add_location("south", huron);
    library->add_location("west", padnos);
    huron->add_location("north", library);
    huron->add_location("south", ontario);
    huron->add_location("west", kirkhof);
    huron->add_location("east", woods);
    ontario->add_location("north", huron);
    woods->add_location("west", huron);

    //Creating the NPCs
    NPC* elf = new NPC("Elf", "This elf will save the campus once properly fed.", {"Hello traveler. I'm very hungry. Do you have food?", "Once I'm properly fed, I can help you out.", "The campus is in danger? I'm too hungry to help. Maybe I can help after I eat!"});
    NPC* npc1 = new NPC("Robert", "Robert likes to read books.", {"Hi! My name is Robert.", "Do you have a favorite book?"});
    NPC* npc2 = new NPC("Nick", "Nick likes to work with computers.", {"My name's Nick! I work with computers", "Is your computer broken? I can fix it!"});
    NPC* npc3 = new NPC("Cindy", "Cindy is studying reading a book.", {"Oh, hello! My name is Cindy.", "This book from my class is very interesting!"});
    NPC* npc4 = new NPC("Harry", "Harry is idling waiting for his next class", {"Nice to meet you! My name is Harry!", "Is something happening around campus? I'm bored waiting for class."});
    NPC* npc5 = new NPC("Sally", "Sally is buying food at Kirkhof", {"My name is Sally, nice to meet you!", "I can't wait to eat my food, I'm hungry!"});

    //Adding the NPCs to locations
    woods->add_npc(*elf);
    padnos->add_npc(*npc1);
    mack->add_npc(*npc2);
    library->add_npc(*npc3);
    huron->add_npc(*npc4);
    kirkhof->add_npc(*npc5);

    //Creating items
    Item* item01 = new Item("Rusty Nail", 0, 1, "A rusty nail (I hope you've had a tetanus shot)");
    Item* item02 = new Item("Apple", 50, 5, "A red apple");
    Item* item03 = new Item("Golden Apple", 150, 10, "A golden apple. It looks like it has lots of calories!");
    Item* item04 = new Item("Bag of rocks", 0, 5, "A bag of rocks");
    Item* item05 = new Item("Cookies", 65, 5, "Some regular cookies");
    Item* item06 = new Item("Taco", 80, 10, "A great-tasting taco");
    Item* item07 = new Item("Candy", 25, 1, "A small pile of candy");
    Item* item08 = new Item("Coal", 0, 15, "A lump of coal");
    Item* item09 = new Item("Bread", 100, 8, "A loaf of bread");
    Item* item10 = new Item("Orange", 80, 10, "A orange");

    ontario->add_item(*item01);
    kirkhof->add_item(*item02);
    ontario->add_item(*item03);
    michigan->add_item(*item04);
    library->add_item(*item05);
    mack->add_item(*item06);
    huron->add_item(*item07);
    padnos->add_item(*item08);
    padnos->add_item(*item09);
    kirkhof->add_item(*item10);

    locations.push_back(*padnos);
    locations.push_back(*mack);
    locations.push_back(*kirkhof);
    locations.push_back(*michigan);
    locations.push_back(*library);
    locations.push_back(*ontario);
    locations.push_back(*huron);
    locations.push_back(*woods);
}

Location* Game::random_location() {
    if (locations.empty()) {
        throw std::runtime_error("No locations available.");
    }

    int random_index = rand() % locations.size();
    return &locations[random_index];
}