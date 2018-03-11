#include "level.h"
using namespace std;


Level::Level(int level, string file, bool seedexist, int seed):
level(level), file(file) {
    if (seedexist) {
        srand(seed);
    }
}

int Level::getlevel() {
    return level;
}

char Level::getnext() {
    return next;
}

void Level::setlevel(int level) {
    this->level = level;
}

void Level::levelup(int times) {
    for (int i = 0; i < times; i++) {
        if (level > 3) {
            return;
        } else {
            level++;
        }
    }
}

void Level::leveldown(int times) {
    for (int i = 0; i < times; i++) {
        if (level < 1) {
            return;
        } else {
            level--;
        }
    }
}

void Level::display_next() {
    cout << "Next:" << endl;
    if (next == 'I') {
        cout << "IIII" << endl;
    }
    else if (next == 'J') {
        cout << "J" << endl;
        cout << "JJJ" << endl;
    }
    else if (next == 'L') {
        cout << "  L" << endl;
        cout << "LLL" << endl;
    }
    else if (next == 'O') {
        cout << "OO" << endl;
        cout << "OO" << endl;
    }
    else if (next == 'S') {
        cout << " SS" << endl;
        cout << "SS" << endl;
    }
    else if (next == 'Z') {
        cout << "ZZ" << endl;
        cout << " ZZ" << endl;
    }
    else if (next == 'T') {
        cout << "TTT" << endl;
        cout << " T " << endl;
    }
}


Block Level::generateBlock(shared_ptr<Board> b, int ith, int &pos, bool random34, string file) {
    Block currb;
    if (level == 0) {
        ifstream f(this->file);
        char c;
        vector<char> char_vec;
        char_vec.clear();
        while (f >> c) {
            if (((c == 'T' || c == 'S') || (c == 'L' || c == 'O')) ||
                ((c == 'J' || c == 'Z') || c == 'I'))
                char_vec.push_back(c);
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
        rand();
        int poss = rand() % 7;
        if (start == false) {
            now = char_vec[poss];
            poss = rand() % 7;
            next = char_vec[poss];
            start = true;
        }
        else {
            now = next;
            next = char_vec[poss];
        }
    }
    else if (level == 3 || level == 4) {
        if (random34) {
            char char_vec[] = {'S','Z','I','T','J','L','O','S','Z'};
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
        } else {
            ifstream f(file);
            char c;
            vector<char> char_vec;
            char_vec.clear();
            while (f >> c) {
                if (((c == 'T' || c == 'S') || (c == 'L' || c == 'O')) ||
                    ((c == 'J' || c == 'Z') || c == 'I'))
                    char_vec.push_back(c);
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
    }
    currb = Block(now, b, ith);
    return currb;
}
