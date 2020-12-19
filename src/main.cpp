#include <iostream>
#include <string>
#include "character.h"
#include "equipment.h"
#include "inventory.h"
#include "item.h"


int main() {

    int userInputInt;
    std::string userInputString;
    std::string userName;
    int userCharacterClass;

    std::cout << "What is your name traveler? >>";
    std::getline(std::cin, userName);
    std::cout << "Welcome! Are you a:\n1.\t Warrior\n2.\tMage\n3.\tThief\n>>";
    std::cin >> userCharacterClass;
    
    rpg::Character userCharacter(userName, static_cast<rpg::CharacterClass>(userCharacterClass));

    rpg::Item healthPotion("health-potion-20", "Health Potion");
    userCharacter.getInventory()->addItem(healthPotion, 3);
    userCharacter.getInventory()->print();
    userCharacter.getInventory()->removeItem(healthPotion, 1, &userCharacter);
    userCharacter.getInventory()->print();
    return 0;
}