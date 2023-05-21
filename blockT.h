#ifndef _BLOCKT_H_
#define _BLOCKT_H_

#include "pos.h"
#include "block.h"

class BlockT: public Block {
    static int ways;
    static Pos initial[4][4]; // how many ways and how many cells

    public:
    ~BlockT();
    BlockT(int level);
    BlockT(const BlockT& other);
    const Pos* getrotate(int rotation) override;
    int getways() override;
    void updatePosition() override;
};

#endif
