#ifndef _BLOCKI_H_
#define _BLOCKI_H_

#include "pos.h"
#include "block.h"

class BlockI: public Block {
    static int ways;
    static Pos initial[2][4]; // how many ways and how many cells

    public:
    BlockI(int level);
    ~BlockI();
    BlockI(const BlockI& other);
    const Pos* getrotate(int rotation) override;
    int getways() override;
    void updatePosition() override;
};

#endif
