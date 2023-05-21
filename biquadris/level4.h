#ifndef _LEVEL4_H_
#define _LEVEL4_H_
#include <memory>

#include "level.h"
#include "level3.h"
extern int seed;

class Level4 : public Level {
    public:
    ~Level4();
    Level4(std::string filename = "");
    char makeBlock() override;
    std::shared_ptr<Level> levelUp() override;
    std::shared_ptr<Level> levelDown() override;
};

#endif
