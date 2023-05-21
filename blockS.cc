#include <iostream>
#include "blockS.h"

using namespace std;

int BlockS::ways = 2;

Pos BlockS::initial[2][4] = {{Pos{0, 1}, Pos{0, 2}, Pos{1, 0}, Pos{1, 1}},
                             {Pos{1, 1}, Pos{0, 1}, Pos{0, 0}, Pos{-1, 0}}};

BlockS::~BlockS() {}

BlockS::BlockS(const BlockS& other): Block{other} {}

BlockS::BlockS(int level) {
    type = 'S';
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

const Pos* BlockS::getrotate(int rotate) {
    return initial[rotate];
}

int BlockS::getways() {
    return ways;
}

void BlockS::updatePosition() {
    for (int i = 0; i < 4; i++) {
        position[i].x = initial[0][i].x + pass.x;
        position[i].y = initial[0][i].y + pass.y;
    }
}
