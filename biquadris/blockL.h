#ifndef _BLOCKL_H_
#define _BLOCKL_H_

#include "pos.h"
#include "block.h"

class BlockL: public Block {
    static int ways;
    static Pos initial[4][4]; // how many ways and how many cells

    public:
    ~BlockL();
    BlockL(int level);
    BlockL(const BlockL& other);
    const Pos* getrotate(int rotation) override;
    int getways() override;
    void updatePosition() override;
};

#endif
