#include "citizen.h"

// Citizen

Citizen::Citizen(HealthPoints health, Age age) :
        health(health), age(age) {}

HealthPoints Citizen::getHealth() const {
    return health;
}

Age Citizen::getAge() const {
    return age;
}

void Citizen::takeDamage(AttackPower damage) {
    health = std::max(0, health - damage);
}

// Adult

Adult::Adult(HealthPoints health, Age age) : Citizen(health, age){};

// Teenager

Teenager::Teenager(HealthPoints health, Age age) : Citizen(health, age){};

// Sheriff

Sheriff::Sheriff(HealthPoints health, Age age, AttackPower attack) :
    Citizen(health, age), attack(attack) {}

AttackPower Sheriff::getAttackPower() const {
    return attack;
}

// Create

Adult createAdult(HealthPoints health, Age age) {
    assert(age >= 18 && age <= 100);
    assert(health > 0);
    return Adult(health, age);
}

Teenager createTeenager(HealthPoints health, Age age) {
    assert(age >= 11 && age <= 17);
    assert(health > 0);
    return Teenager(health, age);
}

Sheriff createSheriff(HealthPoints health, Age age, AttackPower attack) {
    assert(age > 0);
    assert(health > 0);
    assert(attack > 0);
    return Sheriff(health, age, attack);
}