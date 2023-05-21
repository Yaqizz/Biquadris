#include "level2.h"

Level2::~Level2() {}

Level2::Level2( std::string f  )  {
    curlevel = 2;
    curblock = 0;
    count = 0;
    israndom = true;
    filename = f;
    if (f != "") readFile();
 }

char Level2::makeBlock() {
    if (seed != 0) {
        srand(seed);
    }
    // level 2:
    int pSeven = rand() % 7;
    if ( pSeven == 0 ) return 'I';
    if ( pSeven == 1 ) return 'J';
    if ( pSeven == 2 ) return 'L';
    if ( pSeven == 3 ) return 'O';
    if ( pSeven == 4 ) return 'T';
    if ( pSeven == 5 ) return 'S';
    return 'Z';    
}

std::shared_ptr<Level> Level2::levelUp() {
    return std::make_shared<Level3>(filename);
}

std::shared_ptr<Level> Level2::levelDown() {
    return std::make_shared<Level1>(filename);
}
