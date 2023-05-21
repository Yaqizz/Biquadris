#ifndef _LEVEL0_H_
#define _LEVEL0_H_
#include <memory>

#include "level.h"
#include "level1.h"

extern int seed;

class Level0 : public Level {
    public:
    ~Level0();
    Level0(std::string filename = "");
    char makeBlock() override;
    std::shared_ptr<Level> levelUp() override;
    std::shared_ptr<Level> levelDown() override;
};

#endif
