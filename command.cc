#include "command.h"
#include <iostream>
#include <string>
using namespace std;

void Command::renamecmd(string oldcmd, string newcmd) {
    try{
        this->check(oldcmd);
    } catch(int) {
        return;
    }
    if (oldcmd == left) {
        left = newcmd;
    } else if (oldcmd == right) {
        right = newcmd;
    } else if (oldcmd == down) {
        down = newcmd;
    } else if (oldcmd == drop) {
        drop = newcmd;
    } else if (oldcmd == levelup) {
        levelup = newcmd;
    } else if (oldcmd == leveldown) {
        leveldown = newcmd;
    } else if (oldcmd == clockwise) {
        clockwise = newcmd;
    } else if (oldcmd == counterclockwise) {
        counterclockwise = newcmd;
    }
    return;
}


void Command::check(string &cmd) {
    bool exist = false;
    string oricmd = cmd;
    for (unsigned int i = 1; i < left.length(); i++) {
        if (oricmd == left.substr(0, i)) {
            exist = true;
            cmd = left;
            break;
        }
    }
    for (unsigned int i = 1; i < right.length(); i++) {
        if (oricmd == right.substr(0, i)) {
            if (exist) {
                cmd = oricmd;
                throw 1;
            } else {
                exist = true;
                cmd = right;
                break;
            }
        }
    }
    for (unsigned int i = 1; i < down.length(); i++) {
        if (oricmd == down.substr(0, i)) {
            if (exist) {
                cmd = oricmd;
                throw 1;
            } else {
                exist = true;
                cmd = down;
                break;
            }
        }
    }
    for (unsigned int i = 1; i < drop.length(); i++) {
        if (oricmd == drop.substr(0, i)) {
            if (exist) {
                cmd = oricmd;
                throw 1;
            } else {
                exist = true;
                cmd = drop;
                break;
            }
        }
    }
    for (unsigned int i = 1; i < levelup.length(); i++) {
        if (oricmd == levelup.substr(0, i)) {
            if (exist) {
                cmd = oricmd;
                throw 1;
            } else {
                exist = true;
                cmd = levelup;
                break;
            }
        }
    }
    for (unsigned int i = 1; i < leveldown.length(); i++) {
        if (oricmd == leveldown.substr(0, i)) {
            if (exist) {
                cmd = oricmd;
                throw 1;
            } else {
                exist = true;
                cmd = leveldown;
                break;
            }
        }
    }
    for (unsigned int i = 1; i < clockwise.length(); i++) {
        if (oricmd == clockwise.substr(0, i)) {
            if (exist) {
                cmd = oricmd;
                throw 1;
            } else {
                exist = true;
                cmd = clockwise;
                break;
            }
        }
    }
    for (unsigned int i = 1; i < counterclockwise.length(); i++) {
        if (oricmd == counterclockwise.substr(0, i)) {
            if (exist) {
                cmd = oricmd;
                throw 1;
            } else {
                exist = true;
                cmd = counterclockwise;
                break;
            }
        }
    }
}

string Command::getleft() {
    return left;
}

string Command::getright() {
    return right;
}

string Command::getdown() {
    return down;
}

string Command::getdrop() {
    return drop;
}

string Command::getlevelup() {
    return levelup;
}

string Command::getleveldown() {
    return leveldown;
}

string Command::getclockwise() {
    return clockwise;
}

string Command::getcounterclockwise() {
    return counterclockwise;
}
