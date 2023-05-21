#include <iostream>
#include "blockStar.h"
#include "pos.h"
using namespace std;

BlockStar::~BlockStar() {}

BlockStar::BlockStar() {
  type = '*';
  initialLevel = 4;
  specialHeavy = 0;
  levelHeavy = 0;
  curr_rotate = 0;
  pass = Pos{0,0};

  for (int i = 0; i < 4; i++) {
    position[i] = Pos {0, 5};
  }
}


const Pos* BlockStar::getrotate(int rotate) {
    return nullptr;
}

int BlockStar::getways() {
    return 0;
}

void BlockStar::updatePosition() { }
