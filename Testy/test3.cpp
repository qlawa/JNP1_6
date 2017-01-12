#include "citizen.cpp"
#include "monster.cpp"
#include "smalltown.cpp"
#include<iostream>
#include<vector>

int main(int argc, const char *argv[]) {

    std::vector<std::shared_ptr<Monster>> monsters;

    monsters.push_back(createZombie(10, 5));
    monsters.push_back(createVampire(20, 10));
    monsters.push_back(createMummy(30, 15));


    auto groupOfMonsters = createGroupOfMonsters(monsters);

    auto smallTown = SmallTown::Builder()
            .monster(groupOfMonsters)
            .citizen(createSheriff(100, 20, 10))
            .startTime(3)
            .maxTime(9)
            .build();

    auto status = smallTown.getStatus();

    assert(status.getMonsterHealth() == 60);
    assert(status.getAliveCitizens() == 1);

    smallTown.tick(2);

    status = smallTown.getStatus();
    
    assert(status.getMonsterHealth() == 30);
    assert(status.getAliveCitizens() == 1);

    smallTown.tick(1);
    status = smallTown.getStatus();

    assert(status.getMonsterHealth() == 30);
    assert(status.getAliveCitizens() == 1);

    smallTown.tick(3);
    status = smallTown.getStatus();

    assert(status.getMonsterHealth() == 10);
    assert(status.getAliveCitizens() == 1);

    smallTown.tick(3);
    status = smallTown.getStatus();

    assert(status.getMonsterHealth() == 0);
    assert(status.getAliveCitizens() == 1);

    smallTown.tick(1);

    return 0;
}