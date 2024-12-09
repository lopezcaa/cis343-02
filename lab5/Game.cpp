/**
 * Lab 5: GVZork
 * 
 * Game.cpp
 * 
 * By: Alonso Lopez
 * 12-09-2024
 */

#include <stdexcept>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "Game.h"

//constructor
Game::Game() {
    this->player_weight = 0;
    this->elf_calories = 0;
    this->game_in_progress = true;

    create_world();
    setup_commands();
    player_location = random_location();
    player_location->set_visited(true); //Sets the starting location as visited
}

//game loop
void Game::play() {
    std::string userInput; //holds the user input

    std::cout << "--- GVZork ---" << std::endl << std::endl;

    show_help({});
    std::cout << "----------------------------" << std::endl << std::endl;

    //Main loop
    while(game_in_progress) {
        if(has_player_moved) {
            //print out the current location's info
            look({});
            has_player_moved = false;
        }

        //prompt the user for a command
        std::cout << "----------------------------" << std::endl <<\
            std::endl << "What would you like to do?:"\
            << std::endl << "=>";

        std::string input;
        std::getline(std::cin, input);  // Read the full line of input
        std::cout << std::endl;

        //split input into tokens (command and target)
        std::vector<std::string> tokens;
        std::istringstream stream(input);
        std::string token;
        while (stream >> token) {
            tokens.push_back(token);
        }

        if(tokens.empty()) continue;

        std::string command = tokens[0]; //the first word is the command

        //changes the command sting to all lowercase
        std::transform(command.begin(), command.end(), command.begin(),\
        [](unsigned char c) {return std::tolower(c);});

        tokens.erase(tokens.begin()); //the rest are parameters

        //executes the corresponding command
        if (commands.find(command) != commands.end()) {
            commands[command](tokens);  //call the command
        } else {
            std::cout << "Invalid command!"\
                " Type 'help' for a list of commands.\n";
        }
    }

    //runs quit() to free objects from memory an prints ending game message
    quit({});
    std::cout << "Ending the game! Goodbye!" << std::endl;
}

void Game::setup_commands() {
    commands["help"] = std::bind(&Game::show_help, this, std::placeholders::_1);
    commands["talk"] = std::bind(&Game::talk, this, std::placeholders::_1);
    commands["meet"] = std::bind(&Game::meet, this, std::placeholders::_1);
    commands["take"] = std::bind(&Game::take, this, std::placeholders::_1);
    commands["give"] = std::bind(&Game::give, this, std::placeholders::_1);
    commands["go"] = std::bind(&Game::go, this, std::placeholders::_1);
    commands["item"] = std::bind(&Game::show_items, this, std::placeholders::_1);
    commands["items"] = std::bind(&Game::show_items, this, std::placeholders::_1);
    commands["look"] = std::bind(&Game::look, this, std::placeholders::_1);
    commands["quit"] = std::bind(&Game::quit, this, std::placeholders::_1);

    //Setting up the extra commands I implemented apart from what the project called for
    commands["drop"] = std::bind(&Game::drop_item, this, std::placeholders::_1);
    commands["teleport"] = std::bind(&Game::teleport_magic, this, std::placeholders::_1);
}

void Game::show_help(std::vector<std::string> target) {
    std::cout << "Game Commands:" << std::endl;
    std::cout << "help - Shows this help message" << std::endl;
    std::cout << "talk <NPC name> - Talk to an NPC" << std::endl;
    std::cout << "meet <NPC name> - Show description of an NPC" << std::endl;
    std::cout << "take <item name> - Take an item" << std::endl;
    std::cout << "give <item name> - Give an item to the elf" << std::endl;
    std::cout << "go <North|South|East|West> - Move to a new location"\
        << std::endl;

    std::cout << "items - Show the items in your inventory" << std::endl;
    std::cout << "look - Look around the current location" << std::endl;
    std::cout << "quit - End the game" << std::endl << std::endl;

    std::cout << "Extra Commands:" << std::endl;
    std::cout << "drop <item> - Drop an item in the current location" << std::endl;
    std::cout << "teleport <full location name> - Teleport to any visited location"\
        << std::endl << std::endl;
    
    //logic for printing the current time
    time_t now = time(0);
    struct tm time_struct;
    char buf[80];

    //converting to local time
    time_struct = *localtime(&now);

    //formating the time
    strftime(buf, sizeof(buf), "Current time: %a %b %d %Y %H:%M:%S", &time_struct);

    // Output the formatted time
    std::cout << buf << std::endl;
}

//This method returns the current message of the target NPC
void Game::talk(std::vector<std::string> target) {
    //checks if target is empty
    if(target.empty()) {
        std::cout << "Please type the name of the person that you"\
            " would like to talk to." << std::endl;
        return;
    }

    //gets the full string from target and stores it in npcName
    std::string npcName;
    for (size_t i = 0; i < target.size(); ++i) {
        npcName += target[i];
        if (i < target.size() - 1) {
            npcName += " ";
        }
    }

    //changes npcName to be all lowercase
    std::transform(npcName.begin(), npcName.end(), npcName.begin(),\
        [](unsigned char c) {return std::tolower(c);});
    
    //this will loop through all present NPCs in the location and check for a match with target (npcName)
    bool npcPresent = false;
    for(auto& npc : player_location->get_npcs()) {
        //string for holding npc name to make it lowercase too
        std::string npcCompareName = npc->getName();

        //make the found NPC name lowercase too
        std::transform(npcCompareName.begin(), npcCompareName.end(),\
            npcCompareName.begin(),\
            [](unsigned char c) {return std::tolower(c);});

        if(npcCompareName == npcName) {
            std::cout << npc->getCurrentMessage() << std::endl;
            npcPresent = true;
            break;
        }
    }

    //prints a message if target NPC was not found
    if(!npcPresent) {
        std::cout << "[" << npcName << "] is not present here." << std::endl;
    }
}

//returns the descriptoin of the target NPC
void Game::meet(std::vector<std::string> target) {
    //checks if target is empty
    if(target.empty()) {
        std::cout << "Please type the name of the person that"\
            " you would like to meet.";
        return;
    }

    //stores the target vector into a single string
    std::string npcName;
    for (size_t i = 0; i < target.size(); ++i) {
        npcName += target[i];
        if (i < target.size() - 1) {
            npcName += " ";
        }
    }

    //makes the target string to lowercase
    std::transform(npcName.begin(), npcName.end(), npcName.begin(),\
        [](unsigned char c) {return std::tolower(c);});

    //loops through all present NPCs in the current location to check for a match with target
    bool npcPresent = false;
    for(auto& npc : player_location->get_npcs()) {
        //string to hold NPC name
        std::string npcCompareName = npc->getName();

        //make the NPC name lowercase
        std::transform(npcCompareName.begin(), npcCompareName.end(),\
            npcCompareName.begin(),\
            [](unsigned char c) {return std::tolower(c);});

        if(npcCompareName == npcName) {
            std::cout << npc->getDescription() << std::endl;
            npcPresent = true;
            break;
        }
    }

    //prints if the target NPC is not present to meet
    if(!npcPresent) {
        std::cout << npcName << " is not here to meet." << std::endl;
    }
}

//adds an item object pointer to the player's inventory and removes it from the current location
void Game::take(std::vector<std::string> target) {
    //checks if target is empty
    if(target.empty()) {
        std::cout << "Please type the name of the item"\
            " that you want to take." << std::endl;
        return;
    }

    //converts the target vector to a string
    std::string itemName;
    for (size_t i = 0; i < target.size(); ++i) {
        itemName += target[i];
        if (i < target.size() - 1) {
            itemName += " ";
        }
    }
    
    //makes the target string to all lowercase
    std::transform(itemName.begin(), itemName.end(), itemName.begin(),\
        [](unsigned char c) {return std::tolower(c);});

    //loops through all items in current location and checks for a match
    Item* itemToTake = nullptr;
    std::string holdCapitalizedName; //this is meant to hold the item name before making it all lowercase to use later
    for(auto& item : player_location->get_items()) {
        holdCapitalizedName = item->getName();
        std::string itemCompareName = item->getName();
        std::transform(itemCompareName.begin(), itemCompareName.end(),\
            itemCompareName.begin(),\
            [](unsigned char c) {return std::tolower(c);});

        if(itemCompareName == itemName) {
            itemToTake = item;
            break;
        }
    }

    //prints if no item was found under the target name, then exits the method
    if(itemToTake == nullptr) {
        std::cout << "No item named [" << itemName\
            << "] exists here." << std::endl;
        return;
    }

    //adds the item pointer to the player inventory vector and weight to player weight
    player_items.push_back(itemToTake);
    player_weight += itemToTake->getWeight();

    //removes the found item pointer from the current location
    player_location->remove_item(itemToTake);

    //prints info about the current take action
    std::cout << "You have taken [" << holdCapitalizedName\
        << "]." << std::endl;
    if(player_weight > 30.0) {
        std::cout << "You have gone over your max carrying"\
            " weight limit!" << std::endl;
    }
}

//gives items to the elf if player is in the woods
void Game::give(std::vector<std::string> target) {
    //checks if the target is empty
    if(target.empty()) {
        std::cout << "Please type the name of the item"\
            " that you want to give." << std::endl;
        return;
    }

    //convert the target vector to a string
    std::string itemName;
    for (size_t i = 0; i < target.size(); ++i) {
        itemName += target[i];
        if (i < target.size() - 1) {
            itemName += " ";
        }
    }

    //change the target string to lowercase
    std::transform(itemName.begin(), itemName.end(), itemName.begin(),\
        [](unsigned char c) {return std::tolower(c);});

    //check if the target item is in the player's inventory
    Item* itemToGive = nullptr;
    for(auto& item : player_items) {
        std::string itemCompareName = item->getName();

        //makes itemCompareName lowercase
        std::transform(itemCompareName.begin(), itemCompareName.end(),\
            itemCompareName.begin(),\
            [](unsigned char c) {return std::tolower(c);});

        if(itemCompareName == itemName) {
            itemToGive = item;
            break;
        }
    }

    //if item isn't found, print an error message and return
    if(!itemToGive) {
        std::cout << "You don't have that item to give." << std::endl;
        return;
    }

    //remove item from the player's inventory and reduce the player's carried weight
    player_weight -= itemToGive->getWeight();
    player_items.erase(std::remove(player_items.begin(),\
        player_items.end(), itemToGive), player_items.end());

    // Check if the location is the woods and handle the item accordingly
    if(player_location->getName() == "Woods") {
        if(itemToGive->getCalories() > 0) {
            elf_calories += itemToGive->getCalories();
            std::cout << "You gave the elf ["\
                << itemToGive->getName() << "] ("\
                << itemToGive->getCalories() << " calories)."\
                << std::endl;

            std::cout << "The elf ate the " << itemToGive->getName()\
                << "." << std::endl << std::endl;

            std::cout << "Total calories eaten by the elf: "\
                << elf_calories << "/300 calories" << std::endl;

            if(elf_calories >= 300) {
                std::cout << "The elf has eaten enough calories."\
                    " The campus has been saved!" << std::endl << std::endl;

                game_in_progress = false;
            }
        } else {
            //This else statement will happen when the elf is given an inedible item
            std::cout << "You gave the elf [" << itemToGive->getName()\
                << "] (" << itemToGive->getCalories() << " calories)."\
                    << std::endl << std::endl;

            std::cout << "You gave the elf an inedible item!"\
                " The elf didn't like that!" << std::endl;

            player_location = random_location();

            std::cout << "The elf has teleported you"\
                " as punishment to a random location!"\
                << std::endl << "-------------" << std::endl << std::endl;

            look({});
        }
        
        delete itemToGive; //free up the pointer of the used item object
        itemToGive = nullptr; //sets the free'd up pointer to point to null afterwards
    } else {
        std::cout << "The elf is not at this location."\
            " You can't give the item to the elf here." << std::endl;
    }
}

//moves the player's current location pointer to the target
void Game::go(std::vector<std::string> target) {
    //checks if target is empty
    if(target.empty()) {
        std::cout << "Please type the name of the"\
            " location that you want to travel to." << std::endl;

        return;
    }

    //checks if the player weight is over 30 lbs.
    //if so, exits the method
    if(player_weight > 30.0) {
        std::cout << "You have gone over your"\
            " max carrying weight limit!" << std::endl;

        std::cout << "You can't travel without"\
            " dropping the weight first!" << std::endl;

        return;
    }

    //converts the target vector to a string
    std::string direction;
    for (size_t i = 0; i < target.size(); ++i) {
        direction += target[i];
        if (i < target.size() - 1) {
            direction += " ";
        }
    }

    //converts the target string to a lowercase string
    std::transform(direction.begin(), direction.end(),\
        direction.begin(), [](unsigned char c)\
        {return std::tolower(c);});

    //loops through all neighboring location pointers and checks for a match with the target string
    auto neighbors = player_location->get_locations();
    bool direction_found = false;
    for(auto& neighbor : neighbors) {
        std::string neighbor_direction_lower = neighbor.first;

        std::transform(neighbor_direction_lower.begin(),\
            neighbor_direction_lower.end(),\
            neighbor_direction_lower.begin(),\
            [](unsigned char c) {return std::tolower(c);});

        //if a match is found, set the player's current location to the target location
        if(neighbor_direction_lower == direction) {
            player_location = neighbor.second;
            player_location->set_visited(true);
            direction_found = true;

            std::cout << "You have moved to ["\
                << player_location->getName() << "]."\
                << std::endl << std::endl;
            has_player_moved = true; //This will set the game loop to repeat the location data output on the game text interface
            break;
        }
    }

    //prints a message if no valid direction was found
    if (!direction_found) {
        std::cout << "You can't go that way." << std::endl;
        std::cout << "There's no path in that direction." << std::endl;
    }
}

//prints the items and weight that the player currently holds with pointers
void Game::show_items(std::vector<std::string> target) {
    std::cout << "Your current carrying weight: "\
        << player_weight << " lbs" << std::endl;

    if(player_items.empty()) {
        std::cout << "You have no items." << std::endl;
    } else {
        std::cout << "Your items:" << std::endl;
        for(auto& item : player_items) {
            std::cout << "\t- " << *item << std::endl;
        }
    }
}

//prints the current player location's info
void Game::look(std::vector<std::string> target) {
    std::cout << *player_location;
}

//changes game running bool to false and frees objects from memory
void Game::quit(std::vector<std::string> target) {
    game_in_progress = false;

    //loops through all locations to loop through all items and NPCs to free their memory
    for(auto& location : game_locations) {
        for(auto& item : location->get_items()) {
            delete item;
        }

        for(auto& npc : location->get_npcs()) {
            delete npc;
        }

        delete location;
    }
    game_locations.clear();

    //loops through all player items to free them up from memory
    for(auto& player_item : player_items) {
        delete player_item;
    }
    player_items.clear();
}

//sets up all the location, NPCs, and item objects to be used in the game
void Game::create_world() {
    //Creating the locations
    Location* padnos = new Location("Padnos Hall",\
        "Lots of science labs are in this building");

    Location* mack = new Location("Mackinac Hall",\
        "This building has multiple sections");

    Location* kirkhof = new Location("Kirkhof",\
        "You can buy food in this building");

    Location* michigan = new Location("Lake Michigan Hall",\
        "This building has lots of rooms");

    Location* library = new Location("Library",\
        "This building stores lots of books");

    Location* ontario = new Location("Lake Ontario Hall",\
        "There is a parking lot next to this building");

    Location* huron = new Location("Lake Huron Hall",\
        "There are many rooms in this building");

    Location* woods = new Location("Woods",\
        "This is where the elf lives");

    //Adding neighbors to locations
    mack->add_location("South", padnos);
    padnos->add_location("North", mack);
    padnos->add_location("South", kirkhof);
    padnos->add_location("East", library);
    kirkhof->add_location("North", padnos);
    kirkhof->add_location("South", michigan);
    kirkhof->add_location("East", huron);
    michigan->add_location("North", kirkhof);
    library->add_location("South", huron);
    library->add_location("West", padnos);
    huron->add_location("North", library);
    huron->add_location("South", ontario);
    huron->add_location("West", kirkhof);
    huron->add_location("East", woods);
    ontario->add_location("North", huron);
    woods->add_location("West", huron);

    //Creating the NPCs
    NPC* elf = new NPC("Elf",\
        "This elf will save the campus once properly fed.",\
        {"Hello traveler. I'm very hungry. Do you have food?",\
        "Once I'm properly fed, I can help you out.",\
        "The campus is in danger? I'm too hungry to help."\
        " Maybe I can help after I eat!"});

    NPC* npc1 = new NPC("Robert",\
        "Robert likes to read books.",\
        {"Hi! My name is Robert.",\
        "Do you have a favorite book?"});

    NPC* npc2 = new NPC("Nick",\
        "Nick likes to work with computers.",\
        {"My name's Nick! I work with computers",\
        "Is your computer broken? I can fix it!"});

    NPC* npc3 = new NPC("Cindy",\
        "Cindy is studying reading a book.",\
        {"Oh, hello! My name is Cindy.",\
        "This book from my class is very interesting!"});

    NPC* npc4 = new NPC("Harry",\
        "Harry is idling waiting for his next class",\
        {"Nice to meet you! My name is Harry!",\
        "Is something happening around campus?"\
        " I'm bored waiting for class.",\
        "There's a rumour going around that a"\
        " Golden Apple can be found south of"\
        " here.\nIt must be tasty!"});

    NPC* npc5 = new NPC("Sally",\
        "Sally is buying food at Kirkhof",\
        {"My name is Sally, nice to meet you!",\
        "I can't wait to eat my food, I'm hungry!",\
        "I hear that the woods is to the west of here."});

    //Adding the NPCs to locations
    woods->add_npc(elf);
    padnos->add_npc(npc1);
    mack->add_npc(npc2);
    library->add_npc(npc3);
    huron->add_npc(npc4);
    kirkhof->add_npc(npc5);

    //Creating items
    Item* item01 = new Item("Rusty Nail", 0, 1,\
        "A rusty nail (I hope you've had a tetanus shot)");
    
    Item* item02 = new Item("Apple", 50, 10, "A red apple");

    Item* item03 = new Item("Golden Apple", 150, 15,\
        "A golden apple. It looks like it has lots of calories!");

    Item* item04 = new Item("Bag of Rocks", 0, 10, "A bag of rocks");
    Item* item05 = new Item("Cookies", 65, 10, "Some regular cookies");
    Item* item06 = new Item("Taco", 80, 15, "A great-tasting taco");
    Item* item07 = new Item("Candy", 25, 5, "A small pile of candy");
    Item* item08 = new Item("Coal", 0, 20, "A lump of coal");
    Item* item09 = new Item("Bread", 100, 10, "A loaf of bread");
    Item* item10 = new Item("Orange", 80, 15, "An orange");
    Item* item11 = new Item("Rotten Apple", 0, 10, "A rotten apple");

    ontario->add_item(item01);
    kirkhof->add_item(item02);
    ontario->add_item(item03);
    michigan->add_item(item04);
    library->add_item(item05);
    mack->add_item(item06);
    huron->add_item(item07);
    padnos->add_item(item08);
    padnos->add_item(item09);
    kirkhof->add_item(item10);
    mack->add_item(item11);

    //adds the location pointers to the game location vector
    game_locations.push_back(padnos);
    game_locations.push_back(mack);
    game_locations.push_back(kirkhof);
    game_locations.push_back(michigan);
    game_locations.push_back(library);
    game_locations.push_back(ontario);
    game_locations.push_back(huron);
    game_locations.push_back(woods);
}

//returns a random location pointer
Location* Game::random_location() {
    if (game_locations.empty()) {
        throw std::runtime_error("No locations available.");
    }

    srand(time(0));
    int random_index = rand() % game_locations.size();

    return game_locations[random_index];
}

//removes an item pointer from the player inventory and adds it to the current location object
void Game::drop_item(std::vector<std::string> target) {
    //checks if the target is empty
    if(target.empty()) {
        std::cout << "Please type the name of the item"\
            " that you want to drop." << std::endl;

        return;
    }

    //converts the target vector to a string
    std::string itemName;
    for (size_t i = 0; i < target.size(); ++i) {
        itemName += target[i];
        if (i < target.size() - 1) {
            itemName += " ";
        }
    }
    
    //converts the target string to all lowercase
    std::transform(itemName.begin(), itemName.end(),\
        itemName.begin(),\
        [](unsigned char c) {return std::tolower(c);});

    //loopts thorugh all player items and compares with target string
    Item* itemToDrop = nullptr;
    std::string holdCapitalizedName; //Used to hold un-lowercased string to use later
    for(auto& item : player_items) {
        holdCapitalizedName = item->getName();
        std::string itemCompareName = item->getName();

        //lowercase itemCompareName
        std::transform(itemCompareName.begin(),\
            itemCompareName.end(), itemCompareName.begin(),\
            [](unsigned char c) {return std::tolower(c);});

        if(itemCompareName == itemName) {
            itemToDrop = item;
            break;
        }
    }

    //if no item was found in player inventory, this prints and exits the method
    if(itemToDrop == nullptr) {
        std::cout << "No item named [" << itemName\
            << "] exists here." << std::endl;

        return;
    }

    //logic to find and remove the item from player's inventory
    auto it = std::find(player_items.begin(),\
        player_items.end(), itemToDrop);

    if(it != player_items.end()) {
        player_items.erase(it);
        player_weight -= itemToDrop->getWeight();
    }

    //adds the item pointer to the current location's item vector
    player_location->add_item(itemToDrop);

    //prints out info over the droped item
    std::cout << "You have dropped ["\
        << holdCapitalizedName << "]." << std::endl;

    std::cout << "Your current carrying weight: "\
        << player_weight << " lbs" << std::endl;
}

//sets the player location to target location if it was previously visited
void Game::teleport_magic(std::vector<std::string> target) {
    //checks if target is empty
    if(target.empty()) {
        std::cout << "Please type the full name of the"\
            " location you want to teleport to." << std::endl;

        return;
    }
    //checks if the player weight is over 30 lbs.
    //if so, exits the method
    else if(player_weight > 30.0) {
        std::cout << "You have gone over your"\
            " max carrying weight limit!" << std::endl;

        std::cout << "You can't teleport without"\
            " dropping the weight first!" << std::endl;

        return;
    }

    //converts target vector to string
    std::string targetName;
    for (size_t i = 0; i < target.size(); ++i) {
        targetName += target[i];
        if (i < target.size() - 1) {
            targetName += " ";
        }
    }
    
    //converts target string to lowercase
    std::transform(targetName.begin(), targetName.end(),\
        targetName.begin(), [](unsigned char c)\
        {return std::tolower(c);});

    //loops through vector of location pointers to check for a match with target
    for(auto& location : game_locations) {
        std::string lowerCaseLocationName = location->getName();

        //makes loop target lowercase
        std::transform(lowerCaseLocationName.begin(),\
            lowerCaseLocationName.end(), lowerCaseLocationName.begin(),\
            [](unsigned char c) {return std::tolower(c);});

        //if a match is made with a visited location, set player location to target
        if(lowerCaseLocationName == targetName\
            && location->get_visited() == true) {

            player_location = location;
            has_player_moved = true;

            std::cout << "You have successfully used"\
                " teleportation magic!" << std::endl;

            std::cout << "You have teleported to ["\
                << player_location->getName() << "]." << std::endl << std::endl;

            break;
        }
    }

    //if player couldn't move, prints a message for failed teleportation
    if(!has_player_moved) {

        std::cout << "You have failed at using"\
            " teleportation magic." << std::endl;

        std::cout << "You can only teleport to"\
            " locations you previously visited."\
            << std::endl << std::endl;
    }
}
