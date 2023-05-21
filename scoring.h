#ifndef _SCORING_H_
#define _SCORING_H_

class Scoring {
    int curr;
    int hi;
    int level;
public:
    Scoring(int level);
    void clearRow(int num); // num represents number of rows which are cleared
    void clearBlock(int blockLevel);
    void restart();
    int getcurrscore();
    int gethiscore();
    void sethiscore(int hi);
    void addscore(int);
};

#endif

