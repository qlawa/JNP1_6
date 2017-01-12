#ifndef MONSTER_H
#define MONSTER_H

#include <vector>
#include <cassert>
#include <cstdio>
#include <memory>

using HealthPoints = int;
using AttackPower = int;

class MonsterBase {
protected:
    HealthPoints health;
    AttackPower attack;
    std::string name;
public:
    virtual HealthPoints getHealth() const { return health; };

    virtual AttackPower getAttackPower() const { return attack; };

    virtual void takeDamage(AttackPower damage) { };

    virtual std::string getName() { return name; }
};

class Monster : public MonsterBase {
public:
    Monster(HealthPoints health, AttackPower attack, std::string name);

    HealthPoints getHealth() const;

    AttackPower getAttackPower() const;

    void takeDamage(AttackPower damage);

    std::string getName() { return name; }

protected:
    HealthPoints health;
    AttackPower attack;
    std::string name;
};

class Zombie : public Monster {
public:
    Zombie(HealthPoints health, AttackPower attack);
};

class Mummy : public Monster {
public:
    Mummy(HealthPoints health, AttackPower attack);
};

class Vampire : public Monster {
public:
    Vampire(HealthPoints health, AttackPower attack);
};

class GroupOfMonsters : public MonsterBase {
public:
    GroupOfMonsters(std::vector<std::shared_ptr<Monster>> _monsters);

    GroupOfMonsters(std::initializer_list<std::shared_ptr<Monster>> _monsters);

    HealthPoints getHealth() const;

    AttackPower getAttackPower() const;

    void takeDamage(AttackPower Damage);

    std::string getName() { return name; }

private:
    std::vector<std::shared_ptr<Monster>> monsters;
    std::string name;
};

// Create

std::shared_ptr<Zombie> createZombie(HealthPoints health, AttackPower attack);

std::shared_ptr<Mummy> createMummy(HealthPoints health, AttackPower attack);

std::shared_ptr<Vampire> createVampire(HealthPoints health, AttackPower attack);

std::shared_ptr<GroupOfMonsters> createGroupOfMonsters(std::vector<std::shared_ptr<Monster>> monsters);

std::shared_ptr<GroupOfMonsters> createGroupOfMonsters(std::initializer_list<std::shared_ptr<Monster>> monsters);

#endif //MONSTER_H