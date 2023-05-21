#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <iostream>
#include <vector>
#include "pos.h"

class Block {
public:
    char type;
    int initialLevel;
    int numsq;
    int specialHeavy; // represents the number of effects that apply to the block by special actions
    int levelHeavy; // represents the number of effects that apply to the block by level
    int curr_rotate; // curr way of rotation
    Pos pass;
    Pos position[4];

    Block();
    virtual ~Block() = 0;
    Block(const Block& other);

    void left();
    void right();
    void down();
    void up();

    void rotateCW();
    void rotateAW();
    char getType();
    virtual const Pos* getrotate(int rotate) = 0;
    virtual int getways() = 0;
    virtual void updatePosition() = 0;
};

#endif
