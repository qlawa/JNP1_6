#include "smalltown.h"
#include<iostream>
#include <exception>

//Builder
class UndefinedBehaviour : public std::exception {
    const char *what() const throw() {
        return "undefined behaviour";
    }
};
SmallTown SmallTown::Builder::build() {
    if (b_t0 < 0 || b_t1 <= b_t0 || b_monster_base == nullptr || b_citizens.size() == 0) {
        throw UndefinedBehaviour();
    }
    assert(b_t0 >= 0);
    assert(b_t1 > b_t0); // poprawka
    auto st = SmallTown(b_t0, b_t1, b_monster_base, Status(b_monster_base->getName(), b_monster_base->getHealth(), (int)b_citizens.size()));
    st.citizens = b_citizens;
    return st;
}

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

void attack(std::vector<std::shared_ptr<Citizen>> citizens, std::shared_ptr<MonsterBase> m, Status &s) {
    auto c = citizens.begin();
    AttackPower monsterPower = m->getAttackPower();
    while (monsterPower > 0 && c != citizens.end()) {
        if ((*c)->getHealth() != 0) {
            (*c)->takeDamage(monsterPower);
            if ((*c)->getHealth() == 0) {
                s.decreaseAlive();
            }
            (*c)->defendYourself(m);
            if (m->getHealth() == 0) {
                monsterPower-=m->getAttackPower();
            }
        }
        s.decreaseHp(s.getMonsterHealth()- m->getHealth());
        c++;
    }

}

void SmallTown::tick(Time timeStep) {
    checkStatus(this->getStatus());
    if (isAGoodTimeForAttack(act_time)) {
        attack(this->citizens, this->monster_base, this->status);
    }
    act_time += timeStep;
    act_time %= (t1 + 1); // poprawka

}

SmallTown::Builder::Builder() {
    b_t1 = -1;
    b_t0 = -1;
    b_monster_base = nullptr;
}

SmallTown::SmallTown(Time t0, Time t1, std::shared_ptr<MonsterBase> m, Status s) :
        act_time(t0),
        t1(t1),
        monster_base(m),
        status(s) {
}
