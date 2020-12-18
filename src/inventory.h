#ifndef INVENTORY_H
#define INVENTORY_H
#include <unordered_map>
#include <iostream>
#include <iterator>
#include <string>
#include "item.h"


// change to use a vector of InventorySlots
namespace rpg
{
    typedef std::unordered_map<Item, int> ItemMap;

    class Inventory {
    private:
        ItemMap items;
    public:
        void print() const;
        Inventory();
        Inventory(const Inventory&);
        void addItem(Item, int);
        bool removeItem(Item, int);
        Item& getItem(std::string);
    };

    void Inventory::print() const {
        for (auto item : items) {
            std::cout << item.first.getName() << " - " << item.second << std::endl;
        }
    }

    Inventory::Inventory(const Inventory& otherInventory) {
        items.clear();
        for (auto item : otherInventory) {
            items.emplace(item.first, item.second);
        }
    }

    void Inventory::addItem(Item newItem, int count) {
        for (auto item : items) {
            if (item.first.getItemId() == newItem.getItemId()) {
                items[item.first] += count;
                return;
            }
        }
        items.emplace(newItem, count);
    }

    bool Inventory::removeItem(Item deleteItem, int count) {
        for (auto item : items) {
            if (item.first.getItemId() == deleteItem.getItemId()) {
                if (items[item.first] < count)
                    return false;
                else if (items[item.first] == count) {
                    items.erase(item.first);
                    return true;
                } else {
                    items[item.first] -= count;
                    return true;
                }
            }
        }

        return false;
    }

    Item& getItem(std::string itemId) {
        for (auto item : items) {
            if (item.first.getItemId() == itemId) {
                return item.first;
            }
        }
        return nullptr;
    }
}

#endif