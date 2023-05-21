#include "level4.h"

Level4::~Level4() {}

Level4::Level4( std::string f ) {
    curlevel = 4;
    curblock = 0;
    count = 0;
    israndom = true;
    filename = f;
    if (f != "") readFile();
}

char Level4::makeBlock() {
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

std::shared_ptr<Level> Level4::levelUp() {
    return std::shared_ptr<Level4>(this);
}

std::shared_ptr<Level> Level4::levelDown() {
    return std::make_shared<Level3>(filename);
}
