#include <stdexcept>

#include "Item.h"

//constructor to initialize an item
Item::Item(std::string name, int calories, float weight, std::string description) {
    if(name.empty()) {
        throw std::invalid_argument("Name can't be blank.");
    }
    if(calories < 0 || calories > 1000) {
        throw std::out_of_range("Calories must be between 0 and 1000.");
    }
    if(weight < 0 || weight > 500) {
        throw std::out_of_range("Weight must be between 0 and 500");
    }
    if(description.empty()) {
        throw std::invalid_argument("Description can't be blank.");
    }

    this->name = name;
    this->calories = calories;
    this->weight = weight;
    this->description = description;
}

//getter methods
std::string Item::getName() const {
    return name;
}

int Item::getCalories() const {
    return calories;
}

float Item::getWeight() const {
    return weight;
}

std::string Item::getDescription() const {
    return description;
}

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.name << " (" << item.calories << " calories) - " << item.weight << " lb - " << item.description;
    
    return os;
}
