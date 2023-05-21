#include "level1.h"

Level1::~Level1() {}

Level1::Level1( std::string f ) { 
    curlevel = 1;
    curblock = 0;
    count = 0;
    israndom = true;
    filename = f;
    if (f != "") readFile();
}

char Level1::makeBlock() {
    if (seed != 0) {
        srand(seed);
    }
    // level 1:
    int pSix = rand() % 6;
    int pTwo = rand() % 2;
    if ( pSix == 0 ) return 'I';
    if ( pSix == 1 ) return 'J';
    if ( pSix == 2 ) return 'L';
    if ( pSix == 3 ) return 'O';
    if ( pSix == 4 ) return 'T';
    if ( pTwo == 0 ) return 'S';
    return 'Z';
}

std::shared_ptr<Level> Level1::levelUp() {
    return std::make_shared<Level2>(filename);
}

std::shared_ptr<Level> Level1::levelDown() {
    return std::make_shared<Level0>(filename);
}
