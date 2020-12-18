#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "inventory.h"
#include "equipment.h"
#include "item.h"

namespace rpg {
    const float b = 1.35f;
    const float ATTR_MULTIPLIER = 1.2f;

    enum CharacterClass {
        warrior,
        mage,
        thief
    };

    class Character {
    private:
        std::string _name;
        int _gold;
        int _level;
        int _experience;
        CharacterClass _characterClass;
        Inventory _inventory;
        int _attackDamage;
        float _criticalChance;
        int _criticalModifier;
        int _maxHealth;
        int _currentHealth;
        Equipment* _equipment;
    public:
        std::string getName();
        int getGold();
        int getLevel();
        CharacterClass getCharacterClass();
        Inventory* getInventory();
        int getAttackDamage();
        float getCriticalChance();
        int getCriticalModifier();
        int getMaxHealth();
        int getCurrentHealth();
        Equipment* getEquipment(int);
        int experienceToNextLevel();
        int getDefense();

        Character();
        Character(std::string, CharacterClass);
        ~Character();
        void takeDamage(int);
        int calculateDamage();
        void gainExperience(int);
        void heal(int);
        void addGold(int);
        bool removeGold(int);
    };

    std::string Character::getName() { return _name; }

    int Character::getGold() { return _gold; }

    int Character::getLevel() { return _level; }

    CharacterClass Character::getCharacterClass() { return _characterClass; }

    Inventory* Character::getInventory() { return &_inventory; }

    int Character::getAttackDamage() { return _attackDamage; }

    float Character::getCriticalChance() { return _criticalChance; }

    int Character::getCriticalModifier() { return _criticalModifier; }

    int Character::getMaxHealth() { return _maxHealth; }

    int Character::getCurrentHealth() { return _currentHealth; }

    Equipment* Character::getEquipment(int index) { return &_equipment[index]; }

    int Character::experienceToNextLevel() {
        return (int)(100 * ((1 - std::pow(b, _level))/(1 - b)) - 100 * ((1 - std::pow(b, _level - 1))/(1 - b)));
    }

    int Character::getDefense() {
        int defense;
        int arrLength = *(&_equipment + 1) - _equipment;
        for (int i = 0; i < arrLength; i++) {
            defense += _equipment[i].getArmor();
        }
        return defense;
    }

    Character::Character() {
        Character("", warrior);
    }

    Character::Character(std::string name, CharacterClass characterClass) {
        _name = name;
        _characterClass = characterClass;
        _gold = 100;
        _level = 1;
        _equipment = new Equipment[3];
        switch(characterClass) {
            case warrior:
                _attackDamage = 10;
                _criticalChance = 0;
                _criticalModifier = 0;
                _maxHealth = 100;
                break;
            case mage:
                _attackDamage = 15;
                _criticalChance = 0;
                _criticalModifier = 0;
                _maxHealth = 50;
                break;
            case thief:
                _attackDamage = 10;
                _criticalChance = 0.15f;
                _criticalModifier = 3;
                _maxHealth = 75;
                break;
            default:
                break;
        }
        _currentHealth = _maxHealth;
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    Character::~Character() {
        delete [] _equipment;
    }

    void Character::takeDamage(int amount) {
        amount -= getDefense();
        _currentHealth -= amount;
    }

    int Character::calculateDamage() {
        if (_criticalChance > 0) {
            float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            return r <= _criticalChance ? _attackDamage * _criticalModifier : _attackDamage;
        }

        return _attackDamage;
    }

    void Character::gainExperience(int amount) {
        _experience += amount;
        if (_experience >= experienceToNextLevel()) {
            _experience -= experienceToNextLevel();
            _level++;
            _maxHealth = (int)(_maxHealth * ATTR_MULTIPLIER);
            _attackDamage = (int)(_attackDamage * ATTR_MULTIPLIER);
        }
    }

    void Character::heal(int amount) {
        _currentHealth += amount;
    }

    void Character::addGold(int amount) {
        _gold += amount;
    }

    bool Character::removeGold(int amount) {
        if (amount > _gold)
            return false;
        _gold -= amount;
        return true;
    }
}
#endif