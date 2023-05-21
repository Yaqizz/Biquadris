#ifndef _LEVEL1_H_
#define _LEVEL1_H_
#include <memory>

#include "level.h"
#include "level0.h"
#include "level2.h"
extern int seed;

class Level1 : public Level {
    public:
    ~Level1();
    Level1(std::string filename = "");
    char makeBlock() override;
    std::shared_ptr<Level> levelUp() override;
    std::shared_ptr<Level> levelDown() override;
};

#endif
