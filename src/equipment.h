#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include <string>

namespace rpg {

    class Equipment {
    private:
        std::string name;
        std::string equipmentId;
        int armor;
        int attackDamage;
    public:
        int getArmor();
        int getAttackDamage();
        std::string getName();
        std::string getEquipmentId();
        Equipment() {};
        Equipment(std::string, std::string, int, int);
    };

    Equipment::Equipment(std::string name, std::string id, int armor, int damage) {
        this->name = name;
        this->equipmentId = id;
        this->armor = armor;
        this->attackDamage = damage;
    }

    int Equipment::getArmor() { return armor; }

    int Equipment::getAttackDamage() { return attackDamage; }

    std::string Equipment::getName() { return name; }

    std::string Equipment::getEquipmentId() { return equipmentId; }
}

#endif