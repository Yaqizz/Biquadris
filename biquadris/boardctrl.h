#ifndef _BOARDCTRL_H_
#define _BOARDCTRL_H_

#include "board.h"
#include <vector>
#include "pos.h"
#include "boardview.h"
#include <iostream>
#include <memory>

class BoardCtrl {
    std::shared_ptr<Board> board1;
    std::shared_ptr<Board> board2;
    std::shared_ptr<BoardView> view;
public:
    BoardCtrl( bool textOnly );
    ~BoardCtrl();
    
    // Helper function for movement
    std::shared_ptr<Board> whichOne(int);
    bool check(int, int, std::shared_ptr<Board>);
    void NextRound(int);

    bool checkPlace(int i);
    void placeIn(int i);
    void placeOut(int i);

    void check_star(int& round, int& count, int& level, int num_row);

    // Command Function
    void start(int lv, std::string fn1, std::string fn2);
    void restart();
    void end();
    bool specialAction(int);
    void left(int);
    void right(int);
    bool down(int);
    void drop(int);
    void rotateCW(int);
    void rotateAW(int);
    void levelUp(int);
    void levelDown(int);
    void setInPut(int, std::string);
    void changerandom(int, std::string, bool);
    bool force(int, char);

    // cal score
    int clear_and_calScore(int);

    void whoWin(int);

    int getPrefix(std::string);
    std::string getCommand(std::string);

    std::shared_ptr<Board> getboard1();
    std::shared_ptr<Board> getboard2();
    std::shared_ptr<BoardView> getview();
    std::shared_ptr<BoardCtrl> copyctrl();
};

#endif
