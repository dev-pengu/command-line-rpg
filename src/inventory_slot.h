#ifndef INVENTORYSLOT_H
#define INVENTORYSLOT_H
#include "item.h"
//#include "character.h"

namespace rpg
{
    class Character;
    struct InventorySlot {
        Item item;
        int count;

        bool remove(int amount, Character* character) {
            if (amount > count)
                return false;
            count -= amount;
            if (character != nullptr) {
                for (int i = 0; i < amount; i++) {
                    item.use(character);
                }
            }
            return true;
        }

        void add(int amount) {
            count += amount;
        }

        InventorySlot() {
            count = 0;
            item = *nullItem;
        }
    };
}


#endif