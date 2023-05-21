#ifndef _LEVEL3_H_
#define _LEVEL3_H_
#include <memory>

#include "level.h"
#include "level2.h"
#include "level4.h"
extern int seed;

class Level3 : public Level {
    public:
    ~Level3();
    Level3(std::string filename = "");
    char makeBlock() override;
    std::shared_ptr<Level> levelUp() override;
    std::shared_ptr<Level> levelDown() override;
};

#endif
