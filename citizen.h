#ifndef CITIZEN_H
#define CITIZEN_H
#include<iostream>
#include<cassert>

using HealthPoints = int;
using Age = int;
using AttackPower = int;

class Citizen {
public:
    Citizen(HealthPoints health, Age age);

    HealthPoints getHealth() const;

    Age getAge() const ;

    void takeDamage(AttackPower damage);

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

private:
    AttackPower attack;
};

// Create

Adult createAdult(HealthPoints health, Age age);

Teenager createTeenager(HealthPoints health, Age age);

Sheriff createSheriff(HealthPoints health, Age age, AttackPower attack);

#endif //CITIZEN_H