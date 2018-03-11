#ifndef LEVEL_H
#define LEVEL_H
#include <memory>
#include "block.h"
#include <fstream>
#include <cstdlib>


class Level {
    int level;
    std::string file;
    bool start = false;
    char now = ' ';
    char next = ' ';
    
public:
    Level(int level, std::string file, bool seedexist, int seed);
    void levelup(int times = 1);
    void leveldown(int times = 1);
    Block generateBlock(std::shared_ptr<Board> b, int ith, int &pos, bool random34 = false,
                        std::string file = "");
    int getlevel() ;
    void setlevel(int level);
    void display_next();
    char getnext();
    
};



#endif
