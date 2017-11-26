#include "textdisplay.h"
using namespace std;


TextDisplay::TextDisplay() {
    for (int i = 0; i < 18; i++) {
        vector<char> c;
        for (int j = 0; j < 11; j++) {
            c.push_back(' ');
        }
        theDisplay.push_back(c);
    }
}

void TextDisplay::notify(Subject &whoNotified) {
    Info info = whoNotified.getInfo();
    int x = info.x;
    int y = info.y;
    char type = info.type;
    bool empty = info.empty;
    if (empty) {
        theDisplay[x][y] = ' ';
    } else {
        theDisplay[x][y] = type;
    }
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j< 11; j++) {
            out << td.theDisplay[i][j];
        }
        out << endl;
    }
    return out;
}
