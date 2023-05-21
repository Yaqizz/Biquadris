#include <iostream>
#include <fstream>
#include <vector>
#include "level.h"

Level::Level() {}
Level::~Level() {}

char Level::makeFromInput() {
    int len = blocks.size();
    if (curblock == len) curblock = 0;
    char block = blocks[curblock];
    curblock++;
    return block;
}

void Level::readFile() {
    char type;
    std::ifstream file(filename);
    while (file >> type) {
        blocks.emplace_back(type);
    }
}

int Level::getcurrlevel() {
    return curlevel;
}

void Level::setFilename( std::string fname ) {  
    filename = fname;
}

std::string Level::getFilename() {
    if (curlevel == 0) {
        return filename;
    }
    return "";
}

void Level::setrandom(bool random) {
    israndom = random;
    if (random == false) {
        blocks.clear();
        readFile();
        curblock = 0;
    }
}
