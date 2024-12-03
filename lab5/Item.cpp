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
std::string Item::getName() {
    return name;
}
std::string Item::getDescription() {
    return description;
}
int Item::getCalories() {
    return calories;
}
float Item::getWeight() {
    return weight;
}

//setters methods
void Item::setName(std::string name) {
    if(name.empty()) {
        throw std::invalid_argument("Name can't be blank.");
    }
    
    this->name = name;
}
void Item::setCalories(int calories) {
    if(calories < 0 || calories > 1000) {
        throw std::out_of_range("Calories must be between 0 and 1000.");
    }

    this->calories = calories;
}
void Item::setWeight(float weight) {
    if(weight < 0 || weight > 500) {
        throw std::out_of_range("Weight must be between 0 and 500");
    }

    this->weight = weight;
}
void Item::setDescription(std::string description) {
    if(description.empty()) {
        throw std::invalid_argument("Description can't be blank.");
    }

    this->description = description;
}

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.name << " (" << item.calories << " calories) - " << item.weight << " lb - " << item.description;
    
    return os;
}
