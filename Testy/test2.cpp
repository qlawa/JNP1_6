#include "citizen.cpp"
#include "monster.cpp"
#include "smalltown.cpp"

int main(int argc, const char *argv[]) {

    auto vampire = createVampire(10, 10);

    auto smallTown = SmallTown::Builder()
            .monster(vampire)
            .citizen(createSheriff(100, 20, 10))
            .startTime(3)
            .maxTime(6)
            .build();

    auto status1 = smallTown.getStatus();

    assert(status1.getMonsterHealth() == 10);
    assert(status1.getAliveCitizens() == 1);

    smallTown.tick(2);

    auto status2 = smallTown.getStatus();

    assert(status2.getMonsterHealth() == 0);
    assert(status2.getAliveCitizens() == 1);

    smallTown.tick(1);

    return 0;
}