#include <iostream>
#include "block.h"

Block::Block() {}

Block::~Block() {}

Block::Block(const Block &other)
    : type{other.type}, initialLevel{other.initialLevel}, numsq{other.numsq}, 
      specialHeavy{other.specialHeavy}, levelHeavy{other.levelHeavy}, 
      curr_rotate{other.curr_rotate} {
    pass = other.pass;
    for (int i = 0; i < 4; i++) {
        position[i] = other.position[i];
    }
}

void Block::left() {
    for (int i = 0; i < 4; i++) {
        position[i].y--;
    }
    pass.y--;
}

void Block::right() {
    for (int i = 0; i < 4; i++) {
        position[i].y++;
    }
    pass.y++;
}

void Block::down() {
    for (int i = 0; i < 4; i++) {
        position[i].x++;
    }
    pass.x++;
}

void Block::up() {
    for (int i = 0; i < 4; i++) {
        position[i].x--;
    }
    pass.x--;
}


void Block::rotateCW() {
    int ways = getways();
    curr_rotate += 1;

    if (curr_rotate >= ways) {
        curr_rotate = 0;
    }

    for (int i = 0; i < 4; i++) {
        position[i].x = getrotate(curr_rotate)[i].x + pass.x;
        position[i].y = getrotate(curr_rotate)[i].y + pass.y;
    }
}

void Block::rotateAW() {
    int ways = getways();
    curr_rotate = curr_rotate - 1;

    if (curr_rotate < 0) {
        curr_rotate = ways - 1;
    }

    for (int i = 0; i < 4; i++) {
        position[i].x = getrotate(curr_rotate)[i].x + pass.x;
        position[i].y = getrotate(curr_rotate)[i].y + pass.y;
    }
}

char Block::getType() {
    return type;
}

