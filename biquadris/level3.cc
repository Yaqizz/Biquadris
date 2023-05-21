#include "level3.h"

Level3::~Level3() {}

Level3::Level3( std::string f ) { 
    curlevel = 3;
    curblock = 0;
    count = 0;
    israndom = true;
    filename = f;
    if (f != "") readFile();
}

char Level3::makeBlock() {
    if (seed != 0) {
        srand(seed);
    }
    //std::cout << "level: " << curlevel << std::endl;
    //std::cout << israndom << true << std::endl;
    if (israndom) {
        int pNine = rand() % 9;
        if ( pNine == 0 ) return 'I';
        if ( pNine == 1 ) return 'J';
        if ( pNine == 2 ) return 'L';
        if ( pNine == 3 ) return 'O';
        if ( pNine == 4 ) return 'T';
        if ( pNine == 5 || pNine == 6 ) return 'S';
        return 'Z';
    } else if (!israndom || filename != "") {
        return makeFromInput();
    } else {
        int pNine = rand() % 9;
        if ( pNine == 0 ) return 'I';
        if ( pNine == 1 ) return 'J';
        if ( pNine == 2 ) return 'L';
        if ( pNine == 3 ) return 'O';
        if ( pNine == 4 ) return 'T';
        if ( pNine == 5 || pNine == 6 ) return 'S';
         return 'Z';
    }  
}

std::shared_ptr<Level> Level3::levelUp() {
    return std::make_shared<Level4>(filename);
}

std::shared_ptr<Level> Level3::levelDown() {
    return std::make_shared<Level2>(filename);
}
