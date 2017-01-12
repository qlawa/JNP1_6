#include "smalltown.h"
#include<iostream>

//Builder

SmallTown SmallTown::Builder::build() {
    assert(b_t0 >= 0);
    assert(b_t1 > b_t0); // poprawka
    auto st = SmallTown(b_t0, b_t1, b_monster_base);
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

void attack(std::vector<std::shared_ptr<Citizen>> citizens, std::shared_ptr<Monster_Base> m) {
    auto c = citizens.begin();
    AttackPower monster_power = m->getAttackPower();
    HealthPoints citizen_hp = (*c)->getHealth();
    while (monster_power > 0 && c != citizens.end()) {
        (*c)->takeDamage(monster_power);
        (*c)->defendYourself(m);
        c++;
    }

}

void SmallTown::tick(Time timeStep) {
    checkStatus(this->getStatus());
    if (isAGoodTimeForAttack(act_time)) {
        attack(this->citizens, this->monster_base);
    }
    act_time += timeStep;
    act_time %= (t1 + 1); // poprawka

}

SmallTown::Builder::Builder() {
    b_t1 = -1;
    b_t0 = -1;
    b_monster_base = nullptr;
}

SmallTown::SmallTown(Time t0, Time t1, std::shared_ptr<Monster_Base> m) : act_time(t0), t1(t1), monster_base(m) {
}
