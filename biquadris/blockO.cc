#include <iostream>
#include "blockO.h"

using namespace std;

int BlockO::ways = 1;

Pos BlockO::initial[1][4] = {{Pos{0, 0}, Pos{0, 1}, Pos{1, 0}, Pos{1, 1}}};

BlockO::~BlockO() {}

BlockO::BlockO(const BlockO& other): Block{other} {}

BlockO::BlockO(int level) {
    type = 'O';
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

const Pos* BlockO::getrotate(int rotate) {
    return initial[rotate];
}

int BlockO::getways() {
    return ways;
}
void BlockO::updatePosition() {
    for (int i = 0; i < 4; i++) {
        position[i].x = initial[0][i].x + pass.x;
        position[i].y = initial[0][i].y + pass.y;
    }
}
