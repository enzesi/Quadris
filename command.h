#ifndef COMMAND_H
#define COMMAND_H
#include <string>


class Command{
    std::string left = "left";
    std::string right = "right";
    std::string down = "down";
    std::string drop = "drop";
    std::string levelup = "levelup";
    std::string leveldown = "leveldown";
    std::string clockwise = "clockwise";
    std::string counterclockwise = "counterclockwise";
public:
    void renamecmd(std::string oddcmd, std::string newcmd);
    std::string getleft();
    std::string getright();
    std::string getdown();
    std::string getdrop();
    std::string getlevelup();
    std::string getleveldown();
    std::string getclockwise();
    std::string getcounterclockwise();
    void check(std::string &);
};



#endif
