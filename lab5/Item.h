#ifndef __H_ITEM__
#define __H_ITEM__

#include <string>
#include <iostream>

class Item {
    public:
        //constructor
        Item(std::string name, int calories, float weight, std::string description);

        //getters
        std::string getName();
        int getCalories();
        float getWeight();
        std::string getDescription();

        //setters
        void setName(std::string name);
        void setCalories(int calories);
        void setWeight(float weight);
        void setDescription(std::string description);

        //overloading the stream operator for item
        friend std::ostream& operator<<(std::ostream& os, const Item& item);

    private:
        std::string name;
        int calories;
        float weight;
        std::string description;
};

#endif
