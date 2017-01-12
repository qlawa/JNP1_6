//
//  horror_example.cc
//  horror-movie-2
//
//  Created by Patrycja Wegrzynowicz on 12/10/16.
//  Copyright (c) 2016 Patrycja Wegrzynowicz. All rights reserved.
//

#include "citizen.h"
#include "monster.h"
#include "smalltown.h"
void wypisz(SmallTown &smallTown) {
    smallTown.wypisz_mieszkancow();
    smallTown.wypisz_potwory();
    printf("\n");
}
void test1() {
    auto groupOfMonsters = createGroupOfMonsters({
                                                         createMummy(90, 1),
                                                         createZombie(20, 1),
                                                         createVampire(30, 1)
                                                 });

    //auto groupOfMonsters = createMummy(100, 10);
    auto smallTown = SmallTown::Builder()
            .monster(groupOfMonsters)
            .startTime(3)
            .maxTime(27)
            .citizen(createSheriff(100, 35, 20))
            .citizen(createAdult(100, 21))
            .citizen(createTeenager(50, 14))
            .build();

    smallTown.tick(18);
    smallTown.tick(3);

    //wypisz(smallTown);

    auto status = smallTown.getStatus();
//    printf("%s\n", status.getMonsterName().c_str());
    assert(status.getMonsterName() == "GroupOfMonsters");
    assert(status.getMonsterHealth() == 80);
    assert(status.getAliveCitizens() == 3);
    printf("Test1 passed\n");
}

void test2() {
    auto monster = createVampire(20, 100);
    auto st = SmallTown::Builder()
    .monster(monster)
    .citizen(createSheriff(10, 20, 20))
    .citizen(createTeenager(90, 13))
    .startTime(0)
    .maxTime(100)
    .build();

    st.tick(13);

    wypisz(st);
    st.tick(0);
    st.tick(0);
    st.tick(0);

    wypisz(st);

}

int main(int argc, const char * argv[]) {
    test2();
    return 0;
}
