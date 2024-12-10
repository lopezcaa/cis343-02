/**
 * Lab 5: GVZork
 * 
 * Item.h
 * 
 * By: Alonso Lopez
 * 12-10-2024
 */

#ifndef __H_ITEM__
#define __H_ITEM__

#include <string>
#include <iostream>

class Item {
    public:
        //constructor
        Item(std::string name, int calories, float weight, std::string description);

        //getters
        std::string getName() const; //returns the item name
        int getCalories() const; //returns the item calorie count
        float getWeight() const; //returns the weight of the item
        std::string getDescription() const; //returns the description of the item

        //overloading the stream operator for item
        friend std::ostream& operator<<(std::ostream& os, const Item& item);

    private:
        std::string name;
        int calories;
        float weight;
        std::string description;
};

#endif
