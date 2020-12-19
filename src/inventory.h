#ifndef INVENTORY_H
#define INVENTORY_H
#include <unordered_map>
#include <vector>
#include <iostream>
#include <iterator>
#include <string>
#include "item.h"
#include "inventory_slot.h"
//#include "character.h"


// change to use a vector of InventorySlots
namespace rpg
{
    class Character;
    typedef std::vector<InventorySlot*> SlotVector;

    class Inventory {
    private:
        SlotVector items;
    public:
        void print() const;
        Inventory() {}
        Inventory(const Inventory&);
        void addItem(Item, int);
        bool removeItem(Item, int, rpg::Character*);
        Item& getItem(std::string);
    };

    void Inventory::print() const {
        for (int i = 0; i < items.size(); i++) {
            std::cout << (items[i])->item.getName() << " - " << (items[i])->count << std::endl;
        }
    }

    Inventory::Inventory(const Inventory& otherInventory) {
        items.clear();
        for (int i = 0; i < otherInventory.items.size(); i++) {
            InventorySlot* newInventorySlot = new InventorySlot;
            newInventorySlot->item = otherInventory.items[i]->item;
            newInventorySlot->count = otherInventory.items[i]->count;
            this->items.push_back(newInventorySlot);
        }
    }

    void Inventory::addItem(Item newItem, int count) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i]->item.getItemId() == newItem.getItemId()) {
                items[i]->add(count);
                return;
            }
        }
        InventorySlot* newInventorySlot = new InventorySlot;
        newInventorySlot->item = newItem;
        newInventorySlot->count = count;
        this->items.push_back(newInventorySlot);
    }

    bool Inventory::removeItem(Item deleteItem, int count, rpg::Character* character) {
        for (int i = 0; i < items.size(); i++) {
            InventorySlot* currentSlot = items[i];
            if (currentSlot->item.getItemId() == deleteItem.getItemId()) {
                if (currentSlot->count < count)
                    return false;
                else if (currentSlot->count == count) {
                    currentSlot->remove(count, character); //TODO: Pass Character reference to use item
                    items.erase(items.begin() + i);
                    return true;
                }
                else {
                    currentSlot->remove(count, character); //TODO: Pass Character reference to use item
                    return true;
                }
            }
        }
        return false;
    }

    Item& Inventory::getItem(std::string itemId) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i]->item.getItemId() == itemId) {
                return items[i]->item;
            }
        }
        return *nullItem;
    }
}

#endif