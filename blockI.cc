#include <iostream>
#include "blockI.h"

using namespace std;

int BlockI::ways = 2;

Pos BlockI::initial[2][4] = {{Pos{0, 0},  Pos{0, 1},  Pos{0, 2},  Pos{0, 3}},
                                   {Pos{-3, 0}, Pos{-2, 0}, Pos{-1, 0}, Pos{0, 0}}};

BlockI::~BlockI() {}

BlockI::BlockI(const BlockI& other): Block{other} {}

BlockI::BlockI(int level) {
    type = 'I';
    initialLevel = level;
    specialHeavy = 0;
    levelHeavy = 0;
    if ( level >= 3 ) levelHeavy++;
    curr_rotate = 0;
    pass = Pos{3,0};

    for (int i = 0; i < 4; i++) {
        position[i].x = initial[0][i].x + pass.x;
        position[i].y = initial[0][i].y + pass.y;
    }
}

const Pos* BlockI::getrotate(int rotate) {
    return initial[rotate];
}

int BlockI::getways() {
    return ways;
}
void BlockI::updatePosition() {
    for (int i = 0; i < 4; i++) {
        position[i].x = initial[0][i].x + pass.x;
        position[i].y = initial[0][i].y + pass.y;
    }
}
