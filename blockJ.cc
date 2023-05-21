#include <iostream>
#include "blockJ.h"

using namespace std;


int BlockJ::ways = 4;

Pos BlockJ::initial[4][4] = {{Pos{0,0}, Pos{1,0}, Pos{1,1}, Pos{1,2}},
                             {Pos{-1,1}, Pos{-1,0}, Pos{0,0}, Pos{1,0}},
                             {Pos{0,0}, Pos{0,1}, Pos{0,2}, Pos{1,2}},
                             {Pos{1,0}, Pos{1,1}, Pos{0,1}, Pos{-1,1}}};

BlockJ::~BlockJ() {}

BlockJ::BlockJ(const BlockJ& other): Block{other} {}

BlockJ::BlockJ(int level) {
    type = 'J';
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

const Pos* BlockJ::getrotate(int rotate) {
    return initial[rotate];
}

int BlockJ::getways() {
    return ways;
}

void BlockJ::updatePosition() {
    for (int i = 0; i < 4; i++) {
        position[i].x = initial[0][i].x + pass.x;
        position[i].y = initial[0][i].y + pass.y;
    }
}
