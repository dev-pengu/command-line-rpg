#ifndef ITEM_H
#define ITEM_H
#include <string>
//#include "character.h"

namespace rpg {
    class Character;

    class Item {
    private:
        std::string itemId;
        std::string name;
    public:
        Item();
        Item(std::string, std::string);
        std::string getItemId();
        std::string getName();
        virtual void use(rpg::Character* character) {}
    };

    Item::Item(std::string itemId, std::string name) {
        this->itemId = itemId;
        this->name = name;
    }

    Item::Item() {
        this->itemId = "";
        this->name = "";
    }

    std::string Item::getItemId() { return itemId; }

    std::string Item::getName() { return name; }

    Item* nullItem = new Item("", "");

}

#endif