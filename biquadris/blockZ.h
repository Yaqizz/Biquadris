#ifndef _BLOCKZ_H_
#define _BLOCKZ_H_

#include "pos.h"
#include "block.h"

class BlockZ: public Block {
    static int ways;
    static Pos initial[2][4]; // how many ways and how many cells

    public:
    BlockZ();
    ~BlockZ();
    BlockZ(int level);
    BlockZ(const BlockZ& other);
    const Pos* getrotate(int rotation) override;
    int getways() override;
    void updatePosition() override;
};

#endif
