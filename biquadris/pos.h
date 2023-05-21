#ifndef _POS_H_
#define _POS_H_

struct Pos{
  int x;
  int y;
  char c;
  int blockSqNum;
  char cover;
  Pos(int x = 0, int y = 0);
  Pos(const Pos& other);
};

struct BlockInfo {
    int sqNum;
    int originLevel;
    BlockInfo(int, int);
};

#endif
