#include <iostream>
#include "blockZ.h"

using namespace std;

int BlockZ::ways = 2;

Pos BlockZ::initial[2][4] = {{Pos{0, 0},  Pos{0, 1}, Pos{1, 1}, Pos{1, 2}},
                             {Pos{1, 0}, Pos{0, 0}, Pos{0, 1}, Pos{-1, 1}}};

BlockZ::~BlockZ() {}

BlockZ::BlockZ(const BlockZ& other): Block{other} {}

BlockZ::BlockZ(int level) {
    type = 'Z';
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

const Pos* BlockZ::getrotate(int rotate) {
    return initial[rotate];
}

int BlockZ::getways() {
    return ways;
}

void BlockZ::updatePosition() {
    for (int i = 0; i < 4; i++) {
        position[i].x = initial[0][i].x + pass.x;
        position[i].y = initial[0][i].y + pass.y;
    }
}
