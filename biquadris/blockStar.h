#ifndef _BLOCKSTAR_H_
#define _BLOCKSTAR_H_

#include "pos.h"
#include "block.h"


class BlockStar: public Block {
    public:
    BlockStar();
    ~BlockStar();
    const Pos* getrotate(int rotation) override;
    int getways() override;
    void updatePosition() override;
};

#endif
