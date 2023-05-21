#ifndef _BLOCKO_H_
#define _BLOCKO_H_

#include "pos.h"
#include "block.h"

class BlockO: public Block {
    static int ways;
    static Pos initial[1][4]; // how many ways and how many cells

    public:
    ~BlockO();
    BlockO(int level);
    BlockO(const BlockO& other);
    const Pos* getrotate(int rotation) override;
    int getways() override;
    void updatePosition() override;
};

#endif
