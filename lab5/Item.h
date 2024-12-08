#ifndef __H_ITEM__
#define __H_ITEM__

#include <string>
#include <iostream>

class Item {
    public:
        //constructor
        Item(std::string name, int calories, float weight, std::string description);

        //getters
        std::string getName() const;
        int getCalories() const;
        float getWeight() const;
        std::string getDescription() const;

        //overloading the stream operator for item
        friend std::ostream& operator<<(std::ostream& os, const Item& item);

        //overloading the == operator to compare two Item objects
        bool operator==(const Item& other) const;

    private:
        std::string name;
        int calories;
        float weight;
        std::string description;
};

#endif
