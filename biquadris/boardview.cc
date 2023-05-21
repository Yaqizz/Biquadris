#include "boardview.h"
#include "boardctrl.h"

const int row = 11;
const int col = 18;

BoardView::BoardView( bool textOnly ): textOnly{ textOnly }, xw{ nullptr } {
    if ( ! textOnly ) {
        initialGp();
    }
}

void BoardView::displayText( std::shared_ptr<BoardCtrl>b ) {
    std::shared_ptr<Board> board1 = b->getboard1();
    std::shared_ptr<Board> board2 = b->getboard2();
    std::vector<std::vector<std::shared_ptr<Pos>>> b1 =  board1->getCells();
    std::vector<std::vector<std::shared_ptr<Pos>>> b2 =  board2->getCells();
    std::cout << "Level:    " << board1->getLevel()->getcurrlevel();
    std::cout << "       Level:    " << board2->getLevel()->getcurrlevel() << std::endl;
    std::cout << "Score:    " << board1->getScore()->getcurrscore();
    std::cout << "       Score:    " << board2->getScore()->getcurrscore() << std::endl;
    std::cout << "Hi Score: " << board1->getScore()->gethiscore();
    std::cout << "       Hi Score: " << board2->getScore()->gethiscore() << std::endl;
    std::cout << "-----------       -----------" << std::endl;
    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 11; ++j) {
            if ( b1[i][j]->cover == '?' ) {
                std::cout << '?';
                continue;
            }
            std::cout << b1[i][j]->c;
        }
        std::cout << "       ";
        for (int j = 0; j < 11; ++j) {
            if ( b2[i][j]->cover == '?' ) {
                std::cout << '?';
                continue;
            }
            std::cout << b2[i][j]->c;
        }
        std::cout << std::endl; 
    }
    std::cout << "-----------       -----------" << std::endl;
    // print next block
    char next1[2][4] = {{' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}};
    char next2[2][4] = {{' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}};
    std::cout << "Next:             Next:" << std::endl;
    if (board1->getNextBlock() != nullptr){
        for (int i = 0; i < 4; i++){
            int pass = board1->getNextBlock()->pass.x;
            int x = board1->getNextBlock()->position[i].x - pass;
            int y = board1->getNextBlock()->position[i].y;
            next1[x][y] = board1->getNextBlock()->type;
        }
    }
    if (board2->getNextBlock() != nullptr){
        for (int i = 0; i < 4; i++){
            int pass = board1->getNextBlock()->pass.x;
            int x = board2->getNextBlock()->position[i].x - pass;
            int y = board2->getNextBlock()->position[i].y;
            next2[x][y] = board2->getNextBlock()->type;
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << next1[i][j];
        }
        std::cout << "              ";
        for (int k = 0; k < 4; k++) {
            std::cout << next2[i][k];
        }
        std::cout << std::endl;
    }
}

void BoardView::initialGp() {
    xw = std::make_unique<Xwindow>( 1030, 800 );
    xw->fillRectangle( 0, 0, 1030, 800, Xwindow::Black );
    xw->drawString( 480, 50, "Biquadris" );
    xw->drawString( 250, 100, "Board 1" );
    xw->drawString( 750, 100, "Board 2" );

    xw->drawString( 100, 140, "Level:" );
    xw->drawString( 240, 140, "Score:" );
    xw->drawString( 350, 140, "Hi Score:" );

    xw->drawString( 600, 140, "Level:" );
    xw->drawString( 740, 140, "Score:" );
    xw->drawString( 850, 140, "Hi Score:" );

    xw->drawString( 100, 700, "Next:" );
    xw->drawString( 600, 700, "Next:" );
    for ( int i = 0; i < row; i++ ) {
        for ( int j = 0; j < col; j++ ) {
            xw->fillRectangle( 100 + 30 * i, 150 + 30 * j, 25, 25 );
        }
    }
    for ( int i = 0; i < row; i++ ) {
        for ( int j = 0; j < col; j++ ) {
            xw->fillRectangle( 600 + 30 * i, 150 + 30 * j, 25, 25 );
        }
    }
}

bool BoardView::isTextOnly() {
    return textOnly;
}
void BoardView::fillCell( int whichBoard, int row, int col, int width, int height, int colour ) {
    if ( whichBoard == 1 ) {
        xw->fillRectangle( 100 + 30 * col, 150 + 30 * row, width, height, colour );
    } else {
        xw->fillRectangle( 600 + 30 * col, 150 + 30 * row, width, height, colour );
    }
}

std::string getStrNum( int num ) {
    std::string str;
    std::stringstream ss;
    ss << num;
    str = ss.str();
    return str;
}

void BoardView::displayNext( int whichBoard, char type ) {
    int colour;
    int init;
    if ( whichBoard == 1 ) {
        init = 200;
    } else {
        init = 700;
    }
    if ( type == 'I' ) {
        colour = Xwindow::Red;
        for ( int i = 0; i < 4; i++ ) {
            xw->fillRectangle( init + 30 * i, 720, 25, 25, colour );
        }
    }
    if ( type == 'J' ) {
        colour = Xwindow::Green;
        xw->fillRectangle( init, 720, 25, 25, colour );
        for ( int i = 0; i < 3; i++ ) {
            xw->fillRectangle( init + 30 * i, 750, 25, 25, colour );
        }
    }
    if ( type == 'L' ) {
        colour = Xwindow::Cyan;
        xw->fillRectangle( init + 60, 720, 25, 25, colour );
        for ( int i = 0; i < 3; i++ ) {
            xw->fillRectangle( init + 30 * i, 750, 25, 25, colour );
        }
    }
    if ( type == 'O' ) {
        colour = Xwindow::Yellow;
        for ( int i = 0; i < 2; i++ ) {
            xw->fillRectangle( init + 30 * i, 720, 25, 25, colour );
        }
        for ( int i = 0; i < 2; i++ ) {
            xw->fillRectangle( init + 30 * i, 750, 25, 25, colour );
        }
    }
    if ( type == 'S' ) {
        colour = Xwindow::Magenta;
        for ( int i = 1; i < 3; i++ ) {
            xw->fillRectangle( init + 30 * i, 720, 25, 25, colour );
        }
        for ( int i = 0; i < 2; i++ ) {
            xw->fillRectangle( init + 30 * i, 750, 25, 25, colour );
        }
    }
    if ( type == 'Z' ) {
        colour = Xwindow::Orange;
        for ( int i = 0; i < 2; i++ ) {
            xw->fillRectangle( init + 30 * i, 720, 25, 25, colour );
        }
        for ( int i = 1; i < 3; i++ ) {
            xw->fillRectangle( init + 30 * i, 750, 25, 25, colour );
        }
    }
    if ( type == 'T' ) {
        colour = Xwindow::Blue;
        for ( int i = 0; i < 3; i++ ) {
            xw->fillRectangle( init + 30 * i, 720, 25, 25, colour );
        }
        xw->fillRectangle( init + 30, 750, 25, 25, colour );
    }
}

void BoardView::fillGp( std::shared_ptr<BoardCtrl> b ) {
    std::shared_ptr<Board> board1 = b->getboard1();
    std::shared_ptr<Board> board2 = b->getboard2();
    std::vector<std::vector<std::shared_ptr<Pos>>> b1 = board1->getCells();
    std::vector<std::vector<std::shared_ptr<Pos>>> b2 = board2->getCells();
    int level1 = board1->getLevel()->getcurrlevel();
    int level2 = board2->getLevel()->getcurrlevel();
    int score1 = board1->getScore()->getcurrscore();
    int score2 = board2->getScore()->getcurrscore();
    int hiscore1 = board1->getScore()->gethiscore();
    int hiscore2 = board2->getScore()->gethiscore();
    std::string level1Str = getStrNum( level1 );
    std::string level2Str = getStrNum( level2 );
    std::string score1Str = getStrNum( score1 );
    std::string score2Str = getStrNum( score2 );
    std::string hiscore1Str = getStrNum( hiscore1 );
    std::string hiscore2Str = getStrNum( hiscore2 );
    xw->fillRectangle( 150, 125, 25, 25, Xwindow::Black );
    xw->fillRectangle( 290, 125, 25, 25, Xwindow::Black );
    xw->fillRectangle( 410, 125, 25, 25, Xwindow::Black );
    xw->fillRectangle( 650, 125, 25, 25, Xwindow::Black );
    xw->fillRectangle( 790, 125, 25, 25, Xwindow::Black );
    xw->fillRectangle( 910, 125, 25, 25, Xwindow::Black );

    xw->drawString( 150, 140, level1Str );
    xw->drawString( 290, 140, score1Str );
    xw->drawString( 410, 140, hiscore1Str );

    xw->drawString( 650, 140, level2Str );
    xw->drawString( 790, 140, score2Str );
    xw->drawString( 910, 140, hiscore2Str );
    char next1, next2;
    xw->fillRectangle( 180, 690, 200, 100, Xwindow::Black );
    xw->fillRectangle( 680, 690, 200, 100, Xwindow::Black );
    if (board1->getNextBlock() != nullptr){
        next1 = board1->getNextBlock()->type;
        displayNext( 1, next1 );
    }
    if (board2->getNextBlock() != nullptr){
        next2 = board2->getNextBlock()->type;
        displayNext( 2, next2 );
    }
    char type;
    int colour = Xwindow::Black;
    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 11; ++j) {
            type = b1[i][j]->c;
            if ( b1[i][j]->cover == '?' ) {
                fillCell( 1, i, j, 25, 25, Xwindow::Black );
                continue;
            }
            if ( type == ' ' ) colour = Xwindow::White;
            if ( type == 'I' ) colour = Xwindow::Red;
            if ( type == 'J' ) colour = Xwindow::Green;
            if ( type == 'L' ) colour = Xwindow::Cyan;
            if ( type == 'O' ) colour = Xwindow::Yellow;
            if ( type == 'S' ) colour = Xwindow::Magenta;
            if ( type == 'Z' ) colour = Xwindow::Orange;
            if ( type == 'T' ) colour = Xwindow::Blue;
            if ( type == '*' ) colour = Xwindow::Brown;
            fillCell( 1, i, j, 25, 25, colour );
        }
        for (int j = 0; j < 11; ++j) {
            type = b2[i][j]->c;
            if ( b2[i][j]->cover == '?' ) {
                fillCell( 2, i, j, 25, 25, Xwindow::Black );
                continue;
            }
            if ( type == ' ' ) colour = Xwindow::White;;
            if ( type == 'I' ) colour = Xwindow::Red;
            if ( type == 'J' ) colour = Xwindow::Green;
            if ( type == 'L' ) colour = Xwindow::Cyan;
            if ( type == 'O' ) colour = Xwindow::Yellow;
            if ( type == 'S' ) colour = Xwindow::Magenta;
            if ( type == 'Z' ) colour = Xwindow::Orange;
            if ( type == 'T' ) colour = Xwindow::Blue;
            if ( type == '*' ) colour = Xwindow::Brown;
            fillCell( 2, i, j, 25, 25, colour );
        }
    }
}

void BoardView::display( std::shared_ptr<BoardCtrl>b ) {
    if ( ! textOnly ) fillGp( b );
    displayText( b );
}

void BoardView::end( std::shared_ptr<Board> board1, std::shared_ptr<Board> board2, int whoLose ) {
    if ( textOnly ) return;
    std::string winner;
    int p1Score = board1->getScore()->gethiscore();
    int p2Score = board2->getScore()->gethiscore();
    xw->fillRectangle( 0, 0, 1030, 800, Xwindow::Black);
    if ( whoLose == 1 ) {
        winner = "Player 2 Wins!";
    } else if ( whoLose == 2 ) {
        winner = "Player 1 Wins!";
    } else {
        if( p1Score > p2Score ) {
            winner = "Player 1 Wins!";
        }
        else if( p1Score < p2Score ){
            winner = "Player 2 Wins!";
        }
        else{
            winner = "This is a Tie!";
        }
    }
    xw->drawString(440, 330, "Game Over!!!" ,Xwindow::Red);
    xw->drawString(400, 350, "Player 1 highest score:   " + getStrNum( p1Score ), Xwindow::White);
    xw->drawString(400, 370, "Player 2 highest score:   " + getStrNum( p2Score ), Xwindow::White);
    xw->drawString(440, 390, winner ,Xwindow::White);
}
