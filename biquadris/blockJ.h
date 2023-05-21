#ifndef _BLOCKJ_H_
#define _BLOCKJ_H_

#include "pos.h"
#include "block.h"

class BlockJ: public Block {
    static int ways;
    static Pos initial[4][4]; // how many ways and how many cells

    public:
    ~BlockJ();
    BlockJ(int level);
    BlockJ(const BlockJ& other);
    const Pos* getrotate(int rotation) override;
    int getways() override;
    void updatePosition() override;
};

#endif
