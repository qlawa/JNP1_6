#ifndef MONSTER_H
#define MONSTER_H
#include<vector>
#include<cassert>

using HealthPoints = int;
using AttackPower = int;

class Monster {
public:
    Monster(HealthPoints health, AttackPower attack);

    HealthPoints getHealth() const;

    AttackPower getAttackPower() const;

    void takeDamage(AttackPower damage);

protected:
    HealthPoints health;
    AttackPower attack;
};

class Zombie : public Monster {
public:
    Zombie(HealthPoints health, AttackPower attack);
};

class Mummy : public Monster {
public:
    Mummy(HealthPoints health, AttackPower attack);
};

class Vampire : public  Monster {
public:
    Vampire(HealthPoints health, AttackPower attack);
};

class GroupOfMonsters {
public:
    GroupOfMonsters(std::vector<Monster> _monsters);

    GroupOfMonsters(std::initializer_list<Monster> _monsters);

    HealthPoints getHealth() const;

    AttackPower getAttackPower() const;

    void takeDamage(AttackPower Damage);

private:
    std::vector<Monster> monsters;
};

// Create

Zombie createZombie(HealthPoints health, AttackPower attack);

Mummy createMummy(HealthPoints health, AttackPower attack);

Vampire createVampire(HealthPoints health, AttackPower attack);

GroupOfMonsters createGroupOfMonsters(std::vector<Monster> monsters);

GroupOfMonsters createGroupOfMonsters(std::initializer_list<Monster> monsters);

#endif //MONSTER_H