#include "boardctrl.h"
 #include <sstream>
 #include <fstream>


// ====== Helper function ==========================
std::shared_ptr<Board> BoardCtrl::whichOne(int i) {
    if (i % 2 == 0) {
        return board2;
    } else {
        return board1;
    }
}

bool BoardCtrl::check(int x, int y, std::shared_ptr<Board> b) {
    if ( x < 0 || x > 17 ) {
        return false;
    } else if ( y < 0 || y > 10) {
        return false; 
    } else if (b->getCells()[x][y]->c != ' ') {
        return false;
    } else {
        return true;
    }
}

// make next block for next round
void BoardCtrl::NextRound(int i) {
    std::shared_ptr<Board> processB = whichOne(i);
    processB->transBlock();
}

// checkPlace 
bool BoardCtrl::checkPlace(int i) {
    std::shared_ptr<Board> processB = whichOne(i);
    bool isMoveSucc = true;
    for (int i = 0; i < 4; ++i) {
        int x = processB->getCurrBlock()->position[i].x;
        int y = processB->getCurrBlock()->position[i].y;
        //std::cout << x << " " << y << std::endl;
        if (check(x, y, processB) == false) {
            isMoveSucc = false;
            break;
        }
    }
    return isMoveSucc;
}

// placeIn
void BoardCtrl::placeIn(int i) {
    std::shared_ptr<Board>  processB = whichOne(i);
    
    for (int j = 0; j < 4; ++j) {
        int x = processB->getCurrBlock()->position[j].x;
        int y = processB->getCurrBlock()->position[j].y;
        char c = processB->getCurrBlock()->type;
        processB->getCells()[x][y]->c = c;     
        int sq = i;
        sq = (sq % 2 == 0)? sq / 2 : sq / 2 + 1;
        processB->getCells()[x][y]->blockSqNum = sq;
    }
}

// placeOut
void BoardCtrl::placeOut(int i) {
    std::shared_ptr<Board> processB = whichOne(i);
    for (int j = 0; j < 4; ++j) {
        int x = processB->getCurrBlock()->position[j].x;
        int y = processB->getCurrBlock()->position[j].y;
        processB->getCells()[x][y]->c = ' ';
        processB->getCells()[x][y]->blockSqNum = 0;
    }
}

// check star
void BoardCtrl::check_star(int& round, int& count, int& level, int num_row){
    if (level == 4) {
        count++;
    } else {
        return;
    }
    std::shared_ptr<Board> bo = nullptr;
    if (round % 2 != 0) {
        bo = board1;
    } else {
        bo = board2;
    }
    if (count % 5 == 0 && num_row == 0 && count != 0) {
        std::shared_ptr<Block> b = std::make_shared<BlockStar>();
        int x = b->position[0].x + 17;
        int y = b->position[0].y;
        while (x > 0) {
            if (bo->getCells()[x][y]->c != ' ') {
                x--;
            } else {
                break;
            }
        }
        bo->getCells()[x][y]->c = '*';
    }
}

// ======== Constructor and Destructor =================================

BoardCtrl::BoardCtrl( bool textOnly ): board1{std::make_shared<Board>()}, board2{std::make_shared<Board>()}, view{std::make_shared<BoardView>(textOnly)} { }

BoardCtrl::~BoardCtrl() {}

// ========== Command function =========================================

// START
void BoardCtrl::start(int currlevel, std::string filename1, std::string filename2) {
  // creat two new boards for 2 player

    // initialize each board
    // for level
    board1->setLevel(currlevel, filename1);
    board2->setLevel(currlevel, filename2);
    
    // for score
    board1->setScore(currlevel);
    board2->setScore(currlevel);
    
    // for board1 current and next blocks
    char blk = board1->getLevel()->makeBlock();
    board1->setCurrBlcok(board1->createBlock(blk, currlevel));
    board1->numBlocks += 1;
    board1->getCurrBlock()->numsq = board1->numBlocks;
    board1->bif.emplace_back(std::make_shared<BlockInfo>(board1->numBlocks, currlevel));

    blk = board1->getLevel()->makeBlock();
    board1->setNextBlock(board1->createBlock(blk, currlevel));
    board1->getNextBlock()->numsq = board1->numBlocks + 1;
   

    // for board2 current and next blocks
    blk = board2->getLevel()->makeBlock();
    board2->setCurrBlcok(board2->createBlock(blk, currlevel));
    board2->numBlocks += 1;
    board2->getCurrBlock()->numsq = board1->numBlocks;
    board2->bif.emplace_back(std::make_shared<BlockInfo>(board2->numBlocks, currlevel));
    
    blk = board2->getLevel()->makeBlock();
    board2->setNextBlock(board2->createBlock(blk, currlevel));
    board1->getNextBlock()->numsq = board1->numBlocks + 1;
    
}

// RESTART
void BoardCtrl::restart() {
    int hi1 = board1->getScore()->gethiscore();
    int hi2 = board2->getScore()->gethiscore();
    //delete board1;
    //delete board2;
    board1 = std::make_shared<Board>();
    board2 = std::make_shared<Board>();
    std::string filename1 = "sequence1.txt";
    std::string filename2 = "sequence2.txt";
    start(0, filename1, filename2);
    board1->getScore()->sethiscore(hi1);
    board2->getScore()->sethiscore(hi2);
}

// END
void BoardCtrl::end() { }

void BoardCtrl::whoWin( int whoLose ) {
    view->end( board1, board2, whoLose );
}

// SPECIAL AECTION
bool BoardCtrl::specialAction( int i ) {
    std::shared_ptr<Board> opponent = whichOne( i+1 );
    while ( true ) {   // in case the client inputs invalid special action
        std::cout << "Choose a special action from 1. blind 2. heavy 3. force" << std::endl;
        std::string action;
        std::cin >> action;
        if ( action == "blind" ) {
            opponent->blind();
            return true;
        }
        if ( action == "heavy" ) {
            opponent->heavy();
            return true;
        }
        if ( action == "force" ) {
            std::cout << "Choose a type for your opponent's block" << std::endl;
            std::cout << "Enter one of I, J, L, O, S, Z, T" << std::endl;
            char type;
            std::cin >> type;
            while ( type != 'I' && type != 'J' && type != 'L' && type != 'O'
            && type != 'S' && type != 'Z' && type != 'T' ) std::cin >> type;

            return opponent->force( type );
            
        }
    }
}

// LEFT
void BoardCtrl::left(int i) {
    // determine which one to process
    std::shared_ptr<Board> processB = whichOne(i);
    // 1. move out first
    placeOut(i);
    processB->getCurrBlock()->left();

    // 2. Check wheter to move
    bool isMoveSucc = checkPlace(i);
    
    // 3. 判定 if movement is unsuccessful, turn back
    if (isMoveSucc == false) { 
        processB->getCurrBlock()->right();
        placeIn(i);
        return;
    }

    // 4. Place the block
    for ( int j = 0; j < processB->getCurrBlock()->levelHeavy; j++ ) {
        processB->getCurrBlock()->down();
        if ( ! checkPlace(i) ) {
            processB->getCurrBlock()->up();
            break;
        }
    }

    for ( int j = 0; j < processB->getCurrBlock()->specialHeavy; j++ ) {
        processB->getCurrBlock()->down();
        processB->getCurrBlock()->down();
        if ( ! checkPlace(i) ) {
            processB->getCurrBlock()->up();
            processB->getCurrBlock()->up();
            drop(i);
            break;
        }
    }
    placeIn(i);
}

// RIGHT
void BoardCtrl::right(int i) {
    std::shared_ptr<Board> processB = whichOne(i);
    placeOut(i);
    processB->getCurrBlock()->right();
    bool isMoveSucc = checkPlace(i);
    if (isMoveSucc == false) { 
        processB->getCurrBlock()->left();
        placeIn(i);
        return;
    }
    for ( int j = 0; j < processB->getCurrBlock()->levelHeavy; j++ ) {
        processB->getCurrBlock()->down();
        if ( ! checkPlace(i) ) {
            processB->getCurrBlock()->up();
            break;
        }
    }

    for ( int j = 0; j < processB->getCurrBlock()->specialHeavy; j++ ) {
        processB->getCurrBlock()->down();
        processB->getCurrBlock()->down();
        if ( ! checkPlace(i) ) {
            processB->getCurrBlock()->up();
            processB->getCurrBlock()->up();
            drop(i);
            break;
        }
    }
    placeIn(i);
}

// DOWN
bool BoardCtrl::down(int i) {
    std::shared_ptr<Board> processB = whichOne(i);
    placeOut(i);
    processB->getCurrBlock()->down();

    // 2. 检查 attemp to move, check wheter point is ok to move
    bool isMoveSucc = checkPlace(i);
    
    // 3. 判定 if movement is unsuccessful, turn back
    if (isMoveSucc == false) { 
        processB->getCurrBlock()->up();
        placeIn(i);
        return false;
    }
    
    for ( int i = 0; i < processB->getCurrBlock()->levelHeavy; i++ ) {
        processB->getCurrBlock()->down();
    }
    isMoveSucc = checkPlace(i);
    if (isMoveSucc == false) {
        for ( int i = 0; i < processB->getCurrBlock()->levelHeavy; i++ ) {
            processB->getCurrBlock()->up();
        }
        placeIn(i);
        return true;
    }
    placeIn(i);
    return isMoveSucc;
}

// DROP
void BoardCtrl::drop(int i) {
    bool keepdown = true;
    std::shared_ptr<Board> processB = whichOne(i);
    while (keepdown) {
        keepdown = down(i);
        view->displayText(copyctrl());
        //system("cls");
        //system("clear");
    }
    processB->unblind();
}

// rotateCW
void BoardCtrl::rotateCW(int i) {
    std::shared_ptr<Board> processB = whichOne(i);
    placeOut(i);
    processB->getCurrBlock()->rotateCW();
    bool isMoveSucc = checkPlace(i);
    
    // 3. 判定 if movement is unsuccessful, turn back
    if (isMoveSucc == false) { 
        processB->getCurrBlock()->rotateAW();
        placeIn(i);
        return;
    }
    for ( int i = 0; i < processB->getCurrBlock()->levelHeavy; i++ ) {
        processB->getCurrBlock()->down();
    }
    isMoveSucc = checkPlace(i);
    if (isMoveSucc == false) {
        for ( int i = 0; i < processB->getCurrBlock()->levelHeavy; i++ ) {
            processB->getCurrBlock()->up();
        }
    }
    placeIn(i);
}

// rotateAW
void BoardCtrl::rotateAW(int i) {
    std::shared_ptr<Board> processB = whichOne(i);
    placeOut(i);
    processB->getCurrBlock()->rotateAW();
    bool isMoveSucc = checkPlace(i);
    if (isMoveSucc == false) { 
        processB->getCurrBlock()->rotateCW();
        placeIn(i);
        return;
    }
    for ( int i = 0; i < processB->getCurrBlock()->levelHeavy; i++ ) {
        processB->getCurrBlock()->down();
    }
    isMoveSucc = checkPlace(i);
    if (isMoveSucc == false) {
        for ( int i = 0; i < processB->getCurrBlock()->levelHeavy; i++ ) {
            processB->getCurrBlock()->up();
        }
    }
    placeIn(i);
}

// levelUp
void BoardCtrl::levelUp(int i) {
    std::shared_ptr<Board> processB = whichOne(i);
    int lv = processB->level->getcurrlevel();
    if (lv >= 0 && lv < 4) {
        processB->level = processB->level->levelUp();
    }
}

// levelDown
void BoardCtrl::levelDown(int i) {
    std::shared_ptr<Board> processB = whichOne(i);
    int lv = processB->level->getcurrlevel();
    if (lv <= 4 && lv > 0) {
        processB->level = processB->level->levelDown();
    }
}

// get prefix for commands
int BoardCtrl::getPrefix( std::string cmd ) {
    int len = cmd.length();
    int count = 0;
    for ( ; count < len; count++ ) {
        if ( cmd[0] != '1' && cmd[0] != '2' && cmd[0] != '3' && cmd[0] != '4' &&  cmd[0] != '5' &&
             cmd[0] != '6' && cmd[0] != '7' && cmd[0] != '8' && cmd[0] != '9' ) {
            return 0;
        } else if ( cmd[count] == '0' || cmd[count] == '1' || cmd[count] == '2' || cmd[count] == '3' || cmd[count] == '4' ||  
                    cmd[count] == '5' || cmd[count] == '6' || cmd[count] == '7' || cmd[count] == '8' || cmd[count] == '9' ) {
            continue;
        } else {
            break;
        }
    }
    std::string prefix = cmd.substr(0, count);
    std::stringstream ss;
    int num;
    ss << prefix;
    ss >> num;
    return num;
}

// get new command
std::string BoardCtrl::getCommand( std::string cmd ) {
    int len = cmd.length();
    int count = 0;
    for ( ; count < len; count++ ) {
        if ( cmd[0] != '1' && cmd[0] != '2' && cmd[0] != '3' && cmd[0] != '4' &&  cmd[0] != '5' &&
             cmd[0] != '6' && cmd[0] != '7' && cmd[0] != '8' && cmd[0] != '9' ) {
            return 0;
        } else if ( cmd[count] == '0' || cmd[count] == '1' || cmd[count] == '2' || cmd[count] == '3' || cmd[count] == '4' ||  
                    cmd[count] == '5' || cmd[count] == '6' || cmd[count] == '7' || cmd[count] == '8' || cmd[count] == '9' ) {
            continue;
        } else {
            break;
        }
    }
    std::string newcmd = cmd.substr(count, len - count);
    return newcmd;
}

// check whether a cmd is in a command list
bool checkcmd(std::string s, std::string * sa, int len) {
    for (int i = 0; i < len; ++i) {
        if (s == sa[i]) {
            return true;
        }
    }
    return false;
}

// setInPut
void BoardCtrl::setInPut(int i, std::string filename) {
    std::string leftcmd[2] = {"lef", "left"};
    std::string rightcmd[4] = {"ri", "rig", "righ", "right"};
    std::string downcmd[3] = {"do", "dow", "down"};
    std::string CWcmd[8] = {"cl", "clo", "cloc", "clock", "clockw", "clockwi", "clockwis", "clockwise"};
    std::string AWcmd[15] = {"co", "cou", "coun", "count", "counte", "counter", "counterc", "countercl",
                            "counterclo", "countercloc", "counterclock", "counterclockw", "counterclockwi",
                            "counterclockwis", "counterclockwise"};
    std::string dropcmd[3] = {"dr", "dro", "drop"};
    std::string levelupcmd[2] = {"levelu", "levelup"};
    std::string leveldowncmd[4] = {"leveld", "leveldo", "leveldow", "leveldown"};
    std::string norandomcmd[8] = {"n", "no", "nor", "nora", "noran", "norand", "norando", "norandom"};
    std::string randomcmd[5] = {"ra", "ran", "rand", "rando", "random"};
    std::string sqcmd[8] = {"s", "se", "seq", "sequ", "seque", "sequen", "sequenc", "sequence"};
    std::string forcecmd[7] = {"I", "J", "L", "O", "S", "Z", "T"};
    std::string restartcmd[6] = {"re", "res", "rest", "resta", "restar", "restart"};
    std::string cmd;
    std::ifstream file(filename);
    int round = i;
    int time = 1;
    int count1 = 0;
    int count2 = 0;
    while (file >> cmd) {
        //system("cls");
        //system("clear");
        //std::cout << cmd << std::endl;
        //std::cout << getPrefix( cmd ) << std::endl;
        //std::cout << getCommand( cmd ) << std::endl;
        if ( getPrefix( cmd ) != 0 ) {
            time = getPrefix( cmd );
            cmd = getCommand( cmd );
        }
        if (checkcmd(cmd, leftcmd, 2)) {
            // TURN LEFT
            for ( int i = 0; i < time; i++ ) {
                left(round);
            }
            view->displayText(copyctrl());

        } else if (checkcmd(cmd, rightcmd, 4)) {
            // TURN RIGHT
            for ( int i = 0; i < time; i++ ) {
                right(round);
            }
            view->displayText(copyctrl());

        } else if (checkcmd(cmd, downcmd, 3)) {
            // GO DOWN
            for ( int i = 0; i < time; i++ ) {
                down(round);
            }
            view->displayText(copyctrl());

        } else if (checkcmd(cmd, dropcmd, 3)) {
            // DROP THE COURSE
            drop(round);
            int num_row = clear_and_calScore(round);
            NextRound(round);
            bool canPlace = checkPlace(round);
            if (!canPlace) { 
                int r = (round % 2 == 1)? 1 : 2;
                std::cout << "player " << r << " lose" << std::endl; 
                break;
            }
            int level1 = getboard1()->getLevel()->getcurrlevel();
            int level2 = getboard2()->getLevel()->getcurrlevel();
            if (round % 2 != 0) {
                check_star(round, count1, level1, num_row);
            }
            if (round % 2 == 0) {
                check_star(round, count2, level2, num_row);
            }
            placeIn(round + 2);
            view->displayText(copyctrl());
            round += 1;

        } else if (checkcmd(cmd, CWcmd, 8)) {
            // ROTATE CW
                
            for ( int i = 0; i < time; i++ ) {
                rotateCW(round);
            }
            view->displayText(copyctrl());

        } else if (checkcmd(cmd, AWcmd, 15)) {
            // ROTATE AW
            for ( int i = 0; i < time; i++ ) {
                rotateAW(round);
            }
            view->displayText(copyctrl());

        } else if (checkcmd(cmd, levelupcmd, 2)) {
            // LEVEL UP
            for ( int i = 0; i < time; i++ ) {
                levelUp(round);
            }
            view->displayText(copyctrl());

        } else if (checkcmd(cmd, leveldowncmd, 4)) {
            // LEVEL DOWN
            for ( int i = 0; i < time; i++ ) {
                levelDown(round);
            }
            view->displayText(copyctrl());

        } else if (checkcmd(cmd, norandomcmd, 8)) {
            std::string filename;
            std::cin >> filename;
            changerandom(round, filename, false);
            view->displayText(copyctrl());

        } else if (checkcmd(cmd, randomcmd, 5)) {
            changerandom(round, "", true);
            view->displayText(copyctrl());

        } else if (checkcmd(cmd, sqcmd, 5)) {
            std::cout << "Place give the file name:" << std::endl;
            std::string seq;
            std::cin >> seq;
            setInPut(round, seq);
            view->displayText(copyctrl());

        } else if (checkcmd(cmd, forcecmd, 7)) {
            char type = cmd[0];
            force( round, type );
        } else if (checkcmd(cmd, restartcmd, 6)) {
            restart();
        } else {
            view->displayText(copyctrl());
        }
        int rd = (round % 2 == 1)? 1 : 2;
        std::cout << std::endl << "player " << rd << "'s turn: " ;
        time = 1;
    }
}

// setNoRandom
void BoardCtrl::changerandom(int i, std::string filename, bool random) {
    std::shared_ptr<Board> processB = whichOne(i);
    int level = processB->getLevel()->getcurrlevel();
    if ( level < 3 ) return;
    processB->getLevel()->setFilename( filename );
    processB->getLevel()->setrandom(random);
}

// force
bool BoardCtrl::force( int i, char type ) {
    std::shared_ptr<Board> processB = whichOne(i);
    return processB->force( type );
}

// clear the row and update the score
int BoardCtrl::clear_and_calScore(int i) {
    std::shared_ptr<Board> processB = whichOne(i);
    int rowclear = processB->clearRow();
    processB->findBlock();
    if ( rowclear >= 2 ) {
        bool success = specialAction(i);
        if (success == false) {
            return -1;  // copyctrl() means that the action force is false to place
        }
    }
    return rowclear;
}

// getter for some fields
std::shared_ptr<Board> BoardCtrl::getboard1() {
    return board1;
}

std::shared_ptr<Board> BoardCtrl::getboard2() {
    return board2;
}

std::shared_ptr<BoardView> BoardCtrl::getview() {
    return view;
}


std::shared_ptr<BoardCtrl> BoardCtrl::copyctrl() {
    return std::make_shared<BoardCtrl>(*this);
}
