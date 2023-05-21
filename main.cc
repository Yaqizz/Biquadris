#include <iostream>
#include <string>
#include <sstream>
#include "block.h"
#include "blockJ.h"
#include "level.h"
#include "boardctrl.h"
#include "board.h"
#include "boardview.h"
#include <string>

int seed;

// ======= HELPER FUNCTION ===========================================

// find the len of a char []
int my_strlen(const char *s) {
    int len = 0;
    while (s[len]) {
        ++len;
    }
    return len;
}

// compare whether the two char * are the same
int my_strcmp(const char s1[], const char s2[]) {
    int i = 0;
    while (s1[i] == s2[i] && s1[i]) {
        ++i;
    }
    return s1[i] - s2[i];
}

// transfer a char * to int
int s_to_i(std::string s, int len) {
    int value = 0;
    int digit = 1;
    for (int i = len - 1; i >= 0; --i) {
        if (s[i] == '-') {
            value = 0 - value;
        } else {
            value += digit * (s[i] - '0');
            digit *= 10;
        }
    } 
    return value;
}

// check whether a cmd is in a command list
bool check(std::string s, std::string * sa, int len) {
    for (int i = 0; i < len; ++i) {
        if (s == sa[i]) {
            return true;
        }
    }
    return false;
}

// get prefix for commands
int getPrefix( std::string cmd ) {
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
std::string getCommand( std::string cmd ) {
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

void help_display() {
    std::cout << "*------------------------------------------*" << std::endl;
    std::cout << "All commands: " << std::endl;
    std::cout << "reft: move the current block to the left" << std::endl;
    std::cout << std::endl;
    std::cout << "right: move the current block to the right" << std::endl;
    std::cout << std::endl;
    std::cout << "down: move the current block downward" << std::endl;
    std::cout << std::endl;
    std::cout << "drop: drop the current block" << std::endl;
    std::cout << std::endl;
    std::cout << "clockwise: rotates the block 90 degrees clockwise" << std::endl;
    std::cout << std::endl;
    std::cout << "counterclockwise: rotates the block 90 degrees counterclockwise" << std::endl;
    std::cout << std::endl;
    std::cout << "levelup: increases the current level by one" << std::endl;
    std::cout << std::endl;
    std::cout << "leveldown: decreases the current level by one" << std::endl;
    std::cout << std::endl;
    std::cout << "norandom file: in levels 3 and 4, taking input from the sequence file" << std::endl;
    std::cout << std::endl;
    std::cout << "random file: in levels 3 and 4, taking input randomly" << std::endl;
    std::cout << std::endl;
    std::cout << "sequence file: executes the sequence of commands in file" << std::endl;
    std::cout << std::endl;
    std::cout << "I, J, L, O, S, Z, T: changes the current undropped block" << std::endl;
    std::cout << std::endl;
    std::cout << "restart: clears the board and starts a new game" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Special actions: " << std::endl;
    std::cout << "If a player, upon dropping a block, clears two or more rows simultaneously, a special action is triggered" << std::endl;
    std::cout << std::endl;
    std::cout << "blind: let the opponent’s board, from columns 3-9, and from rows 3-12, is covered with question marks (?), until the player drops a block" << std::endl;
    std::cout << std::endl;
    std::cout << "heavy: every time a player moves a block left or right, the block automatically falls by two rows" << std::endl;
    std::cout << std::endl;
    std::cout << "force block: change the opponent’s current block to block" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Levels: " << std::endl;
    std::cout << "Level 0: " << std::endl;
    std::cout << "Takes blocks in sequence from the files sequence1.txt (for player 1) and sequence2.txt (for player 2)" << std::endl;
    std::cout << "Level 1: " << std::endl;
    std::cout << "The block selector will randomly choose a block. Block S and Z are selected with probability 1/12 each, and the other blocks are selected with probability 1/6 each" << std::endl;
    std::cout << "Level 2:" << std::endl;
    std::cout << "All blocks are selected with equal probability" << std::endl;
    std::cout << "Level 3:" << std::endl;
    std::cout << "The block selector will randomly choose a block. Block S and Z are selected with probability 2/9 each, and the other blocks are selected with probability 1/9 each" << std::endl;
    std::cout << "Every command to move or rotate the block will be followed immediately and automatically by a downward move of one row" << std::endl;
    std::cout << "Level 4:" << std::endl;
    std::cout << "In addition to the rules of Level 3, in Level 4, every time you place 5 blocks without clearing at least one row, a 1x1 block is dropped onto your game board in the centre column" << std::endl;
    std::cout << "*------------------------------------------*" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

}




// ============== MAIN FUNCTION ===============================================

int main(int argc, const char *argv[]) {

    // --------------- Some set up from Command-line Interface --------------
    bool textOnly = false;
    int currlevel = 0;
    std::string filename1 = "sequence1.txt";
    std::string filename2 = "sequence2.txt";
    // this area can be add by command-line interface
    for (int i = 1; i < argc; ++i) {
        std::string command = argv[i];
        if (command == "-text") {
            // no graph display./biquadris -text -seed 1219 -scriptfile1 JUDE -scriptfile2 XH -startlevel 3
            textOnly = true;
        } else if (command == "-seed") {
            i += 1;
            std::string seed_value = argv[i];
            int seed_len = seed_value.length();
            seed = s_to_i(seed_value, seed_len);
            srand(seed);
            // set seed for some function
        } else if (command == "-scriptfile1") {
            i += 1;
            filename1 = argv[i];
        } else if (command == "-scriptfile2") {
            i += 1;
            filename2 = argv[i];
        } else if (command == "-startlevel") {
            i += 1;
            std::string level_value = argv[i];
            filename1 = "";
            filename2 = "";
            int level_length = level_value.length();
            currlevel = s_to_i(level_value, level_length);
            if (currlevel < 0) {
                currlevel = 0;
            } else if (currlevel > 4) {
                currlevel = 4;
            }
        } else if (command == "-help") {
            help_display();
        }
    }



    // --------------- Tell the players about the gamer setting ---------------- 
    std::cout << "*------------------------------------------*" << std::endl;
    // print information for asseration 这里的print这么难看，原因是为了居中对齐
    if (! textOnly) {
        std::cout << "    Graphics and text will be displayed" << std::endl;
    } else {
        std::cout << "        Only text will be displayed" << std::endl;
    }
    std::cout << "            The seed is " << seed << std::endl;
    std::cout << "         The current level is " << currlevel << std::endl;
    std::cout << "    The files for player 1 is " << filename1 << std::endl;
    std::cout << "    The files for player 2 is " << filename2 << std::endl;
    std::cout << "*------------------------------------------*" << std::endl;
    
    char c;
    std::cout << "Are your ready? Please type any key to start / or type q to quit ";
    std::cin >> c;
    if (c == 'q') {
        std::cout << "You success fully quit the game" << std::endl;
        return 0;
    }
    std::cout << "Enjoy your Games" << std::endl << std::endl;
    


    // ------------------------- All set of Commands -----------------------------------------

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

    // -------------------- Start Game & Enter (Basic) Commands -----------------------
    
    bool restart_game = true;
    int count1 = 0;
    int count2 = 0;
    while (restart_game) {
        // will not restart game unless some action does
        restart_game = false; 
        // creat a empty control board and initialize it
        std::shared_ptr<BoardCtrl> bt = std::make_shared<BoardCtrl>( textOnly );
        bt->start(currlevel, filename1, filename2);
        int round = 1;
        bt->placeIn(round);
        bt->placeIn(round + 1);
        bt->getview()->display( bt );
        int rd = (round % 2 == 1)? 1 : 2;
        std::cout << std::endl << "player " << rd << "'s turn: ";
        std::string cmd;
        int time = 1;
        int whoLose = 0;
        while (std::cin >> cmd) {
            //system("cls");
            //system("clear");
            //std::cout << cmd << std::endl;
            //std::cout << getPrefix( cmd ) << std::endl;
            //std::cout << getCommand( cmd ) << std::endl;
            if ( getPrefix( cmd ) != 0 ) {
                time = getPrefix( cmd );
                cmd = getCommand( cmd );
            }
            if (check(cmd, leftcmd, 2)) {
                // TURN LEFT
                for ( int i = 0; i < time; i++ ) {
                    bt->left(round);
                }
                bt->getview()->display( bt );
            } else if (check(cmd, rightcmd, 4)) {
                // TURN RIGHT
                for ( int i = 0; i < time; i++ ) {
                    bt->right(round);
                }
                bt->getview()->display( bt );

            } else if (check(cmd, downcmd, 3)) {
                // GO DOWN
                for ( int i = 0; i < time; i++ ) {
                    bt->down(round);
                }
                bt->getview()->display( bt );

            } else if (check(cmd, dropcmd, 3)) {
                // DROP THE COURSE
                bt->drop(round);
                int num_row = bt->clear_and_calScore(round);
                if (num_row == -1) {
                    int r = (round % 2 == 1)? 2 : 1;
                    std::cout << "player " << r << " lose" << std::endl;
                    whoLose = r;
                    break;
                }
                bt->NextRound(round);
                bool canPlace = bt->checkPlace(round);
                if (!canPlace) { 
                    int r = (round % 2 == 1)? 1 : 2;
                    std::cout << "player " << r << " lose" << std::endl; 
                    whoLose = r;
                    break;
                }
                int level1 = bt->getboard1()->getLevel()->getcurrlevel();
                int level2 = bt->getboard2()->getLevel()->getcurrlevel();
                if (round % 2 != 0) {
                    bt->check_star(round, count1, level1, num_row);
                }
                if (round % 2 == 0) {
                    bt->check_star(round, count2, level2, num_row);
                }
                bt->placeIn(round + 2);
                bt->getview()->display( bt );
                round += 1;
            } else if (check(cmd, CWcmd, 8)) {
                // ROTATE CW
                
                for ( int i = 0; i < time; i++ ) {
                    bt->rotateCW(round);
                }
                bt->getview()->display( bt );

            } else if (check(cmd, AWcmd, 15)) {
                // ROTATE AW
                for ( int i = 0; i < time; i++ ) {
                    bt->rotateAW(round);
                }
                bt->getview()->display( bt );

            } else if (check(cmd, levelupcmd, 2)) {
                // LEVEL UP
                for ( int i = 0; i < time; i++ ) {
                    bt->levelUp(round);
                }
                bt->getview()->display( bt );

            } else if (check(cmd, leveldowncmd, 4)) {
                // LEVEL DOWN
                for ( int i = 0; i < time; i++ ) {
                    bt->levelDown(round);
                }
                bt->getview()->display( bt );

            } else if (check(cmd, norandomcmd, 8)) {
                std::cout << "Place give the file name:" << std::endl;
                std::string filename;
                std::cin >> filename;
                bt->changerandom(round, filename, false);
                bt->getview()->display( bt );

            } else if (check(cmd, randomcmd, 5)) {
                bt->changerandom(round, "", true);
                bt->getview()->display( bt );

            } else if (check(cmd, sqcmd, 5)) {
                std::string seq;
                std::cin >> seq;
                bt->setInPut(round, seq);
                bt->getview()->display( bt );

            } else if (check(cmd, forcecmd, 7)) {
                char type = cmd[0];
                if (bt->force( round, type )) {
                    bt->getview()->display( bt );
                } else {
                    std::cout << "There is not enough space to place, please move around" << std::endl;
                }
            } else if (check(cmd, restartcmd, 6)) {
                bt->restart();
                round = 1;
                bt->placeIn(round);
                bt->placeIn(round + 1);
                bt->getview()->display( bt );
                restart_game = false;
            } else {
                bt->getview()->display( bt );
            }
            int rd = (round % 2 == 1)? 1 : 2;
            std::cout << std::endl << "player " << rd << "'s turn: " ;
            time = 1;
        }
        // end and destroy every thing
        bt->whoWin( whoLose );
        std::cout << "Press any key to exit the game" << std::endl;
        char c;
        std::cin >> c;
        bt->end();
    }
    std::cout << "END of Games" << std::endl << std::endl;
}
