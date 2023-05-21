#include "scoring.h"
#include <iostream>

Scoring::Scoring( int level ): curr{ 0 }, hi{ 0 }, level{ level } { }

void Scoring::clearRow( int num ) {
    int score = ( level + num ) * ( level + num );
    curr += score;
    if ( curr > hi ) hi = curr;
}

void Scoring::clearBlock( int blockLevel ) {
    int score = ( blockLevel + 1 ) * ( blockLevel + 1 );
    curr += score;
    if ( curr > hi ) hi = curr;
}

void Scoring::restart() {
    curr = 0;
}

int Scoring::getcurrscore() { return curr; }

void Scoring::addscore(int i) {
    curr += i;
    if (curr > hi) {
        hi = curr;
    }
}

int Scoring::gethiscore() {
    return hi;
}

void Scoring::sethiscore(int h) {
    this->hi = h;
}
