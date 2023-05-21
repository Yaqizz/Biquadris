#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <string>
#include <vector>
#include <memory>

extern int seed;

class Level {
protected:
    int curlevel;
    int curblock;
    int count;
    bool israndom;
    std::string filename;
    std::vector<char> blocks;

public:
    Level();
    virtual ~Level() = 0;
    virtual std::shared_ptr<Level> levelUp() = 0;
    virtual std::shared_ptr<Level> levelDown() = 0;
    virtual char makeBlock() = 0;
    char makeFromInput();
    void readFile();
    int getcurrlevel();
    void setFilename(std::string);
    void setrandom(bool random);
    std::string getFilename();
};

#endif
