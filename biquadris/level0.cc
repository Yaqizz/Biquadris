#include "level0.h"

Level0::~Level0() {}

Level0::Level0( std::string f ) { 
    curlevel = 0;
    curblock = 0;
    count = 0;
    israndom = true;
    filename = f;
    if (f != "") readFile();
}


char Level0::makeBlock() {
    if (seed != 0) {
        srand(seed);
    }
    // level 0: read from file one by one
    return makeFromInput();
}

std::shared_ptr<Level> Level0::levelUp() {
    return std::make_shared<Level1>(filename);
}

std::shared_ptr<Level> Level0::levelDown() {
    return std::shared_ptr<Level0>(this);
}
