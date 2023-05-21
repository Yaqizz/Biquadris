#include "pos.h"
Pos::Pos(int x, int y) : x{x}, y{y}, c{' '},  blockSqNum{0}, cover{' '} {}
Pos::Pos(const Pos& other) : x{other.x}, y{other.y} {}

BlockInfo::BlockInfo(int sqNum, int olv): sqNum{sqNum}, originLevel{olv} {}
