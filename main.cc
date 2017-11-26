#include <iostream>
#include "textdisplay.h"
#include "board.h"
#include "subject.h"
#include "observer.h"
#include "posn.h"
#include "info.h"
#include "block.h"
#include "blockinfo.h"
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <fstream>
using namespace std;


void display_next(char now_displaying) {
    cout << "Next:" << endl;
    if (now_displaying == 'I') {
        cout << "IIII" << endl;
    }
    else if (now_displaying == 'J') {
        cout << "J" << endl;
        cout << "JJJ" << endl;
    }
    else if (now_displaying == 'L') {
        cout << "  L" << endl;
        cout << "LLL" << endl;
    }
    else if (now_displaying == 'O') {
        cout << "OO" << endl;
        cout << "OO" << endl;
    }
    else if (now_displaying == 'S') {
        cout << " SS" << endl;
        cout << "SS" << endl;
    }
    else if (now_displaying == 'Z') {
        cout << "ZZ" << endl;
        cout << " ZZ" << endl;
    }
    else if (now_displaying == 'T') {
        cout << "TTT" << endl;
        cout << " T " << endl;
    }
}


void set_level(int level, int &pos, bool &start, char &now,
               char &next, const string file = "sequence.txt") {
    if (level == 0) {
        ifstream f(file);
        char c;
        vector<char> char_vec;
        char_vec.clear();
        while (f >> c) {
            if (c == 'T' || c == 'S' || c == 'L' || c == 'O' || c == 'J' || c == 'Z' || c == 'I') {
                char_vec.push_back(c);
            }
        }
        int size = char_vec.size();
        if (start == false) {
            now = char_vec[pos];
            if (pos == size - 1) {
                pos = 0;
                next = char_vec[pos];
            } else {
                next = char_vec[pos + 1];
            }
            start = true;
            pos++;
        }
        else {
            if (pos >= size - 1) {
                now = next;
                next = char_vec[0];
                pos = 0;
            } else {
                now = next;
                pos++;
                next = char_vec[pos];
            }
        }
    }
    else if (level == 1) {
        char char_vec[] = {'S','Z','I','I','T','T','J','J','L','L','O','O'};
        srand(time(NULL));
        rand();
        int poss = rand() % 12;
        if (start == false) {
            now = char_vec[poss];
            poss = rand() % 12;
            next = char_vec[poss];
            start = true;
        } else {
            now = next;
            poss = rand() % 12;
            next = char_vec[poss];
        }
    }
    else if (level == 2) {
        char char_vec[] = {'S','Z','I','T','J','L','O'};
        srand(time(NULL));
        rand();
        int poss = rand() % 6;
        if (start == false) {
            now = char_vec[poss];
            poss = rand() % 6;
            next = char_vec[poss];
            start = true;
        }
        else {
            now = next;
            next = char_vec[poss];
        }
    }
    else if (level == 3 || level == 4) {
        char char_vec[] = {'S','Z','I','T','J','L','O','S','Z'};
        srand(time(NULL));
        rand();
        int poss = rand() % 9;
        if (start == false) {
            now = char_vec[poss];
            poss = rand() % 9;
            next = char_vec[poss];
            start = true;
        }
        else {
            now = next;
            next = char_vec[poss];
        }
    }
}

int main(int argc, char *argv[]) {
    string cmd;
    vector<BlockInfo> binfo;
    binfo.clear();
    vector<int> * v = nullptr;
    int ith = 0;    // use for score;
    Board *b;
    b = new Board;
    b->init();
    
    int start_level;
    cin >> start_level;
    int level = start_level;
    b->setlevel(level);
    bool start = false;
    int pos = 0;
    char now;
    char next;
    bool complete;
    while (true) {
        
        int curr_level = level;
        set_level(level, pos, start, now, next);
        Block currb(now, b, ith);
        cout << (*b);
        display_next(next);
        while (1) {
            cin >> cmd;
            if (((cmd == "T" || cmd == "S") || (cmd == "L" || cmd == "O")) ||
                ((cmd == "J" || cmd == "Z") || cmd == "I")) {
                now = cmd[0];
                currb.clean();
                currb = Block(now, b, ith);
                cout << (*b);
                display_next(next);
            } else {
                complete = true;
                break;
            }
        }
        binfo.push_back(BlockInfo {4, level, true});
        ith++;
        
        
        while (complete || cin >> cmd) {
            complete = false;
            if (cmd == "r") {
                currb.right();
                if (level == 3 || level == 4) {
                    currb.down();
                }
                cout << (*b);
                display_next(next);
            } else if (cmd == "l") {
                currb.left();
                if (level == 3 || level == 4) {
                    currb.down();
                }
                cout << (*b);
                display_next(next);
            } else if (cmd == "d") {
                currb.down();
                if (level == 3 || level == 4) {
                    currb.down();
                }
                cout << (*b);
                display_next(next);
            } else if (cmd == "p") {
                currb.drop();
                v = b->clean();
                int size = v->size();
                for (int i = 0; i < size; i++) {
                    int k = v->at(i);
                    binfo[k].count--;
                }
                delete v;
                for (int i = 0; i < ith; i++) {
                    if (binfo[i].cal) {
                        if (binfo[i].count == 0) {
                            int sco = binfo[i].level + 1;
                            b->addScore(sco * sco);
                            binfo[i].cal = false;
                        }
                    }
                }
                if (curr_level != level) {
                    level = curr_level;
                    b->setlevel(level);
                    if (level == 0) {
                        pos = -1;
                    }
                }
                break;
            } else if (cmd == "cr") {
                currb.clockwise();
                if (level == 3 || level == 4) {
                    currb.down();
                }
                cout << (*b);
                display_next(next);
            } else if (cmd == "ccr") {
                currb.countclockwise();
                if (level == 3 || level == 4) {
                    currb.down();
                }
                cout << (*b);
                display_next(next);
            } else if (cmd == "levelup") {
                if (curr_level == 4) {
                    continue;
                } else {
                    curr_level++;
                }
            } else if (cmd == "leveldown") {
                if (curr_level == 0) {
                    continue;
                } else {
                    curr_level--;
                }
            } else if (cmd == "q") {
                break;
            } else {
                continue;
            }
        }
    }
}
