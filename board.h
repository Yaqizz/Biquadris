#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <iostream>
#include <memory>
// for block
#include "block.h"
#include "blockI.h"
#include "blockJ.h"
#include "blockL.h"
#include "blockO.h"
#include "blockS.h"
#include "blockZ.h"
#include "blockT.h"
#include "blockStar.h"
// for level
#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
// for scoring
#include "scoring.h"
#include "pos.h"


class Board {
    std::vector<std::vector<std::shared_ptr<Pos>>> cells;
    std::shared_ptr<Block> curr_block;
    std::shared_ptr<Block> next_block;
    std::shared_ptr<Scoring> scoring;
    bool isBlind;
    bool specialAction;
public:
    std::vector<std::shared_ptr<BlockInfo>> bif;
    int numBlocks;
    std::shared_ptr<Level> level;
    // constructor and destructor
    Board();
    ~Board();

    std::shared_ptr<Block> createBlock(char, int);
    void transBlock();

    // geter for cells
    std::vector<std::vector<std::shared_ptr<Pos>>>& getCells(); 

    // geters and setter for block
    std::shared_ptr<Block> getCurrBlock();
    std::shared_ptr<Block> getNextBlock();
    void setCurrBlcok(std::shared_ptr<Block>);
    void setNextBlock(std::shared_ptr<Block>);

    // geters and setters for level
    std::shared_ptr<Level> getLevel();
    void setLevel(int, std::string);

    // geters and setters for score
    std::shared_ptr<Scoring> getScore();
    void setScore(int);


    int clearRow();
    void findBlock();

    void placeIn();
    void placeOut();
    bool check(int, int);
    bool checkPlace();

    // some functional operator
    void blind();
    void unblind();
    void heavy();
    bool force(char type);
    void endGame();
};

#endif
