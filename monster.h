#ifndef MONSTER_H
#define MONSTER_H

#include<vector>
#include<cassert>
#include <cstdio>
#include <memory>

using HealthPoints = int;
using AttackPower = int;

class Monster_Base {
protected:
    HealthPoints health;
    AttackPower attack;
    std::string name;
public:
    //Monster_Base (Monster_Base & mb) = default;
    //virtual ~Monster_Base() = 0;
    virtual HealthPoints getHealth() const { return health; };

    virtual AttackPower getAttackPower() const { return attack; };

    virtual void takeDamage(AttackPower damage) { };

    virtual void wypisz_sie() { printf("Monster:\n- h=%d, at=%d\n", getHealth(), getAttackPower()); }

    //virtual void defend_yourself(Monster_Base &m) { };
    virtual std::string getName() { return name; }
};

class Monster : public Monster_Base {
public:
    Monster(HealthPoints health, AttackPower attack, std::string name);

    //Monster(Monster &m) = default;

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

class GroupOfMonsters : public Monster_Base {
public:

    //GroupOfMonsters(GroupOfMonsters &gm) = default;

    GroupOfMonsters(std::vector<std::shared_ptr<Monster>> _monsters);

    GroupOfMonsters(std::initializer_list<std::shared_ptr<Monster>> _monsters);

    HealthPoints getHealth() const;

    AttackPower getAttackPower() const;

    void takeDamage(AttackPower Damage);

    std::string getName() { return name; }


    void wypisz_sie() {
        printf("Group_of_montsers:\n");
        for (auto m : monsters) {
            printf("- h=%d, a=%d\n", m->getHealth(), m->getAttackPower());
        }
    }

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