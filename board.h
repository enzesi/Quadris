#ifndef BOARD_H_
#define BOARD_H_
#include <iostream>
#include "posn.h"
#include "cell.h"
#include <vector>
#include <iomanip>
#include "textdisplay.h"

class Board {
    std::vector<std::vector<Cell>> theBoard;
    TextDisplay *td = nullptr;
    Observer *ob = nullptr;
    int level = 0;
    int score = 0;
    int Hi_Score = 0;;
public:
    ~Board();
    void init();
    bool check(std::vector<Posn> p);
    void clear(std::vector<Posn> p);
    void set(std::vector<Posn> p, char type);
    void setith(std::vector<Posn> p, int ith);
    void setlevel(int level);
    void addScore(int x);
    void setObserver(Observer *ob);
    void Remove(int ith);
///////////////////////////
    void checkHiScore();
    int getHiscore();
    void setHiScore(int x);
///////////////////////////
    std::vector<int> *clean();
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};




#endif
