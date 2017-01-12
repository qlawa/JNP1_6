#ifndef SMALLTOWN_H
#define SMALLTOWN_H

#include "citizen.h"
#include "monster.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>

struct MyStatus {
private:
    std::string name;
    HealthPoints healthPoints;
    int aliveCitizens;
public:
    MyStatus(std::string name, HealthPoints healthPoints, int aliveCitizens);

    std::string getMonsterName();

    HealthPoints getMonsterHealth();;

    int getAliveCitizens();

    void decreaseHp(HealthPoints hp);

    void decreaseAlive();
};

using Status = MyStatus;
using Time = int;


class SmallTown {

private:
    Time actTime;
    Time t1;
    std::vector<std::shared_ptr<Citizen>> citizens;
    std::shared_ptr<MonsterBase> monsterBase;
    Status status;

    int getAlive();

public:
    class Builder {
    public:
        Builder();

        Builder &monster(std::shared_ptr<Monster> m) {
            buidMonsterBase = m;
            return *this;
        }

        Builder &monster(std::shared_ptr<GroupOfMonsters> gm) {
            buidMonsterBase = gm;
            return *this;
        }

        Builder &startTime(Time t) {
            assert(t >= 0);
            buildT0 = t;
            return *this;
        }

        Builder &maxTime(Time t) {
            assert(t > 0);
            buildT1 = t;
            return *this;
        }

        Builder &citizen(std::shared_ptr<Citizen> c) {
            buildCitizens.push_back(c);
            return *this;
        }

        Builder &citizen(std::shared_ptr<Sheriff> s) {
            buildCitizens.push_back(s);
            return *this;
        }

        SmallTown build();

    private:
        Time buildT0;
        Time buildT1;
        std::vector<std::shared_ptr<Citizen>> buildCitizens;
        std::shared_ptr<MonsterBase> buidMonsterBase;
    };

    SmallTown(Time t0, Time t1, std::shared_ptr<MonsterBase> m, Status s);

    Status & getStatus();

    void tick(Time timeStep);

};

#endif //SMALLTOWN_H
