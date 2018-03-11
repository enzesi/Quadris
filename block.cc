#include "block.h"
#include "combination.h"
#include <iostream>
using namespace std;

bool comp(Combination one, Combination sec) {
    return (((one.a.x == sec.a.x && one.a.y == sec.a.y) &&
             (one.b.x == sec.b.x && one.b.y == sec.b.y)) &&
            ((one.c.x == sec.c.x && one.c.y == sec.c.y) &&
             (one.d.x == sec.d.x && one.d.y == sec.d.y)));

}

Block::Block(){};

// initialize the block;
Block::Block(char type, shared_ptr<Board> board, int ith):
type(type), ith(ith) {
    this->board = board;
    block.clear();
    if (type == 'I') {
        block.push_back(Posn{3,0});
        block.push_back(Posn{3,1});
        block.push_back(Posn{3,2});
        block.push_back(Posn{3,3});
    } else if (type == 'J') {
        block.push_back(Posn{3,0});
        block.push_back(Posn{4,0});
        block.push_back(Posn{4,1});
        block.push_back(Posn{4,2});
    } else if (type == 'L') {
        block.push_back(Posn{3,2});
        block.push_back(Posn{4,0});
        block.push_back(Posn{4,1});
        block.push_back(Posn{4,2});
    } else if (type == 'O') {
        block.push_back(Posn{3,0});
        block.push_back(Posn{3,1});
        block.push_back(Posn{4,0});
        block.push_back(Posn{4,1});
    } else if (type == 'S') {
        block.push_back(Posn{3,1});
        block.push_back(Posn{3,2});
        block.push_back(Posn{4,0});
        block.push_back(Posn{4,1});
    } else if (type == 'Z') {
        block.push_back(Posn{3,0});
        block.push_back(Posn{3,1});
        block.push_back(Posn{4,1});
        block.push_back(Posn{4,2});
    } else if (type == 'T'){
        block.push_back(Posn{3,0});
        block.push_back(Posn{3,1});
        block.push_back(Posn{3,2});
        block.push_back(Posn{4,1});
    } else {
        block.push_back(Posn{3,5});
    }
    if (!board->check(block) && type != '*') {
        throw 1;
    }// if it is not avalible to generate a new block, the game is over;
    board->set(block, type);
}

void Block::clean() {
    board->clear(block);
}

void Block::left(int times, bool hint, vector<Combination> *choice) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for (int t = 0; t < times; t++) {
        vector<Posn> newB;
        for (int i = 0; i < 4; i++) { //get the possible positions;
            Posn np;
            np.x = block[i].x;
            np.y = block[i].y - 1;
            if (np.y < 0) {
                stop = true;
                break;
            }
            newB.push_back(np);
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block); // clean the current block temporarily;
        }
        if (board->check(newB)) {    // check the newspace is available or not;
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                downhelp(15, true, choice); // do the recursion to find the
                clockwiselhelp(4, true, choice); // hint;
                counterclockwisehelp(4, true, choice);
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}

void Block::right(int times, bool hint, vector<Combination> *choice) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for (int t = 0; t < times; t++) {
        vector<Posn> newB;
        for (int i = 0; i < 4; i++) {// similar as above;
            Posn np;
            np.x = block[i].x;
            np.y = block[i].y + 1;
            if (np.y > 10) {
                stop = true;
                break;
            }
            newB.push_back(np);
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                downhelp(15, true, choice); // similar as above;
                clockwiserhelp(4, true, choice);
                counterclockwisehelp(4, true, choice);
                downhelp(15, true, choice);
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}

void Block::down(int times, bool hint, vector<Combination> *choice) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for (int t = 0; t < times; t++) {   // similar as above;
        vector<Posn> newB;
        for (int i = 0; i < 4; i++) {
            Posn np;
            np.x = block[i].x + 1;
            np.y = block[i].y;
            if (np.x > 17) {
                stop = true;
                break;
            }
            newB.push_back(np);
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                lefthelp(13, true, choice);
                righthelp(13, true, choice);
                clockwiselhelp(4, true, choice);
                counterclockwisehelp(4, true, choice);
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}

void Block::drop() {
    if (type == '*') {
        board->clear(block);
        while(1) {
            vector<Posn> newB;
            Posn np;
            np.x = block[0].x + 1;
            np.y = block[0].y;
            if (np.x > 17) {
                break;
            }
            newB.push_back(np);
            board->tempclean(block);
            if (board->check(newB)) {
                block[0].x = np.x;
                block[0].y = np.y;
            } else {
                break;
            }
        }
        board->set(block, type);
        return;
    }
    this->down(15);
    board->setith(block, ith);
}

void Block::clockwise(int times, bool hint, vector<Combination> *choice) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for(int t = 0; t < times; t++) {      // different types of block have
        vector<Posn> newB;                // different kinds of algorithms
        if (type == 'I') {                // to rotate;
            bool same_col = false;
            if (block[0].x != block[1].x){
                same_col = true;
            }
            if (same_col) {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    np.x = block[i].x + 3 - i;
                    np.y = block[i].y + i;
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    np.x = block[i].x - 3 + i;
                    np.y = block[i].y - i;
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            }
        } else if (type == 'O') {
            stop = true;
            break;
        } else if (type == 'Z') {
            bool z1 = true;        
            if ((block[3].x - block[0].x) != 1) {
                z1 = false;
            }
            if (z1) {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 2;
                    }
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 2;
                    }
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            }
        } else if (type == 'S') {
            bool z1 = true;        
            if ((block[3].x - block[0].x) != 1) {
                z1 = false;
            }
            if (z1) {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y - 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y - 2;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    }
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y + 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y + 2;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    }
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            }
        } else if (type == 'J') {
            int Jtype = 0;
            if ((block[3].x - block[0].x) == 1) {
                if ((block[1].x - block[0].x) == 1) {
                    Jtype = 0;
                } else {
                    Jtype = 2;
                }
            } else {
                if ((block[1].x - block[0].x) == 1) {
                    Jtype = 3;
                } else {
                    Jtype = 1;
                }
            }
            for (int i = 0; i < 4; i++) {
                Posn np;
                if (Jtype == 0) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x - 2;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 2;
                    }
                } else if (Jtype == 1) {
                    if (i == 0 || i == 1) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 2;
                    }
                } else if (Jtype == 2) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 2;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else {
                    if (i == 0 || i == 1) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                }
                if (np.y > 10) {
                    stop = true;
                    break;
                }
                newB.push_back(np);
            }
        } else if (type == 'L') {
            int Ltype = 0;
            if ((block[3].x - block[0].x) == 1) {
                if ((block[1].x - block[0].x) == 1) {
                    Ltype = 0;
                } else {
                    Ltype = 2;
                }
            } else {
                if ((block[1].x - block[0].x) == 1) {
                    Ltype = 1;
                } else {
                    Ltype = 3;
                }
            }
            for (int i = 0; i < 4; i++) {
                Posn np;
                if (Ltype == 0) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y - 2;
                    } else if (i == 1) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else if (Ltype == 1) {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 2;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else if (Ltype == 2) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                } else {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y + 2;
                    } else if (i == 1) {
                        np.x = block[i].x + 2;
                        np.y = block[i].y - 1;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                }
                if (np.y > 10) {
                    stop = true;
                    break;
                }
                newB.push_back(np);
            }
        } else { // type == 'T';
            int Ttype = 0;
            if ((block[3].x - block[0].x) == 1) {
                if ((block[1].x - block[0].x) == 1) {
                    Ttype = 2;
                } else {
                    Ttype = 0;
                }
            } else {
                if ((block[0].y - block[1].y) == 1) {
                    Ttype = 1;
                } else {
                    Ttype = 3;
                }
            }
            for (int i = 0; i < 4; i++) {
                Posn np;
                if (Ttype == 0) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    }
                } else if (Ttype == 1) {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                } else if (Ttype == 2) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y - 1;
                    } else if (i == 1) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 2;
                    }
                } else {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                }
                if (np.y > 10) {
                    stop = true;
                    break;
                }
                newB.push_back(np);
            }
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                right(11, true, choice);
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                left(11, true, choice);
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                down(15, true, choice);
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}

void Block::countclockwise(int times, bool hint,vector<Combination> *choice ) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for (int t = 0; t < times; t++) {
        vector<Posn> newB;
        if ((type == 'I' || type == 'O') || (type == 'S' || type == 'Z')){
            if (!hint) {
                clockwise(times);
            }
            return;
        } else if (type == 'J') {
            int Jtype = 0;
            if ((block[3].x - block[0].x) == 1) {
                if ((block[1].x - block[0].x) == 1) {
                    Jtype = 0;
                } else {
                    Jtype = 2;
                }
            } else {
                if ((block[1].x - block[0].x) == 1) {
                    Jtype = 3;
                } else {
                    Jtype = 1;
                }
            }
            for (int i = 0; i < 4; i++) {
                Posn np;
                if (Jtype == 0) {
                    if (i == 0 || i == 1) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else if (Jtype == 1) {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x + 2;
                        np.y = block[i].y - 1;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 2;
                    }
                } else if (Jtype == 2) {
                    if (i == 0 || i == 1) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 2;
                    }
                } else {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 2;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                }
                if (np.y > 10) {
                    stop = true;
                    break;
                }
                newB.push_back(np);
            }
        } else if (type == 'L') {
            int Ltype = 0;
            if ((block[3].x - block[0].x) == 1) {
                if ((block[1].x - block[0].x) == 1) {
                    Ltype = 0;
                } else {
                    Ltype = 2;
                }
            } else {
                if ((block[1].x - block[0].x) == 1) {
                    Ltype = 1;
                } else {
                    Ltype = 3;
                }
            }
            for (int i = 0; i < 4; i++) {
                Posn np;
                if (Ltype == 0) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y - 2;
                    } else if (i == 1) {
                        np.x = block[i].x - 2;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else if (Ltype == 1) {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y + 2;
                    } else if (i == 1) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                } else if (Ltype == 2) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 2;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                } else {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                }
                if (np.y > 10) {
                    stop = true;
                    break;
                }
                newB.push_back(np);
            }
        } else { // type == 'T';
            int Ttype = 0;
            if ((block[3].x - block[0].x) == 1) {
                if ((block[1].x - block[0].x) == 1) {
                    Ttype = 2;
                } else {
                    Ttype = 0;
                }
            } else {
                if ((block[0].y - block[1].y) == 1) {
                    Ttype = 1;
                } else {
                    Ttype = 3;
                }
            }
            for (int i = 0; i < 4; i++) {
                Posn np;
                if (Ttype == 0) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else if (Ttype == 1) {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    }
                } else if (Ttype == 2) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y + 1;
                    } else if (i == 1) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 2;
                    }
                }
                if (np.y > 10) {
                    stop = true;
                    break;
                }
                newB.push_back(np);
            }
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                left(11, true, choice);
                right(11, true, choice);
                down(15, true, choice);
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}


// The codes below are same as above but they are used for hint to do recursion.
void Block::counterclockwisehelp(int times, bool hint,
                            vector<Combination> *choice ) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for (int t = 0; t < times; t++) {
        vector<Posn> newB;
        if ((type == 'I' || type == 'O') || (type == 'S' || type == 'Z')){
            if (!hint) {
                clockwise(times);
            }
            return;
        } else if (type == 'J') {
            int Jtype = 0;
            if ((block[3].x - block[0].x) == 1) {
                if ((block[1].x - block[0].x) == 1) {
                    Jtype = 0;
                } else {
                    Jtype = 2;
                }
            } else {
                if ((block[1].x - block[0].x) == 1) {
                    Jtype = 3;
                } else {
                    Jtype = 1;
                }
            }
            for (int i = 0; i < 4; i++) {
                Posn np;
                if (Jtype == 0) {
                    if (i == 0 || i == 1) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else if (Jtype == 1) {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x + 2;
                        np.y = block[i].y - 1;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 2;
                    }
                } else if (Jtype == 2) {
                    if (i == 0 || i == 1) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 2;
                    }
                } else {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 2;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                }
                if (np.y > 10) {
                    stop = true;
                    break;
                }
                newB.push_back(np);
            }
        } else if (type == 'L') {
            int Ltype = 0;
            if ((block[3].x - block[0].x) == 1) {
                if ((block[1].x - block[0].x) == 1) {
                    Ltype = 0;
                } else {
                    Ltype = 2;
                }
            } else {
                if ((block[1].x - block[0].x) == 1) {
                    Ltype = 1;
                } else {
                    Ltype = 3;
                }
            }
            for (int i = 0; i < 4; i++) {
                Posn np;
                if (Ltype == 0) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y - 2;
                    } else if (i == 1) {
                        np.x = block[i].x - 2;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else if (Ltype == 1) {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y + 2;
                    } else if (i == 1) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                } else if (Ltype == 2) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 2;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                } else {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                }
                if (np.y > 10) {
                    stop = true;
                    break;
                }
                newB.push_back(np);
            }
        } else { // type == 'T';
            int Ttype = 0;
            if ((block[3].x - block[0].x) == 1) {
                if ((block[1].x - block[0].x) == 1) {
                    Ttype = 2;
                } else {
                    Ttype = 0;
                }
            } else {
                if ((block[0].y - block[1].y) == 1) {
                    Ttype = 1;
                } else {
                    Ttype = 3;
                }
            }
            for (int i = 0; i < 4; i++) {
                Posn np;
                if (Ttype == 0) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else if (Ttype == 1) {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    }
                } else if (Ttype == 2) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y + 1;
                    } else if (i == 1) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 2;
                    }
                }
                if (np.y > 10) {
                    stop = true;
                    break;
                }
                newB.push_back(np);
            }
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                lefthelp3(11, true, choice);
                righthelp3(11, true, choice);
                downhelp3(15, true, choice);
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}
void Block::clockwiselhelp(int times, bool hint, vector<Combination> *choice) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for(int t = 0; t < times; t++) {
        vector<Posn> newB;
        if (type == 'I') {
            bool same_col = false;
            if (block[0].x != block[1].x){
                same_col = true;
            }
            if (same_col) {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    np.x = block[i].x + 3 - i;
                    np.y = block[i].y + i;
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    np.x = block[i].x - 3 + i;
                    np.y = block[i].y - i;
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            }
        } else if (type == 'O') {
            stop = true;
            break;
        } else if (type == 'Z') {
            bool z1 = true;        
            if ((block[3].x - block[0].x) != 1) {
                z1 = false;
            }
            if (z1) {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 2;
                    }
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 2;
                    }
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            }
        } else if (type == 'S') {
            bool z1 = true;
            if ((block[3].x - block[0].x) != 1) {
                z1 = false;
            }
            if (z1) {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y - 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y - 2;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    }
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y + 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y + 2;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    }
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            }
        } else if (type == 'J') {
            int Jtype = 0;
            if ((block[3].x - block[0].x) == 1) {
                if ((block[1].x - block[0].x) == 1) {
                    Jtype = 0;
                } else {
                    Jtype = 2;
                }
            } else {
                if ((block[1].x - block[0].x) == 1) {
                    Jtype = 3;
                } else {
                    Jtype = 1;
                }
            }
            for (int i = 0; i < 4; i++) {
                Posn np;
                if (Jtype == 0) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x - 2;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 2;
                    }
                } else if (Jtype == 1) {
                    if (i == 0 || i == 1) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 2;
                    }
                } else if (Jtype == 2) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 2;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else {
                    if (i == 0 || i == 1) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                }
                if (np.y > 10) {
                    stop = true;
                    break;
                }
                newB.push_back(np);
            }
        } else if (type == 'L') {
            int Ltype = 0;
            if ((block[3].x - block[0].x) == 1) {
                if ((block[1].x - block[0].x) == 1) {
                    Ltype = 0;
                } else {
                    Ltype = 2;
                }
            } else {
                if ((block[1].x - block[0].x) == 1) {
                    Ltype = 1;
                } else {
                    Ltype = 3;
                }
            }
            for (int i = 0; i < 4; i++) {
                Posn np;
                if (Ltype == 0) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y - 2;
                    } else if (i == 1) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else if (Ltype == 1) {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 2;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else if (Ltype == 2) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                } else {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y + 2;
                    } else if (i == 1) {
                        np.x = block[i].x + 2;
                        np.y = block[i].y - 1;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                }
                if (np.y > 10) {
                    stop = true;
                    break;
                }
                newB.push_back(np);
            }
        } else { 
            int Ttype = 0;
            if ((block[3].x - block[0].x) == 1) {
                if ((block[1].x - block[0].x) == 1) {
                    Ttype = 2;
                } else {
                    Ttype = 0;
                }
            } else {
                if ((block[0].y - block[1].y) == 1) {
                    Ttype = 1;
                } else {
                    Ttype = 3;
                }
            }
            for (int i = 0; i < 4; i++) {
                Posn np;
                if (Ttype == 0) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    }
                } else if (Ttype == 1) {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                } else if (Ttype == 2) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y - 1;
                    } else if (i == 1) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 2;
                    }
                } else {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                }
                if (np.y > 10) {
                    stop = true;
                    break;
                }
                newB.push_back(np);
            }
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                lefthelp3(11, true, choice);
                righthelp3(11, true, choice);
                downhelp3(15, true, choice);
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}

void Block::clockwiserhelp(int times, bool hint, vector<Combination> *choice) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for(int t = 0; t < times; t++) {
        vector<Posn> newB;
        if (type == 'I') {
            bool same_col = false;
            if (block[0].x != block[1].x){
                same_col = true;
            }
            if (same_col) {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    np.x = block[i].x + 3 - i;
                    np.y = block[i].y + i;
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    np.x = block[i].x - 3 + i;
                    np.y = block[i].y - i;
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            }
        } else if (type == 'O') {
            stop = true;
            break;
        } else if (type == 'Z') {
            bool z1 = true;         // (3,0) (3,1) (4,1) (4,2)
            if ((block[3].x - block[0].x) != 1) {
                z1 = false;
            }
            if (z1) {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 2;
                    }
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 2;
                    }
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            }
        } else if (type == 'S') {
            bool z1 = true;
            if ((block[3].x - block[0].x) != 1) {
                z1 = false;
            }
            if (z1) {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y - 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y - 2;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    }
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    Posn np;
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y + 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y + 2;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    }
                    if (np.y > 10) {
                        stop = true;
                        break;
                    }
                    newB.push_back(np);
                }
            }
        } else if (type == 'J') {
            int Jtype = 0;
            if ((block[3].x - block[0].x) == 1) {
                if ((block[1].x - block[0].x) == 1) {
                    Jtype = 0;
                } else {
                    Jtype = 2;
                }
            } else {
                if ((block[1].x - block[0].x) == 1) {
                    Jtype = 3;
                } else {
                    Jtype = 1;
                }
            }
            for (int i = 0; i < 4; i++) {
                Posn np;
                if (Jtype == 0) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x - 2;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 2;
                    }
                } else if (Jtype == 1) {
                    if (i == 0 || i == 1) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 2;
                    }
                } else if (Jtype == 2) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 2;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else {
                    if (i == 0 || i == 1) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                }
                if (np.y > 10) {
                    stop = true;
                    break;
                }
                newB.push_back(np);
            }
        } else if (type == 'L') {
            int Ltype = 0;
            if ((block[3].x - block[0].x) == 1) {
                if ((block[1].x - block[0].x) == 1) {
                    Ltype = 0;
                } else {
                    Ltype = 2;
                }
            } else {
                if ((block[1].x - block[0].x) == 1) {
                    Ltype = 1;
                } else {
                    Ltype = 3;
                }
            }
            for (int i = 0; i < 4; i++) {
                Posn np;
                if (Ltype == 0) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y - 2;
                    } else if (i == 1) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else if (Ltype == 1) {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 2;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    }
                } else if (Ltype == 2) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                } else {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y + 2;
                    } else if (i == 1) {
                        np.x = block[i].x + 2;
                        np.y = block[i].y - 1;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                }
                if (np.y > 10) {
                    stop = true;
                    break;
                }
                newB.push_back(np);
            }
        } else { // type == 'T';
            int Ttype = 0;
            if ((block[3].x - block[0].x) == 1) {
                if ((block[1].x - block[0].x) == 1) {
                    Ttype = 2;
                } else {
                    Ttype = 0;
                }
            } else {
                if ((block[0].y - block[1].y) == 1) {
                    Ttype = 1;
                } else {
                    Ttype = 3;
                }
            }
            for (int i = 0; i < 4; i++) {
                Posn np;
                if (Ttype == 0) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y + 1;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y - 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y;
                    }
                } else if (Ttype == 1) {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                } else if (Ttype == 2) {
                    if (i == 0) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y - 1;
                    } else if (i == 1) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else if (i == 2) {
                        np.x = block[i].x - 1;
                        np.y = block[i].y;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y - 2;
                    }
                } else {
                    if (i == 0) {
                        np.x = block[i].x + 1;
                        np.y = block[i].y;
                    } else if (i == 1) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else if (i == 2) {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    } else {
                        np.x = block[i].x;
                        np.y = block[i].y + 1;
                    }
                }
                if (np.y > 10) {
                    stop = true;
                    break;
                }
                newB.push_back(np);
            }
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                righthelp3(11, true, choice);
                lefthelp3(11, true, choice);
                downhelp3(15,true,choice);
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}

void Block::lefthelp(int times, bool hint, vector<Combination> *choice) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for (int t = 0; t < times; t++) {
        vector<Posn> newB;
        for (int i = 0; i < 4; i++) {
            Posn np;
            np.x = block[i].x;
            np.y = block[i].y - 1;
            if (np.y < 0) {
                stop = true;
                break;
            }
            newB.push_back(np);
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                clockwiselhelp(4, true, choice);
                counterclockwisehelp(4, true, choice);
                downhelp2(15, true, choice);
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}

void Block::righthelp(int times, bool hint, vector<Combination> *choice) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for (int t = 0; t < times; t++) {
        vector<Posn> newB;
        for (int i = 0; i < 4; i++) {
            Posn np;
            np.x = block[i].x;
            np.y = block[i].y + 1;
            if (np.y > 10) {
                stop = true;
                break;
            }
            newB.push_back(np);
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint){
                counterclockwisehelp(4, true, choice);
                clockwiserhelp(4, true, choice);
                downhelp2(15, true, choice);
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}

void Block::downhelp(int times, bool hint, vector<Combination> *choice) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for (int t = 0; t < times; t++) {
        vector<Posn> newB;
        for (int i = 0; i < 4; i++) {
            Posn np;
            np.x = block[i].x + 1;
            np.y = block[i].y;
            if (np.x > 17) {
                stop = true;
                break;
            }
            newB.push_back(np);
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                counterclockwisehelp(4, true, choice);
                righthelp2(11, true, choice);
                lefthelp2(11, true, choice);
                clockwiselhelp(4, true, choice);
                lefthelp2(11, true, choice);
                righthelp2(11, true, choice);
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}

void Block::lefthelp2(int times, bool hint, vector<Combination> *choice) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for (int t = 0; t < times; t++) {
        vector<Posn> newB;
        for (int i = 0; i < 4; i++) {
            Posn np;
            np.x = block[i].x;
            np.y = block[i].y - 1;
            if (np.y < 0) {
                stop = true;
                break;
            }
            newB.push_back(np);
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                downhelp3(15, true, choice);
                clockwiselhelp(4, true, choice);
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}

void Block::righthelp2(int times, bool hint, vector<Combination> *choice) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for (int t = 0; t < times; t++) {
        vector<Posn> newB;
        for (int i = 0; i < 4; i++) {
            Posn np;
            np.x = block[i].x;
            np.y = block[i].y + 1;
            if (np.y > 10) {
                stop = true;
                break;
            }
            newB.push_back(np);
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                clockwiserhelp(4, true, choice);
                downhelp3(15, true, choice);
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}

void Block::downhelp2(int times, bool hint, vector<Combination> *choice) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for (int t = 0; t < times; t++) {
        vector<Posn> newB;
        for (int i = 0; i < 4; i++) {
            Posn np;
            np.x = block[i].x + 1;
            np.y = block[i].y;
            if (np.x > 17) {
                stop = true;
                break;
            }
            newB.push_back(np);
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                counterclockwisehelp(4, true, choice);
                righthelp3(11, true, choice);
                lefthelp3(11, true, choice);
                clockwiselhelp(4, true, choice);
                lefthelp3(11, true, choice);
                righthelp3(11, true, choice);
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                bool same = false;
                for (int i = 0; i < 4; i++) {
                    block[i].x = newB[i].x;
                    block[i].y = newB[i].y;
                }
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}

void Block::lefthelp3(int times, bool hint, vector<Combination> *choice) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for (int t = 0; t < times; t++) {
        vector<Posn> newB;
        for (int i = 0; i < 4; i++) {
            Posn np;
            np.x = block[i].x;
            np.y = block[i].y - 1;
            if (np.y < 0) {
                stop = true;
                break;
            }
            newB.push_back(np);
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}

void Block::righthelp3(int times, bool hint, vector<Combination> *choice) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for (int t = 0; t < times; t++) {
        vector<Posn> newB;
        for (int i = 0; i < 4; i++) {
            Posn np;
            np.x = block[i].x;
            np.y = block[i].y + 1;
            if (np.y > 10) {
                stop = true;
                break;
            }
            newB.push_back(np);
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}

void Block::downhelp3(int times, bool hint, vector<Combination> *choice) {
    bool stop = false;
    if (!hint) {
        board->clear(block);
    }
    for (int t = 0; t < times; t++) {
        vector<Posn> newB;
        for (int i = 0; i < 4; i++) {
            Posn np;
            np.x = block[i].x + 1;
            np.y = block[i].y;
            if (np.x > 17) {
                stop = true;
                break;
            }
            newB.push_back(np);
        }
        if (stop) break;
        if (!hint) {
            board->tempclean(block);
        }
        if (board->check(newB)) {
            for (int i = 0; i < 4; i++) {
                block[i].x = newB[i].x;
                block[i].y = newB[i].y;
            }
            if (hint) {
                Combination blo;
                blo.a.x = newB[0].x;
                blo.a.y = newB[0].y;
                blo.b.x = newB[1].x;
                blo.b.y = newB[1].y;
                blo.c.x = newB[2].x;
                blo.c.y = newB[2].y;
                blo.d.x = newB[3].x;
                blo.d.y = newB[3].y;
                bool same = false;
                int size = choice->size();
                for (int i = 0; i < size; i++) {
                    if (comp((*choice)[i],blo)) {
                        same = true;
                    }
                }
                if (!same) {
                    choice->push_back(blo);
                }
            }
        }
    }
    if (!hint) {
        board->set(block, type);
    }
}
// above are hint helper;

Combination Block::hint() {
    vector<Combination> choice;
    vector<Combination> filter;
    Combination self;     // record the current block;
    self.a.x = block[0].x;
    self.a.y = block[0].y;
    self.b.x = block[1].x;
    self.b.y = block[1].y;
    self.c.x = block[2].x;
    self.c.y = block[2].y;
    self.d.x = block[3].x;
    self.d.y = block[3].y;
    board->tempclean(block); // clean the block temporarily;
    if (type == 'O') {
        left(11, true, &choice);
        right(11, true, &choice);
        down(15, true, &choice);
    } else {
        clockwise(4, true, &choice); // do the recursion 
        left(11, true, &choice);
        right(11, true, &choice);
        down(15, true, &choice);
        countclockwise(4, true, &choice);
    }
    bool same = false;
    int size = choice.size();
    for (int i = 0; i < size; i++) { // avoid the same positions;
        if (comp(choice[i],self)) {
            same = true;
        }
    }
    if (!same) {
        choice.push_back(self);
    }
    // find the positions that blocks can land;
    for (unsigned int i = 0; i < choice.size(); i++) {
        vector<Posn> temp;
        temp.push_back(choice[i].a);
        temp.push_back(choice[i].b);
        temp.push_back(choice[i].c);
        temp.push_back(choice[i].d);
        temp[0].x++;
        temp[1].x++;
        temp[2].x++;
        temp[3].x++;
        if (((choice[i].d.x + 1) > 17) || (!(board->check(temp)))) {
            filter.push_back(choice[i]);
        }
    }
    block[0].x = self.a.x;
    block[0].y = self.a.y;
    block[1].x = self.b.x;
    block[1].y = self.b.y;
    block[2].x = self.c.x;
    block[2].y = self.c.y;
    block[3].x = self.d.x;
    block[3].y = self.d.y;
    board->setback(block);
    vector <Combination> bestcom;
    bestcom.clear();
    int bestline = 0;
    // find which positions can clean whole lines;
    for (unsigned int i = 0; i < filter.size(); i++) {
        int numofzero = 0;
        int x1, x2, x3, x4;
        vector<Posn> temp;
        temp.push_back(filter[i].a);
        temp.push_back(filter[i].b);
        temp.push_back(filter[i].c);
        temp.push_back(filter[i].d);
        board->setback(temp);
        x1 = board->getEmpty(filter[i].a.x);
        x2 = board->getEmpty(filter[i].b.x);
        x3 = board->getEmpty(filter[i].c.x);
        x4 = board->getEmpty(filter[i].d.x);
        board->tempclean(temp);
        if (x1 == 0) numofzero++;
        if (x2 == 0) numofzero++;
        if (x3 == 0) numofzero++;
        if (x4 == 0) numofzero++;
        if (numofzero > bestline) {
            bestline = numofzero;
            bestcom.clear();
            bestcom.push_back(filter[i]);
        } else if (numofzero == bestline) {
            bestcom.push_back(filter[i]);
        }
    }
    vector<int> emp;
    // find which postions has less empty space under the block;
    if (bestline != 0) {
        for (unsigned int i = 0; i < bestcom.size(); i++) {
            if (type == 'I') {
                int Itype = 0;
                if (bestcom[i].a.x == bestcom[i].b.x) {
                    Itype = 0;
                } else {
                    Itype = 1;
                }
                if (Itype == 0) {
                    int empty = 4;
                    Posn a{bestcom[i].a.x + 1, bestcom[i].a.y};
                    Posn b{bestcom[i].b.x + 1, bestcom[i].b.y};
                    Posn c{bestcom[i].c.x + 1, bestcom[i].c.y};
                    Posn d{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    if (c.x > 17 || (!board->checkempty(c))) {
                        empty--;
                    }
                    if (d.x > 17 || (!board->checkempty(d))) {
                        empty--;
                    }
                    emp.push_back(empty);
                } else {
                    int empty = 1;
                    Posn a{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    emp.push_back(empty);
                }
            } else if (type == 'Z') {
                int Ztype = 0;
                if ((bestcom[i].d.x - bestcom[i].a.x) != 1) {
                    Ztype = 1;
                }
                if (Ztype == 0) {
                    int empty = 3;
                    Posn a{bestcom[i].a.x + 1, bestcom[i].a.y};
                    Posn b{bestcom[i].c.x + 1, bestcom[i].c.y};
                    Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    if (c.x > 17 || (!board->checkempty(c))) {
                        empty--;
                    }
                    emp.push_back(empty);
                } else {
                    int empty = 2;
                    Posn a{bestcom[i].c.x + 1, bestcom[i].c.y};
                    Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    emp.push_back(empty);
                }
            } else if (type == 'S') {
                int Stype = 0;
                if ((bestcom[i].d.x - bestcom[i].a.x) != 1) {
                    Stype = 1;
                }
                if (Stype == 0) {
                    int empty = 3;
                    Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                    Posn b{bestcom[i].c.x + 1, bestcom[i].c.y};
                    Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    if (c.x > 17 || (!board->checkempty(c))) {
                        empty--;
                    }
                    emp.push_back(empty);
                } else {
                    int empty = 2;
                    Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                    Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    emp.push_back(empty);
                }
            } else if (type == 'J') {
                int Jtype = 0;
                if ((bestcom[i].d.x - bestcom[i].a.x) == 1) {
                    if ((bestcom[i].b.x - bestcom[i].a.x) == 1) {
                        Jtype = 0;
                    } else {
                        Jtype = 2;
                    }
                } else {
                    if ((bestcom[i].b.x - bestcom[i].a.x) == 1) {
                        Jtype = 3;
                    } else {
                        Jtype = 1;
                    }
                }
                if (Jtype == 0) {
                    int empty = 3;
                    Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                    Posn b{bestcom[i].c.x + 1, bestcom[i].c.y};
                    Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    if (c.x > 17 || (!board->checkempty(c))) {
                        empty--;
                    }
                    emp.push_back(empty);
                } else if (Jtype == 1) {
                    int empty = 2;
                    Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                    Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    emp.push_back(empty);
                } else if (Jtype == 2) {
                    int empty = 3;
                    Posn a{bestcom[i].a.x + 1, bestcom[i].a.y};
                    Posn b{bestcom[i].b.x + 1, bestcom[i].b.y};
                    Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    if (c.x > 17 || (!board->checkempty(c))) {
                        empty--;
                    }
                    emp.push_back(empty);
                } else {
                    int empty = 2;
                    Posn a{bestcom[i].c.x + 1, bestcom[i].c.y};
                    Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    emp.push_back(empty);
                }
            } else if (type == 'L') {
                int Ltype = 0;
                if ((bestcom[i].d.x - bestcom[i].a.x) == 1) {
                    if ((bestcom[i].b.x - bestcom[i].a.x) == 1) {
                        Ltype = 0;
                    } else {
                        Ltype = 2;
                    }
                } else {
                    if ((bestcom[i].b.x - bestcom[i].a.x) == 1) {
                        Ltype = 1;
                    } else {
                        Ltype = 3;
                    }
                }
                if (Ltype == 0) {
                    int empty = 3;
                    Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                    Posn b{bestcom[i].c.x + 1, bestcom[i].c.y};
                    Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    if (c.x > 17 || (!board->checkempty(c))) {
                        empty--;
                    }
                    emp.push_back(empty);
                } else if (Ltype == 1) {
                    int empty = 2;
                    Posn a{bestcom[i].c.x + 1, bestcom[i].c.y};
                    Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    emp.push_back(empty);
                } else if (Ltype == 2) {
                    int empty = 3;
                    Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                    Posn b{bestcom[i].c.x + 1, bestcom[i].c.y};
                    Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    if (c.x > 17 || (!board->checkempty(c))) {
                        empty--;
                    }
                    emp.push_back(empty);
                } else {
                    int empty = 2;
                    Posn a{bestcom[i].a.x + 1, bestcom[i].a.y};
                    Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    emp.push_back(empty);
                }
            } else if (type == 'T') {
                int Ttype = 0;
                if ((bestcom[i].d.x - bestcom[i].a.x) == 1) {
                    if ((bestcom[i].b.x - bestcom[i].a.x) == 1) {
                        Ttype = 2;
                    } else {
                        Ttype = 0;
                    }
                } else {
                    if ((bestcom[i].a.y - bestcom[i].b.y) == 1) {
                        Ttype = 1;
                    } else {
                        Ttype = 3;
                    }
                }
                if (Ttype == 0) {
                    int empty = 3;
                    Posn a{bestcom[i].a.x + 1, bestcom[i].a.y};
                    Posn b{bestcom[i].c.x + 1, bestcom[i].c.y};
                    Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    if (c.x > 17 || (!board->checkempty(c))) {
                        empty--;
                    }
                    emp.push_back(empty);
                } else if (Ttype == 1) {
                    int empty = 2;
                    Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                    Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    emp.push_back(empty);
                } else if (Ttype == 2) {
                    int empty = 3;
                    Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                    Posn b{bestcom[i].c.x + 1, bestcom[i].c.y};
                    Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    if (c.x > 17 || (!board->checkempty(c))) {
                        empty--;
                    }
                    emp.push_back(empty);
                } else {
                    int empty = 2;
                    Posn a{bestcom[i].c.x + 1, bestcom[i].c.y};
                    Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                    if (a.x > 17 || (!board->checkempty(a))) {
                        empty--;
                    }
                    if (b.x > 17 || (!board->checkempty(b))) {
                        empty--;
                    }
                    emp.push_back(empty);
                }

            } else {
                break;
            }
        }
        vector<int> empnum;
        int lessempty = 5;
        for (unsigned int i = 0; i < emp.size(); i++) {
            if (emp[i] < lessempty) {
                empnum.clear();
                lessempty = emp[i];
                empnum.push_back(i);
            } else if (emp[i] == lessempty) {
                empnum.push_back(i);
            }
        }
        int lowerb = 0;
        int finalb = 0;
        // find which one is lower;
        for (unsigned int i = 0; i < empnum.size(); i++) {
            if (bestcom[empnum[i]].a.x > lowerb) {
                lowerb = bestcom[empnum[i]].a.x;
                finalb = empnum[i];
            }
        }

        board->setback(block);
        return bestcom[finalb];
    }

    for (unsigned int i = 0; i < bestcom.size(); i++) {
        if (type == 'I') {
            int Itype = 0;
            if (bestcom[i].a.x == bestcom[i].b.x) {
                Itype = 0;
            } else {
                Itype = 1;
            }
            if (Itype == 0) {
                int empty = 4;
                Posn a{bestcom[i].a.x + 1, bestcom[i].a.y};
                Posn b{bestcom[i].b.x + 1, bestcom[i].b.y};
                Posn c{bestcom[i].c.x + 1, bestcom[i].c.y};
                Posn d{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                if (c.x > 17 || (!board->checkempty(c))) {
                    empty--;
                }
                if (d.x > 17 || (!board->checkempty(d))) {
                    empty--;
                }
                emp.push_back(empty);
            } else {
                int empty = 1;
                Posn a{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                emp.push_back(empty);
            }
        } else if (type == 'Z') {
            int Ztype = 0;
            if ((bestcom[i].d.x - bestcom[i].a.x) != 1) {
                Ztype = 1;
            }
            if (Ztype == 0) {
                int empty = 3;
                Posn a{bestcom[i].a.x + 1, bestcom[i].a.y};
                Posn b{bestcom[i].c.x + 1, bestcom[i].c.y};
                Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                if (c.x > 17 || (!board->checkempty(c))) {
                    empty--;
                }
                emp.push_back(empty);
            } else {
                int empty = 2;
                Posn a{bestcom[i].c.x + 1, bestcom[i].c.y};
                Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                emp.push_back(empty);
            }
        } else if (type == 'S') {
            int Stype = 0;
            if ((bestcom[i].d.x - bestcom[i].a.x) != 1) {
                Stype = 1;
            }
            if (Stype == 0) {
                int empty = 3;
                Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                Posn b{bestcom[i].c.x + 1, bestcom[i].c.y};
                Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                if (c.x > 17 || (!board->checkempty(c))) {
                    empty--;
                }
                emp.push_back(empty);
            } else {
                int empty = 2;
                Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                emp.push_back(empty);
            }
        } else if (type == 'J') {
            int Jtype = 0;
            if ((bestcom[i].d.x - bestcom[i].a.x) == 1) {
                if ((bestcom[i].b.x - bestcom[i].a.x) == 1) {
                    Jtype = 0;
                } else {
                    Jtype = 2;
                }
            } else {
                if ((bestcom[i].b.x - bestcom[i].a.x) == 1) {
                    Jtype = 3;
                } else {
                    Jtype = 1;
                }
            }
            if (Jtype == 0) {
                int empty = 3;
                Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                Posn b{bestcom[i].c.x + 1, bestcom[i].c.y};
                Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                if (c.x > 17 || (!board->checkempty(c))) {
                    empty--;
                }
                emp.push_back(empty);
            } else if (Jtype == 1) {
                int empty = 2;
                Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                emp.push_back(empty);
            } else if (Jtype == 2) {
                int empty = 3;
                Posn a{bestcom[i].a.x + 1, bestcom[i].a.y};
                Posn b{bestcom[i].b.x + 1, bestcom[i].b.y};
                Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                if (c.x > 17 || (!board->checkempty(c))) {
                    empty--;
                }
                emp.push_back(empty);
            } else {
                int empty = 2;
                Posn a{bestcom[i].c.x + 1, bestcom[i].c.y};
                Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                emp.push_back(empty);
            }
        } else if (type == 'L') {
            int Ltype = 0;
            if ((bestcom[i].d.x - bestcom[i].a.x) == 1) {
                if ((bestcom[i].b.x - bestcom[i].a.x) == 1) {
                    Ltype = 0;
                } else {
                    Ltype = 2;
                }
            } else {
                if ((bestcom[i].b.x - bestcom[i].a.x) == 1) {
                    Ltype = 1;
                } else {
                    Ltype = 3;
                }
            }
            if (Ltype == 0) {
                int empty = 3;
                Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                Posn b{bestcom[i].c.x + 1, bestcom[i].c.y};
                Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                if (c.x > 17 || (!board->checkempty(c))) {
                    empty--;
                }
                emp.push_back(empty);
            } else if (Ltype == 1) {
                int empty = 2;
                Posn a{bestcom[i].c.x + 1, bestcom[i].c.y};
                Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                emp.push_back(empty);
            } else if (Ltype == 2) {
                int empty = 3;
                Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                Posn b{bestcom[i].c.x + 1, bestcom[i].c.y};
                Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                if (c.x > 17 || (!board->checkempty(c))) {
                    empty--;
                }
                emp.push_back(empty);
            } else {
                int empty = 2;
                Posn a{bestcom[i].a.x + 1, bestcom[i].a.y};
                Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                emp.push_back(empty);
            }
        } else if (type == 'T') {
            int Ttype = 0;
            if ((bestcom[i].d.x - bestcom[i].a.x) == 1) {
                if ((bestcom[i].b.x - bestcom[i].a.x) == 1) {
                    Ttype = 2;
                } else {
                    Ttype = 0;
                }
            } else {
                if ((bestcom[i].a.y - bestcom[i].b.y) == 1) {
                    Ttype = 1;
                } else {
                    Ttype = 3;
                }
            }
            if (Ttype == 0) {
                int empty = 3;
                Posn a{bestcom[i].a.x + 1, bestcom[i].a.y};
                Posn b{bestcom[i].c.x + 1, bestcom[i].c.y};
                Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                if (c.x > 17 || (!board->checkempty(c))) {
                    empty--;
                }
                emp.push_back(empty);
            } else if (Ttype == 1) {
                int empty = 2;
                Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                emp.push_back(empty);
            } else if (Ttype == 2) {
                int empty = 3;
                Posn a{bestcom[i].b.x + 1, bestcom[i].b.y};
                Posn b{bestcom[i].c.x + 1, bestcom[i].c.y};
                Posn c{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                if (c.x > 17 || (!board->checkempty(c))) {
                    empty--;
                }
                emp.push_back(empty);
            } else {
                int empty = 2;
                Posn a{bestcom[i].c.x + 1, bestcom[i].c.y};
                Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
                if (a.x > 17 || (!board->checkempty(a))) {
                    empty--;
                }
                if (b.x > 17 || (!board->checkempty(b))) {
                    empty--;
                }
                emp.push_back(empty);
            }

        } else if (type == 'O'){
            int empty = 2;
            Posn a{bestcom[i].c.x + 1, bestcom[i].c.y};
            Posn b{bestcom[i].d.x + 1, bestcom[i].d.y};
            if (a.x > 17 || (!board->checkempty(a))) {
                empty--;
            }
            if (b.x > 17 || (!board->checkempty(b))) {
                empty--;
            }
            emp.push_back(empty);
        }
    }
    vector<int> empnum;
    int lessempty = 5;
    for (unsigned int i = 0; i < emp.size(); i++) {
        if (emp[i] < lessempty) {
            empnum.clear();
            lessempty = emp[i];
            empnum.push_back(i);
        } else if (emp[i] == lessempty) {
            empnum.push_back(i);
        }
    }
    int lowerb = 0;
    vector<int> lowerri;
    for (unsigned int i = 0; i < empnum.size(); i++) {
        if (bestcom[empnum[i]].a.x > lowerb) {
            lowerri.clear();
            lowerb = bestcom[empnum[i]].a.x;
            lowerri.push_back(empnum[i]);
        } else if (bestcom[empnum[i]].a.x == lowerb) {
            lowerri.push_back(empnum[i]);
        }
    }
    int finalb = 0;
    // find which one is the rightest;
    int right = -1;
    for (unsigned int i = 0; i < lowerri.size(); i++) {
        if (bestcom[lowerri[i]].d.y > right) {
            right = bestcom[lowerri[i]].d.y;
            finalb = lowerri[i];
        }
    }

    board->setback(block);
    return bestcom[finalb];
}

