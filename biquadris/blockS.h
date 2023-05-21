#ifndef _BLOCKS_H_
#define _BLOCKS_H_

#include "pos.h"
#include "block.h"

class BlockS: public Block {
    static int ways;
    static Pos initial[2][4]; // how many ways and how many cells

    public:
    ~BlockS();
    BlockS();
    BlockS(int level);
    BlockS(const BlockS& other);
    const Pos* getrotate(int rotation) override;
    int getways() override;
    void updatePosition() override;
};

#endif
