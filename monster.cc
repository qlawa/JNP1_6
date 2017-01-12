#include "monster.h"

// Monster

Monster::Monster(HealthPoints health, AttackPower attack, std::string name) :
        health(health), attack(attack), name(name) {}

HealthPoints Monster::getHealth() const {
    return health;
}

AttackPower Monster::getAttackPower() const {
    return attack;
}

void Monster::takeDamage(AttackPower damage) {
    health = std::max(0, health - damage);
}

// Zombie

Zombie::Zombie(HealthPoints health, AttackPower attack) :
        Monster(health, attack, "Zombie") {}

// Mummy

Mummy::Mummy(HealthPoints health, AttackPower attack) :
        Monster(health, attack, "Mummy") {}

// Vampire

Vampire::Vampire(HealthPoints health, AttackPower attack) :
        Monster(health, attack, "Vampire") {}

// Create

std::shared_ptr<Zombie> createZombie(HealthPoints health, AttackPower attack) {
    assert(health > 0 && attack > 0);
    return std::make_shared<Zombie>(Zombie(health, attack));
}

std::shared_ptr<Mummy> createMummy(HealthPoints health, AttackPower attack) {
    assert(health > 0 && attack > 0);
    return std::make_shared<Mummy>(Mummy(health, attack));
}

std::shared_ptr<Vampire> createVampire(HealthPoints health, AttackPower attack) {
    assert(health > 0 && attack > 0);
    return std::make_shared<Vampire>(Vampire(health, attack));
}

// GroupOfMonsters

GroupOfMonsters::GroupOfMonsters(std::vector<std::shared_ptr<Monster>> _monsters) : name("GroupOfMonsters"){
    monsters.insert(monsters.end(), _monsters.begin(), _monsters.end());
}

GroupOfMonsters::GroupOfMonsters(std::initializer_list<std::shared_ptr<Monster>> _monsters)  : name("GroupOfMonsters") {
    monsters.insert(monsters.end(), _monsters.begin(), _monsters.end());
}

HealthPoints GroupOfMonsters::getHealth() const {
    HealthPoints groupHealth = 0;
    for (auto monster : monsters) {
        groupHealth += monster->getHealth();
    }
    return groupHealth;
}

AttackPower GroupOfMonsters::getAttackPower() const{
    AttackPower groupAttack = 0;
    for (auto monster : monsters) {
        if (monster->getHealth() != 0) {
            groupAttack += monster->getAttackPower();
        }
    }
    return groupAttack;
}

void GroupOfMonsters::takeDamage(AttackPower damage) {
    for (auto monster : monsters) {
        monster->takeDamage(damage);
    }
}

// Create GroupOfMonsters

std::shared_ptr<GroupOfMonsters> createGroupOfMonsters(std::vector<std::shared_ptr<Monster>> monsters) {
    return std::make_shared<GroupOfMonsters>(GroupOfMonsters(monsters));
}

std::shared_ptr<GroupOfMonsters> createGroupOfMonsters(std::initializer_list<std::shared_ptr<Monster>> monsters) {
    return std::make_shared<GroupOfMonsters>(GroupOfMonsters(monsters));
}

