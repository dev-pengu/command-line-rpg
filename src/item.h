#ifndef ITEM_H
#define ITEM_H
#include <string>

namespace rpg {

    class Item {
    private:
        std::string itemId;
        std::string name;
    public:
        Item(std::string, std::string);
        std::string getItemId();
        std::string getName();
    };

    Item::Item(std::string itemId, std::string name) {
        this->itemId = itemId;
        this->name = name;
    }

    std::string Item::getItemId() { return itemId; }

    std::string Item::getName() { return name; }

}

#endif