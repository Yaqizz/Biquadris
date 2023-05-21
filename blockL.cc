#include <iostream>
#include "blockL.h"

using namespace std;

int BlockL::ways = 4;

Pos BlockL::initial[4][4] = {{Pos{1, 0},  Pos{1, 1}, Pos{1, 2}, Pos{0, 2}},
                            {Pos{-1, 0},  Pos{0, 0}, Pos{1, 0}, Pos{1, 1}},
                            {Pos{0, 0},  Pos{0, 1}, Pos{0, 2}, Pos{1, 0}},
                            {Pos{-1, 0}, Pos{-1, 1}, Pos{0, 1}, Pos{1, 1}}};

BlockL::~BlockL() {}

BlockL::BlockL(const BlockL& other): Block{other} {}

BlockL::BlockL(int level) {
    type = 'L';
    initialLevel = level;
    specialHeavy = 0;
    levelHeavy = 0;
    if ( level >= 3 ) levelHeavy++;
    curr_rotate = 0;
    pass = Pos{2,0};

    for (int i = 0; i < 4; i++) {
        position[i].x = initial[0][i].x + pass.x;
        position[i].y = initial[0][i].y + pass.y;
    }
}

const Pos* BlockL::getrotate(int rotate) {
    return initial[rotate];
}

int BlockL::getways() {
    return ways;
}

void BlockL::updatePosition() {
    for (int i = 0; i < 4; i++) {
        position[i].x = initial[0][i].x + pass.x;
        position[i].y = initial[0][i].y + pass.y;
    }
}
