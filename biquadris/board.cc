#include "board.h"
#include <memory>

// constructor
Board::Board() {
    for (int i = 0; i < 18; ++i) {
        std::vector<std::shared_ptr<Pos>> row;
        for (int j = 0; j < 11; ++j) {
            std::shared_ptr<Pos> one = std::make_shared<Pos>(i, j);
            row.push_back(one);
        }
        cells.push_back(row);
    }
    curr_block = nullptr;
    next_block = nullptr;
    scoring = nullptr;
    numBlocks = 0;
    isBlind = false;
    specialAction = false;
    level = nullptr;
}

Board::~Board() {}

// ============== making new block =========================

// make new block   
std::shared_ptr<Block>  Board::createBlock(char c, int lv) {
    if (c == 'I') {
        return std::make_shared<BlockI>(lv);
    } else if (c == 'J') {
        return std::make_shared<BlockJ>(lv);
    } else if (c == 'L') {
        return std::make_shared<BlockL>(lv);
    } else if (c == 'O') {
        return std::make_shared<BlockO>(lv);
    } else if (c == 'S') {
        return std::make_shared<BlockS>(lv);
    } else if (c == 'Z') {
        return std::make_shared<BlockZ>(lv);
    } else if (c == 'T') {
        return std::make_shared<BlockT>(lv);
    } else {
        return nullptr;   
    }
}

// replace the curr_block with next_block and make a new block for new_block
void Board::transBlock() {
    //delete curr_block;
    curr_block = next_block;
    int currlevel = level->getcurrlevel();
    char c;
    if ( level->getFilename() == "" ) {
        c = getLevel()->makeBlock();
    } else {
        c = getLevel()->makeFromInput();
    }
    numBlocks += 1;
    bif.emplace_back(std::make_shared<BlockInfo>(numBlocks, currlevel));
    next_block = createBlock(c, currlevel);
    next_block->numsq = numBlocks + 1;
}

// ============== geter for cells ======================
std::vector<std::vector<std::shared_ptr<Pos>>>& Board::getCells() {
    return cells;
}

// ===== geters and setters for block ==================
std::shared_ptr<Block> Board::getCurrBlock() {
    return curr_block;
}

std::shared_ptr<Block> Board::getNextBlock() {
    return next_block;
}

void Board::setCurrBlcok(std::shared_ptr<Block> b) {
    if (curr_block != nullptr) {
        //delete curr_block;
    }
    curr_block = b;
}

void Board::setNextBlock(std::shared_ptr<Block> b) {
    next_block = b;
}

// ==== geters and setters for level ===================
std::shared_ptr<Level> Board::getLevel() {
    return level;
}

void Board::setLevel(int lv, std::string fileName) {
    if (lv == 0) {
        level = std::make_shared<Level0>(fileName);
    } else if (lv == 1) {
        level = std::make_shared<Level1>(fileName);
    } else if (lv == 2) {
        level = std::make_shared<Level2>(fileName);
    } else if (lv == 3) {
        level = std::make_shared<Level3>(fileName);
    } else if (lv == 4) {
        level = std::make_shared<Level4>(fileName);
    } 
}

// ==== geters and setters for scoring ================
std::shared_ptr<Scoring> Board::getScore() {
    return scoring;
}
void Board::setScore(int lv) {
    scoring = std::make_shared<Scoring>(lv);
}

// clear the row is the row is full and return the number of rows that have been cleared
int Board::clearRow() {
    int RowCancle = 0;
    for (int i = 3; i < 18; ++i) {
        bool isFull = true;
        for (int j = 0; j < 11; ++j) {
            if (cells[i][j]->c == ' ') {
                isFull = false;
                break;
            }
        }
        if (isFull) {
            // move down
            for (int k = i - 1; k >= 3; --k) {
                for (int j = 0; j < 11; ++j) {
                    cells[k + 1][j]->c = cells[k][j]->c;
                    cells[k + 1][j]->blockSqNum = cells[k][j]->blockSqNum;
                    cells[k][j]->c = ' ';
                    cells[k][j]->blockSqNum = 0;
                }
            }
            RowCancle += 1;
        }
    }
    if (RowCancle > 0) {
        int currlevel = curr_block->initialLevel;
        int final_score = (RowCancle + currlevel) * (RowCancle + currlevel);
        scoring->addscore(final_score);
    }
    return RowCancle;

}

// find the number 
void Board::findBlock() {
    int final_score = 0;
    for (unsigned int i = 0; i < bif.size(); ++i) {
        int currSeNum = bif[i]->sqNum;
        int olv = bif[i]->originLevel;
        bool isIn = false;
        for (int j = 3; j < 18; ++j) {
            for (int k = 0; k < 11; ++k) {
                if (cells[j][k]->blockSqNum == currSeNum) {
                    isIn = true;
                    break;
                }
            }
            if (isIn == true) {
                break;
            }
        }
        if (isIn == false) {
            final_score += (olv + 1) * (olv + 1); 
            //delete bif[i];
            bif.erase(bif.begin() + i);
            i = i - 1;
        }
    }
    scoring->addscore(final_score);
}

// set blind block
void Board::blind() {
    for ( int row = 5; row < 15; row++ ) {
        for ( int col = 2; col < 9; col++ ) {
            cells[row][col]->cover = '?';
        }
    }
    isBlind = true;
}

// unset blind block
void Board::unblind() {
    for ( int row = 5; row < 15; row++ ) {
        for ( int col = 2; col < 9; col++ ) {
            cells[row][col]->cover = ' ';
        }
    }
    isBlind = false;
}

void Board::heavy() {
    curr_block->specialHeavy += 1;
}

// placeIn
// put the block into the board
void Board::placeIn() {
    
    for (int j = 0; j < 4; ++j) {
        int x = curr_block->position[j].x;
        int y = curr_block->position[j].y;
        char c = curr_block->type;
        cells[x][y]->c = c;     
        int sq = numBlocks;
        sq = (sq % 2 == 0)? sq / 2 : sq / 2 + 1;
        cells[x][y]->blockSqNum = sq;
    }
}

// placeOut
// take the block out of the board
void Board::placeOut() {
    for (int j = 0; j < 4; ++j) {
        int x = curr_block->position[j].x;
        int y = curr_block->position[j].y;
        cells[x][y]->c = ' ';
        cells[x][y]->blockSqNum = 0;
    }
}

bool Board::check(int x, int y) {
    if ( x < 0 || x > 17 ) {
        return false;
    } else if ( y < 0 || y > 10) {
        return false; 
    } else if (cells[x][y]->c != ' ') {
        return false;
    } else {
        return true;
    }
}

// check whether it is ok to place the block
bool Board::checkPlace() {
    bool isMoveSucc = true;
    for (int i = 0; i < 4; ++i) {
        int x = curr_block->position[i].x;
        int y = curr_block->position[i].y;
        //std::cout << x << " " << y << std::endl;
        if (check(x, y) == false) {
            isMoveSucc = false;
            break;
        }
    }
    return isMoveSucc;
}

// force to replace the curr_block with the target block
bool Board::force( char type ) {
    std::shared_ptr<Block> temp = curr_block;
    std::shared_ptr<Block> newBlock = createBlock( type, curr_block->initialLevel );
    if (curr_block->getType() == 'I' && type == 'I') {
        newBlock->pass = curr_block->pass;
    } else if (type == 'I') {
        newBlock->pass = curr_block->pass;
        newBlock->pass.x++;
    } else {
        newBlock->pass = curr_block->pass;
    }
    newBlock->numsq = curr_block->numsq;
    newBlock->updatePosition();
    placeOut();
    
    curr_block = newBlock;
    if (checkPlace()) {
        placeIn();
        //delete temp;
        return true;
    } else {
        //delete curr_block;
        curr_block = temp;
        placeIn();
        return false;
    }
}
