#ifndef CITIZEN_H
#define CITIZEN_H

#include <iostream>
#include <cassert>
#include <memory>
#include "monster.h"

using HealthPoints = int;
using Age = int;
using AttackPower = int;

class Citizen {
public:
    Citizen(HealthPoints health, Age age);

    HealthPoints getHealth() const;

    Age getAge() const;

    void takeDamage(AttackPower damage);

    virtual void defendYourself(std::shared_ptr<MonsterBase>) { }

protected:
    HealthPoints health;
    Age age;
};

class Adult : public Citizen {
public:
    Adult(HealthPoints health, Age age);
};

class Teenager : public Citizen {
public:
    Teenager(HealthPoints health, Age age);
};

class Sheriff : public Citizen {
public:
    Sheriff(HealthPoints health, Age age, AttackPower attack);

    AttackPower getAttackPower() const;

    void defendYourself(std::shared_ptr<MonsterBase> m) {
        m->takeDamage(getAttackPower());
    }

private:
    AttackPower attack;
};

// Create

std::shared_ptr<Adult> createAdult(HealthPoints health, Age age);

std::shared_ptr<Teenager> createTeenager(HealthPoints health, Age age);

std::shared_ptr<Sheriff> createSheriff(HealthPoints health, Age age, AttackPower attack);

#endif //CITIZEN_H