#ifndef _BOARDVIEW_H_
#define _BOARDVIEW_H_

#include "window.h"
#include <sstream>
#include <memory>
#include "board.h"
//#include "boardctrl.h"

class BoardCtrl;

class BoardView {
    bool textOnly;
    std::unique_ptr<Xwindow> xw;
public:
    BoardView(bool textOnly = false);
    void displayText(std::shared_ptr<BoardCtrl> b);
    void initialGp();
    bool isTextOnly();
    void fillCell(int whichBoard, int row, int col, int width, int height, int colour);
    void fillGp(std::shared_ptr<BoardCtrl> b);
    void displayNext(int, char);
    void display(std::shared_ptr<BoardCtrl> b);
    void end(std::shared_ptr<Board> board1, std::shared_ptr<Board> board2, int whoLose);
};

#endif
