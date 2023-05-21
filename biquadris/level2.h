#ifndef _LEVEL2_H_
#define _LEVEL2_H_
#include <memory>

#include "level.h"
#include "level1.h"
#include "level3.h"
extern int seed;

class Level2 : public Level {
    public:
    ~Level2();
    Level2(std::string filename = "");
    char makeBlock() override;
    std::shared_ptr<Level> levelUp() override;
    std::shared_ptr<Level> levelDown() override;
};

#endif
