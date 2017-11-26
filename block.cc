#include "block.h"
using namespace std;

Block::Block(char type, Board *board, int ith):
type(type), board(board), ith(ith) {
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
    if (!board->check(block)) {
        cout <<"game is over" << endl;//throw
    }
    board->set(block, type);
}

void Block::clean() {
    board->clear(block);
}

void Block::left() {
    vector<Posn> newB;
    for (int i = 0; i < 4; i++) {
        Posn np;
        np.x = block[i].x;
        np.y = block[i].y - 1;
        if (np.y < 0) return;
        newB.push_back(np);
    }
    board->clear(block);
    if (board->check(newB)) {
        for (int i = 0; i < 4; i++) {
            block[i].x = newB[i].x;
            block[i].y = newB[i].y;
        }
    }
    board->set(block, type);
}

void Block::right() {
    vector<Posn> newB;
    for (int i = 0; i < 4; i++) {
        Posn np;
        np.x = block[i].x;
        np.y = block[i].y + 1;
        if (np.y > 10) return;
        newB.push_back(np);
    }
    board->clear(block);
    if (board->check(newB)) {
        for (int i = 0; i < 4; i++) {
            block[i].x = newB[i].x;
            block[i].y = newB[i].y;
        }
    }
    board->set(block, type);
}

void Block::down() {
    if (type == '*') {
        vector<Posn> newB;
        Posn np;
        np.x = block[0].x + 1;
        np.y = block[0].y;
        if (np.x > 17) return;
        newB.push_back(np);
        board->clear(block);
        if (board->check(newB)) {
            block[0].x = np.x;
            block[0].y = np.y;
        }
        board->set(block, type);
        return;
    }
    vector<Posn> newB;
    for (int i = 0; i < 4; i++) {
        Posn np;
        np.x = block[i].x + 1;
        np.y = block[i].y;
        if (np.x > 17) return;
        newB.push_back(np);
    }
    board->clear(block);
    if (board->check(newB)) {
        for (int i = 0; i < 4; i++) {
            block[i].x = newB[i].x;
            block[i].y = newB[i].y;
        }
    }
    board->set(block, type);
}

void Block::drop() {
    while(true) {
        int a = block[0].x;
        this->down();
        int b = block[0].x;
        if (a == b) {break;}
    }
    board->setith(block, ith);
}

void Block::clockwise() {
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
                if (np.y > 10) return;
                newB.push_back(np);
            }
        } else {
            for (int i = 0; i < 4; i++) {
                Posn np;
                np.x = block[i].x - 3 + i;
                np.y = block[i].y - i;
                if (np.y > 10) return;
                newB.push_back(np);
            }
        }
    } else if (type == 'O') {
        return;
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
                if (np.y > 10) return;
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
                if (np.y > 10) return;
                newB.push_back(np);
            }
        }
    } else if (type == 'S') {
        bool z1 = true;         // (3,1) (3,2) (4,0) (4,1)
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
                if (np.y > 10) return;
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
                if (np.y > 10) return;
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
            if (np.y > 10) return;
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
            if (np.y > 10) return;
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
            if (np.y > 10) return;
            newB.push_back(np);
        }
    }
    board->clear(block);
    if (board->check(newB)) {
        for (int i = 0; i < 4; i++) { // add level;
            block[i].x = newB[i].x;
            block[i].y = newB[i].y;
        }
    }
    board->set(block, type);
}

void Block::countclockwise() {
    vector<Posn> newB;
    if ((type == 'I' || type == 'O') || (type == 'S' || type == 'Z')){
        clockwise();
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
            if (np.y > 10) return;
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
            if (np.y > 10) return;
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
            if (np.y > 10) return;
            newB.push_back(np);
        }
    }
    board->clear(block);
    if (board->check(newB)) {
        for (int i = 0; i < 4; i++) {
            block[i].x = newB[i].x;
            block[i].y = newB[i].y;
        }
    }
    board->set(block, type);
}
