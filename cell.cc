#include "cell.h"
using namespace std;

Cell::Cell(int x, int y): x(x), y(y) {}

Info Cell::getInfo() const {
    Info info;
    info.x = x;
    info.y = y;
    info.empty = empty;
    info.type = type;
    info.ith = ith;
    return info;
}

bool Cell::getempty() const {
    return empty;
}

void Cell::setith(int ith) {
    this->ith = ith;
}

void Cell::settype(char type) {
    this->type = type;
    notifyObservers();
}

void Cell::cleartemp() {
    this->empty = true;
}

void Cell::setempty(bool empty) {
    this->empty = empty;
    if (empty) {
        notifyObservers();
    }
}
