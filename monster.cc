#include "monster.h"

// Monster

Monster::Monster(HealthPoints health, AttackPower attack) :
        health(health), attack(attack) {}

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
        Monster(health, attack) {}

// Mummy

Mummy::Mummy(HealthPoints health, AttackPower attack) :
        Monster(health, attack) {}

// Vampire

Vampire::Vampire(HealthPoints health, AttackPower attack) :
        Monster(health, attack) {}

// Create

Zombie createZombie(HealthPoints health, AttackPower attack) {
    assert(health > 0 && attack > 0);
    return Zombie(health, attack);
}

Mummy createMummy(HealthPoints health, AttackPower attack) {
    assert(health > 0 && attack > 0);
    return Mummy(health, attack);
}

Vampire createVampire(HealthPoints health, AttackPower attack) {
    assert(health > 0 && attack > 0);
    return Vampire(health, attack);
}

// GroupOfMonsters

GroupOfMonsters::GroupOfMonsters(std::vector<Monster> _monsters) {
    monsters.insert(monsters.end(), _monsters.begin(), _monsters.end());
}

GroupOfMonsters::GroupOfMonsters(std::initializer_list<Monster> _monsters) {
    monsters.insert(monsters.end(), _monsters.begin(), _monsters.end());
}

HealthPoints GroupOfMonsters::getHealth() const {
    HealthPoints groupHealth = 0;
    for (Monster monster : monsters) {
        groupHealth += monster.getHealth();
    }
    return groupHealth;
}

AttackPower GroupOfMonsters::getAttackPower() const{
    AttackPower groupAttack = 0;
    for (Monster monster : monsters) {
        if (monster.getHealth() != 0) {
            groupAttack += monster.getAttackPower();
        }
    }
    return groupAttack;
}

void GroupOfMonsters::takeDamage(AttackPower damage) {
    for (Monster& monster : monsters) {
        monster.takeDamage(damage);
    }
}

// Create GroupOfMonsters

GroupOfMonsters createGroupOfMonsters(std::vector<Monster> monsters) {
    return GroupOfMonsters(monsters);
}

GroupOfMonsters createGroupOfMonsters(std::initializer_list<Monster> monsters) {
    return GroupOfMonsters(monsters);
}