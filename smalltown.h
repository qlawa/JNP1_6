#ifndef SMALLTOWN_H
#define SMALLTOWN_H

#include "citizen.h"
#include "monster.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>

using Time = int;

struct MyStatus {
private:
    std::string name;
    HealthPoints healthPoints;
    int aliveCitizens;
public:
    MyStatus (std::string name, HealthPoints healthPoints, int aliveCitizens) :
            name(name),
            healthPoints(healthPoints),
            aliveCitizens(aliveCitizens){}

    std::string getMonsterName() { return name; }

    HealthPoints getMonsterHealth() { return healthPoints; };

    int getAliveCitizens() { return aliveCitizens; }

    void decreaseHp(HealthPoints hp) {
        healthPoints -= hp;
    }

    void decreaseAlive() {
        aliveCitizens--;
    }
};

using Status = MyStatus;


class SmallTown {

private:
    Time act_time;
    Time t1;
    std::vector<std::shared_ptr<Citizen>> citizens;
    std::shared_ptr<MonsterBase> monster_base;
    Status status;

    int getAlive() {
        //to można usprawnić zmieniając na bieżąco liczbę żywych i usuwając martwych z vectora/kolejki?
        int alive = 0;
        for (auto c : citizens) {
            if (c->getHealth() > 0) {
                alive++;
            }
        }
        return alive;
    }

public:
    class Builder {
    public:
        Builder();

        Builder &monster(std::shared_ptr<Monster> m) {
            b_monster_base = m;
            return *this;
        }

        Builder &monster(std::shared_ptr<GroupOfMonsters> gm) {
            b_monster_base = gm;
            return *this;
        }

        Builder &startTime(Time t) {
            assert(t >= 0);
            b_t0 = t;
            return *this;
        }

        Builder &maxTime(Time t) {
            assert(t > 0);
            b_t1 = t;
            return *this;
        }

        Builder &citizen(std::shared_ptr<Citizen> c) {
            b_citizens.push_back(c);
            return *this;
        }

        Builder &citizen(std::shared_ptr<Sheriff> s) {
            b_citizens.push_back(s);
            return *this;
        }

        SmallTown build();

    private:
        Time b_t0;
        Time b_t1;
        std::vector<std::shared_ptr<Citizen>> b_citizens;
        std::shared_ptr<MonsterBase> b_monster_base;
    };

    SmallTown(Time t0, Time t1, std::shared_ptr<MonsterBase> m, Status s);

    Status &getStatus() {
        return status;
    }

    void tick(Time timeStep);

    void wypisz_potwory() {
        monster_base->wypisz_sie();
    }

    void wypisz_mieszkancow() {
        printf("Mieszkańcy:\n");
        for (auto &it : citizens) {
            it->wypisz_sie();
        }
    }
};

#endif //SMALLTOWN_H
