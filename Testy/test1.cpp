#include "citizen.cpp"
#include "monster.cpp"
#include "smalltown.cpp"

int main(int argc, const char *argv[]) {

    auto zombie = createZombie(20, 100);

    auto smallTown = SmallTown::Builder()
            .monster(zombie)
            .citizen(createAdult(100, 20))
            .startTime(7)
            .maxTime(23)
            .build();

    smallTown.tick(2);

    auto status1 = smallTown.getStatus();

    assert(status1.getMonsterHealth() == 20);
    assert(status1.getAliveCitizens() == 1);

    smallTown.tick(1);
    auto status2 = smallTown.getStatus();

    assert(status2.getMonsterHealth() == 20);
    assert(status2.getAliveCitizens() == 0);

    smallTown.tick(1);

    return 0;
}