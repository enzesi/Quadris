#include "board.h"
#include <iostream>
using namespace std;


Board::~Board(){}

void Board::reset() {
    theBoard.clear();
    score = 0;
}

int Board::getScore() {
    return score;
}

void Board::deletehint(vector<Posn> p) { // clean the hint temporarily;
    for (int i = 0; i < 4; i++) {
        Info info = theBoard[p[i].x][p[i].y].getInfo();
        if (info.type == '?') {
            theBoard[p[i].x][p[i].y].settype(' ');
        }
    }
}


int Board::getEmpty(int line) {
    int x = 0;
    for (int i = 0; i < 11; i++) {
        if (theBoard[line][i].getInfo().empty) {
            x++;
        }
    }
    return x;
}

void Board::init() {
    int size = theBoard.size();
    if (size != 0) {
        theBoard.clear();
    }
    td = make_shared<TextDisplay>();// set all the cell properly;
    for (int i = 0; i < 18; i++) {
        vector <Cell> c;
        for (int j = 0; j < 11; j++) {
            Cell newC(i, j);
            newC.attach(td);
            c.push_back(newC);
        }
        theBoard.push_back(c);
    }
}

void Board::setObserver(shared_ptr<Observer> ob) { // set the graphicsdisplay
    for (int i = 0; i < 18; i++) {                 // to every cell;
        for (int j = 0; j < 11; j++) {
            theBoard[i][j].attach(ob);
        }
    }
    this->ob = ob;
}

bool Board::check(vector<Posn> p) {
    if(p.size() == 1) {
        return (theBoard[p[0].x][p[0].y].getempty());
    }
    if (((theBoard[p[0].x][p[0].y].getempty() &&
          theBoard[p[1].x][p[1].y].getempty()) &&
         theBoard[p[2].x][p[2].y].getempty()) &&
        theBoard[p[3].x][p[3].y].getempty()) {
        return true;
    } else {
        return false;
    }
}

void Board::clear(vector<Posn> p) {
    if(p.size() == 1) {
        theBoard[p[0].x][p[0].y].setempty(true);
        return;
    }
    for (int i = 0; i < 4; i++) {
        theBoard[p[i].x][p[i].y].setempty(true);
    }
}

void Board::tempclean(vector<Posn> p) {
    if(p.size() == 1) {
        theBoard[p[0].x][p[0].y].cleartemp();
        return;
    }
    for (int i = 0; i < 4; i++) {
        theBoard[p[i].x][p[i].y].cleartemp();
    }
}

void Board::setback(std::vector<Posn> p) {
    for (int i = 0; i < 4; i++) {
        theBoard[p[i].x][p[i].y].setempty(false);
    }
}

bool Board::checkempty(Posn p) {
    return theBoard[p.x][p.y].getempty();
}

void Board::set(std::vector<Posn> p, char type) {
    if(p.size() == 1) {
        theBoard[p[0].x][p[0].y].setempty(false);
        theBoard[p[0].x][p[0].y].settype(type);
        return;
    }
    if (type == '?') {
        if (theBoard[p[0].x][p[0].y].getempty()){
            theBoard[p[0].x][p[0].y].settype(type);
        }
        if (theBoard[p[1].x][p[1].y].getempty()){
            theBoard[p[1].x][p[1].y].settype(type);
        }
        if (theBoard[p[2].x][p[2].y].getempty()){
            theBoard[p[2].x][p[2].y].settype(type);
        }
        
        if (theBoard[p[3].x][p[3].y].getempty()){
            theBoard[p[3].x][p[3].y].settype(type);
        }
        return;
    }
    for (int i = 0; i < 4; i++) {
        theBoard[p[i].x][p[i].y].setempty(false);
        theBoard[p[i].x][p[i].y].settype(type);
    }
}

void Board::setith(std::vector<Posn> p, int ith) {
    if (p.size() == 1) return;
    for (int i = 0; i < 4; i++) {
        theBoard[p[i].x][p[i].y].setith(ith);
    }
}

void Board::addScore(int x) {
    score += x;
}

void Board::setlevel(int level) {
    this->level = level;
}

void Board::checkHiScore() {
    if(Hi_Score < score) {
        Hi_Score = score;
    }
}

void Board::Remove(int ith) {
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 11; j++) {
            Info info = theBoard[i][j].getInfo();
            if (info.ith == ith) {
                theBoard[i][j].setempty(true);
            }
        }
    }
}

int Board::getHiscore() {
    return Hi_Score;
}

void Board::setHiScore(int x) {
    Hi_Score = x;
}

unique_ptr<vector<int>> Board::clean() {
    unique_ptr<vector<int>> v;
    v = make_unique<vector<int>>();
    int lines = 0;
    for (int i = 17; i >= 0; i--) {
        bool full = true;
        for (int j = 0; j < 11; j++) {
            Info info = theBoard[i][j].getInfo();
            if (info.empty) {
                full = false;
                break;
            }
        }
        if (full) {
            lines++;
            for (int j = 0; j < 11; j++) {
                Info info = theBoard[i][j].getInfo();
                v->push_back(info.ith);
            }
            for (int k = i; k >= 1; k--) {
                for (int h = 0; h < 11; h++) {
                    Info info = theBoard[k-1][h].getInfo();
                    theBoard[k][h].setith(info.ith);
                    theBoard[k][h].setempty(info.empty);
                    if (!info.empty) {
                        theBoard[k][h].settype(info.type);
                    }
                }
            }
            i++;
        }
    }
    if (lines != 0) {
        score += (lines + level) * (lines + level);
    }
    return v;
}

std::ostream &operator<<(std::ostream &out, const Board &b) {
    out << "Level:" << setw(7)<< b.level << endl;
    out << "Score:" << setw(7) << b.score << endl;
    out << "Hi Score:" << setw(4) << b.Hi_Score << endl;
    for (int i = 0; i < 11; i++) {out << '-';}
    out << endl;
    TextDisplay t = *(b.td);
    out << t;
    for (int i = 0; i < 11; i++) {out << '-';}
    out << endl;
    return out;
}
