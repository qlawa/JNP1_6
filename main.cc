#include "citizen.h"
#include "monster.h"
#include "smalltown.h"

int main(int argc, const char *argv[]) {

    auto mummy = createMummy(10, 20);

    auto smallTown = SmallTown::Builder()
            .monster(mummy)
            .citizen(createSheriff(1, 20, 9))
            .citizen(createTeenager(1,17))
            .startTime(3)
            .maxTime(6)
            .build();

    auto status1 = smallTown.getStatus();

    assert(status1.getMonsterHealth() == 10);
    assert(status1.getAliveCitizens() == 2);

    smallTown.tick(2);

    auto status2 = smallTown.getStatus();

    assert(status2.getMonsterHealth() == 1);
    assert(status2.getAliveCitizens() == 0);

    smallTown.tick(1);

    return 0;
}