#include "smalltown.h"
#include<iostream>
#include <exception>

namespace {
    class UndefinedBehaviour : public std::exception {
        const char *what() const throw() {
            return "undefined behaviour";
        }
    };

    bool isAGoodTimeForAttack(Time t) {
        return (t % 7 != 0 && (t % 3 == 0 || t % 13 == 0));
    }

    void checkStatus(Status status) {
        if (status.getAliveCitizens() == 0 && status.getMonsterHealth() == 0) {
            std::cout << "DRAW" << std::endl;
            exit(0);
        } else if (status.getAliveCitizens() == 0) {
            std::cout << "MONSTER WON" << std::endl;
            exit(0);
        } else if (status.getMonsterHealth() == 0) {
            std::cout << "CITIZENS WON" << std::endl;
            exit(0);
        }
    }

    void attack(std::vector<std::shared_ptr<Citizen>> citizens,
                std::shared_ptr<MonsterBase> monster, Status &status) {
        auto citizen = citizens.begin();
        AttackPower monsterPower = monster->getAttackPower();
        while (monsterPower > 0 && citizen != citizens.end()) {
            if ((*citizen)->getHealth() != 0) {
                (*citizen)->takeDamage(monsterPower);
                if ((*citizen)->getHealth() == 0) {
                    status.decreaseAlive();
                }
                (*citizen)->defendYourself(monster);
                if (monster->getHealth() == 0) {
                    monsterPower -= monster->getAttackPower();
                }
            }
            status.decreaseHp(status.getMonsterHealth() - monster->getHealth());
            citizen++;
        }

    }
}

SmallTown SmallTown::Builder::build() {
    if (buildT0 < 0 || buildT1 < buildT0 || buidMonsterBase == nullptr || buildCitizens.size() == 0) {
        throw UndefinedBehaviour();
    }
    assert(buildT0 >= 0);
    assert(buildT1 >= buildT0);
    auto st = SmallTown(buildT0, buildT1, buidMonsterBase, Status(buidMonsterBase->getName(),
           buidMonsterBase->getHealth(), (int)buildCitizens.size()));
    st.citizens = buildCitizens;
    return st;
}

void SmallTown::tick(Time timeStep) {
    checkStatus(getStatus());
    if (isAGoodTimeForAttack(actTime)) {
        attack(citizens, monsterBase, status);
    }
    actTime += timeStep;
    actTime %= (t1 + 1);

}

SmallTown::Builder::Builder() {
    buildT1 = -1;
    buildT0 = -1;
    buidMonsterBase = nullptr;
}

SmallTown::SmallTown(Time t0, Time t1, std::shared_ptr<MonsterBase> m, Status s) :
        actTime(t0),
        t1(t1),
        monsterBase(m),
        status(s) { }

MyStatus::MyStatus(std::string name, HealthPoints healthPoints, int aliveCitizens) :
        name(name),
        healthPoints(healthPoints),
        aliveCitizens(aliveCitizens) { }

std::string MyStatus::getMonsterName() { return name; }

HealthPoints MyStatus::getMonsterHealth() { return healthPoints; }

int MyStatus::getAliveCitizens() { return aliveCitizens; }

void MyStatus::decreaseHp(HealthPoints hp) {
    healthPoints -= hp;
}

void MyStatus::decreaseAlive() {
    aliveCitizens--;
}

int SmallTown::getAlive() {
    int alive = 0;
    for (auto c : citizens) {
        if (c->getHealth() > 0) {
            alive++;
        }
    }
    return alive;
}

Status &SmallTown::getStatus() {
    return status;
}